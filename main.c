#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

// Constants
const int testCode[] = {1, 3, 3, 7};
const int CODE_SIZE = 4;
const int NULL_TERM_SPACE = 1;
const char *EXIT = "exit";
const int WIN_STATE = CODE_SIZE;

// Globals
typedef struct
{
    char digit;
    char hint;
    bool taken;
} IntegerAttribute;

// Prototypes
int *int_to_list(int integer);
bool good_guess(char *guess);
void guess_prompter(char *buffer);
unsigned int nano_seed(void);
int basic_RNG(unsigned int seed, int rangeStart, int rangeEnd);
void code_generator(int *list, int size);
// int digit_counter(int integer);
int inputHandler(char *variable);
void inputPrompt(char *variable, char *prompt);

int main(void)
{    
    // Intro
    printf("\n*****\nWelcome to Mastermindle!\n*****\n\n");
    // Index #4 to check if more than 4 digits entered, Index #5 for `scanf()`s automatic newline.
    char userInput[CODE_SIZE + 1 + NULL_TERM_SPACE];
    memset(userInput, '\0', sizeof(userInput[0]) * (CODE_SIZE + 1 + NULL_TERM_SPACE));
    int secretCode[CODE_SIZE + NULL_TERM_SPACE];
    memset(secretCode, '\0', sizeof(secretCode[0]) * (CODE_SIZE + NULL_TERM_SPACE));

    // RNG
    code_generator(secretCode, CODE_SIZE);
    // debug
    for (int i = 0; i < CODE_SIZE; i++)
    {
        printf("Digit %d: %d\n", i+1, secretCode[i]);
    }
    printf("\n");
    // endDebug

    int *userGuessListed;
    IntegerAttribute indexStatus[CODE_SIZE];
    
    do
    {
        guess_prompter(userInput);
        if (!strcmp(EXIT, userInput))
        {
            return 0;
        }
        
        short userGuess = atoi(userInput);
        userGuessListed = int_to_list(userGuess);
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
                indexStatus[i].hint = 'y';
                // debug
                printf("Position #%d is a match!\n", i+1);
                    // shove this into a loop based on boolean list
                // endDebug
            }
            else
            {
                for (int j = 0; j < CODE_SIZE; j++)
                {
                    if (currentDigit == secretCode[j] && (!indexStatus[j].taken))
                    {
                        indexStatus[j].taken = true;
                        indexStatus[j].hint = 'o';
                    }
                }
            }
        }

        // debug (might become the display loop)
        for (int i = 0; i < CODE_SIZE; i++)
        {
            printf("[%d]: %d %c\n\n", indexStatus[i].digit, indexStatus[i].taken, indexStatus[i].hint);
        }
        // (implement here) general matches loop

    } while (true);
    
    free(userGuessListed);
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
        if (guess[i] == '\0' || guess[i] < 48 || guess[i] > 57)
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

// int digit_counter(int integer)
// {
//     int counter = 0;
//     for (; integer != 0; counter++)
//     {
//         integer /= 10;
//     }
//     return counter;
// }

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