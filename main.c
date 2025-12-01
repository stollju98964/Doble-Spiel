#include <stdlib.h>
#include <stdio.h>
#include "numbers.h"
#include "timer.h"
#include "highscore.h"

// Read an unsigned integer from stdin with prompt (retries until valid).
int inputNumber(const char *promptText)
{
    unsigned int number;
    int numberOfInputs = 0;

    while(numberOfInputs != 1)
    {
        printf("%s", promptText);
        numberOfInputs = scanf("%u", &number);
        while(getchar() != '\n') {} // clear input buffer
    }

    return number;
}

// Print an array of numbers.
void showNumbers(const unsigned int *numbers, unsigned int len)
{
    if(numbers != NULL)
    {
        printf("Numbers:");

        for(int i = 0; i < len; i++)
            printf(" %5d", numbers[i]);

        printf("\n");
    }
}

// Main game loop: generate numbers, ask user for duplicate, measure time, update highscores.
int main(int argc, char *argv[])
{
    int exitCode = EXIT_FAILURE;

    if(argc != 2)
    {
        fprintf(stderr, "Usage: %s <player name>\n", argv[0]);
        exitCode = EXIT_FAILURE;
    }
    else
    {
        const char *highscorePath = "highscores.txt";
        const char *playerName = argv[1];
        unsigned int *numbers = NULL;
        unsigned int duplicate = 0;
        double measuredSeconds;
        unsigned int userInput;
        unsigned int numberOfElements = 0;

        // ask until valid number of elements (3..1000)
        while(numberOfElements < 3 || numberOfElements > 1000)
            numberOfElements = inputNumber("Wie viele Zahlen sollen gezeigt werden: ");

        // create numbers and show them
        numbers = createNumbers(numberOfElements);
        showNumbers(numbers, numberOfElements);

        // measure time while user guesses the duplicate
        startTimer();
        userInput = inputNumber("Welche Zahl kommt doppelt vor: ");
        measuredSeconds = stopTimer();

        duplicate = getDuplicate(numbers, numberOfElements);

        // check result and update highscores
        if(userInput == duplicate)
        {
            int score = addHighscore(playerName, measuredSeconds, numberOfElements);
            printf("Sie haben die korrekte Zahl in %.6lf Sekunde(n) gefunden und %u Punkte erzielt.\n", measuredSeconds, score);
        }
        else
            printf("Leider ist %u nicht korrekt. Richtig waere %u gewesen.\n", userInput, duplicate);

        loadHighscores(highscorePath);
        showHighscores();
        saveHighscores(highscorePath);
        clearHighscores();

        exitCode = EXIT_SUCCESS;
    }

    return exitCode;
}