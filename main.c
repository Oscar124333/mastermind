#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

// Constants
const int testCode[] = {1, 3, 3, 5};
const int SIZEOFCODE = 4;

// Prototypes
int *int_to_list(int original);
int inputHandler(int *variable);
void inputPrompt(int *variable, char *prompt);

int main(void)
{    
    // Intro
    printf("\n*****\nWelcome to Mastermindle!\n*****\n");

    int userInput = 0;
    inputPrompt(&userInput, "Please enter a guess for the secret code. It can only be 4 digits long.");

    int *userGuess = int_to_list(userInput);

    for (int i = 0; i < SIZEOFCODE; i++)
    {
        printf("%d\n", userGuess[i]);
    }

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


int inputHandler(int *variable)
{
    int status = 0;
    int ch;
    status = scanf("%d", variable);
    while ((ch = getchar()) != '\n' && ch != EOF);
    return status;
}

void inputPrompt(int *variable, char *prompt)
{
    do
    {
        printf("%s\n==> ", prompt);
    } while (inputHandler(variable) != 1);
    return;
}