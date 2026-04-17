#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

// Constants
const int CODE_SIZE = 4;
const int NULL_TERM_SPACE = 1;
const int LIVES = 5;
const char *EXIT = "exit";

// Globals
typedef struct
{
    char digit; // char is used as a small integer data type
    char hint;
    bool taken;
    bool exact;
} IntegerAttribute;

// Prototypes
int *int_to_list(int integer);
bool good_guess(char *guess);
void guess_prompter(char *buffer);
unsigned int nano_seed(void);
int basic_RNG(unsigned int seed, int rangeStart, int rangeEnd);
void code_generator(int *list, int size);
int inputHandler(char *variable);
void inputPrompt(char *variable, char *prompt);

int main(void)
{       
    // Intro
    printf("\n*****\nWelcome to Mastermindle!\n*****\n\nType 'exit' at any time to quit the program.\n");
    // Index #4 used to check if more than 4 digits entered, Index #5 allocated to `scanf()`s automatic newline.
    char userInput[CODE_SIZE + 1 + NULL_TERM_SPACE];
    memset(userInput, '\0', sizeof(userInput[0]) * (CODE_SIZE + 1 + NULL_TERM_SPACE));
    int secretCode[CODE_SIZE + NULL_TERM_SPACE];
    memset(secretCode, '\0', sizeof(secretCode[0]) * (CODE_SIZE + NULL_TERM_SPACE));
    
    // RNG
    code_generator(secretCode, CODE_SIZE);
    
    // loop data
    int *userGuessListed;
    short exactCounter;
    short guessCounter = 0;

    IntegerAttribute indexStatus[CODE_SIZE];
    
    do
    {
        printf("You have %d guesses remaining.\n\n", LIVES - guessCounter);
        guess_prompter(userInput);
        if (!strcmp(EXIT, userInput))
        {
            return 0;
        }
        
        short userGuess = atoi(userInput);
        userGuessListed = int_to_list(userGuess);
        if (userGuessListed == NULL)
        {
            perror("userGuess failed");
            return 1;
        }
        memset(indexStatus, '\0', sizeof(indexStatus));
        
        /* start logic */
        // exact matches loop
        for (int i = 0; i < CODE_SIZE; i++)
        {
            char currentDigit = userGuessListed[i];
            indexStatus[i].digit = currentDigit;
            
            if (currentDigit == secretCode[i])
            {
                indexStatus[i].taken = true;
                indexStatus[i].exact = true;
                indexStatus[i].hint = 'Y';
            }
            else
            {
                // general matches loop
                for (int j = 0; j < CODE_SIZE; j++)
                {
                    if (!indexStatus[j].taken && currentDigit == secretCode[j] && userGuessListed[j] != secretCode[j])
                    {
                        indexStatus[j].taken = true;
                        indexStatus[i].hint = 'O';
                        break;
                    }
                }
            }
        }
        
        // no matches loop
        for (int i = 0; i < CODE_SIZE; i++)
        {
            if (indexStatus[i].hint == '\0')
            {
                indexStatus[i].hint = 'X';
            }
        }
        
        // display hint
        printf("\n");
        for (int i = 0; i < CODE_SIZE; i++)
        {
            printf("[%d]\t", indexStatus[i].digit);
        }
        printf("\n");
        for (int i = 0; i < CODE_SIZE; i++)
        {
            printf(" %c\t", indexStatus[i].hint);
        }
        
        // iteration of terms in do-while conditional
        guessCounter++;
        exactCounter = 0;
        for (int i = 0; i < CODE_SIZE; i++)
        {
            if (indexStatus[i].exact)
            {
                exactCounter++;
            }
        }
        
        free(userGuessListed);
        
    } while (exactCounter < CODE_SIZE && guessCounter < LIVES);
    
    // win/lose conditions
    printf("\n\n*****\n");
    if (exactCounter >= CODE_SIZE)
    {
        if (guessCounter == 1)
        {
            printf("Wow, first try! ");
        }
        printf("Congratulations! ");
    }
    else
    {
        printf("Better luck next time! ");
    }
    
    printf("The secret code was:");
    for (int i = 0; i < CODE_SIZE; i++)
    {
        printf(" %d", secretCode[i]);
    }
    printf("\n*****\n\n");

    return 0;
}

int *int_to_list(int integer)
{
    int *ptr = malloc(sizeof(int) * CODE_SIZE);

    for (int i = 0, divisor = 1000; i < CODE_SIZE; i++, divisor/=10)
    {
        ptr[i] = (integer / divisor) % 10;
    }

    return ptr;
}

bool good_guess(char *guess)
{
    if (guess[CODE_SIZE] != '\0')
    {
        return false;
    }
    
    for (int i = 0; i < CODE_SIZE; i++)
    {
        if (guess[i] == '\0' || guess[i] < '0' || guess[i] > '9')
        {
            return false;
        }
    }
    return true;
}

void guess_prompter(char *buffer)
{
    do
    {
        inputPrompt(buffer, "Please enter a guess for the secret code. It can only be 4 digits long.");
    } while (!good_guess(buffer) && strcmp("exit", buffer));
    return;
}

unsigned int nano_seed(void)
{
    struct timespec seed;
    if (clock_gettime(CLOCK_MONOTONIC, &seed) == -1)
    {
        perror("clock_gettime error");
    }
    unsigned int seedOut = (unsigned int)(seed.tv_sec ^ seed.tv_nsec);
    return seedOut;
}

int basic_RNG(unsigned int seed, int rangeStart, int rangeEnd)
{
    int output = 0;
    srand(seed);
    output = (rand() % (rangeEnd - rangeStart)) + rangeStart;
    return output;
}

void code_generator(int *list, int size)
{
    for (int i = 0; i < size; i++)
    {
        int digit = basic_RNG(nano_seed(), 0, 10);
        list[i] = digit;
    }
    return;
}

int inputHandler(char *variable)
{
    int status = 0;
    int ch;
    status = scanf("%5s", variable);
    while ((ch = getchar()) != '\n' && ch != EOF);
    return status;
}

void inputPrompt(char *variable, char *prompt)
{
    do
    {
        printf("%s\n==> ", prompt);
    } while (inputHandler(variable) != 1);
    return;
}