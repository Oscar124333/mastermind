#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

// Constants
const int testCode[] = {1, 3, 3, 5};
const int SIZEOFCODE = 4;
const char SPECIAL_NULL = '#';

// Prototypes
int *int_to_list(int original);
bool good_guess(char *guess);
int digit_counter(int integer);
int inputHandler(char *variable);
void inputPrompt(char *variable, char *prompt);

int main(void)
{    
    // Intro
    printf("\n*****\nWelcome to Mastermindle!\n*****\n\n");

    char userInput[5] = {'\0'};
    inputPrompt(userInput, "Please enter a guess for the secret code. It can only be 4 digits long.");

    int userGuess = atoi(userInput);

    printf("%d\n", userGuess);

    int *f_userGuess = int_to_list(userGuess);

    // debug
    for (int i = 0; i < SIZEOFCODE; i++)
    {
        printf("%d\n", f_userGuess[i]);
    }
    // end

    return 0;
}

int *int_to_list(int original)
{
    int *ptr = malloc(sizeof(int) * SIZEOFCODE);

    for (int i = 0, divisor = 1000; i < SIZEOFCODE; i++, divisor/=10)
    {
        ptr[i] = (original / divisor) % 10;
    }

    return ptr;
}

bool good_guess(char *guess)
{
    if (guess[4] != SPECIAL_NULL)
    {
        return false;
    }
    
    for (int i = 0; i != SPECIAL_NULL; i++)
    {
        // how to differentiate the end vs in the middle
    }
    return true;
}

int digit_counter(int integer)
{
    int counter = 0;
    for (; integer != 0; counter++)
    {
        integer /= 10;
    }
    return counter;
}

int inputHandler(char *variable)
{
    int status = 0;
    int ch;
    status = scanf("%s", variable);
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