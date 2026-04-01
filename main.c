#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Constants
const int testCode[] = {1, 3, 3, 7};
const int CODE_SIZE = 4;
const int NULL_TERM_SPACE = 1;

// Prototypes
int *int_to_list(int original);
bool good_guess(char *guess);
unsigned int nano_seed(void)
int basic_RNG(unsigned int seed, int rangeStart, int rangeEnd)
// int digit_counter(int integer);
int inputHandler(char *variable);
void inputPrompt(char *variable, char *prompt);

int main(void)
{    
    // Intro
    printf("\n*****\nWelcome to Mastermindle!\n*****\n\n");
    // Index 4 to check if more than 4 digits entered, Index 5 for `scanf()`s automatic newline.
    char userInput[6] = {'\0'};

    do
    {
        inputPrompt(userInput, "Please enter a guess for the secret code. It can only be 4 digits long.");
    } while (!good_guess(userInput));

    short userGuess = atoi(userInput);

    int *f_userGuess = int_to_list(userGuess);



    return 0;
}

int *int_to_list(int original)
{
    int *ptr = malloc(sizeof(int) * CODE_SIZE);

    for (int i = 0, divisor = 1000; i < CODE_SIZE; i++, divisor/=10)
    {
        ptr[i] = (original / divisor) % 10;
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