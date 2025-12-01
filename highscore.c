#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "highscore.h"
#include "bintree.h"

#define MAX_LINE_LEN 100
#define MAX_PLAYER_NAME_LEN 20

typedef struct
{
    char name[MAX_PLAYER_NAME_LEN];
    int score;
} HighscoreEntry;

static TreeNode *highscoreTree = NULL;

// Compare two highscore entries by score (descending), then by name (ascending).
static int compareHighscoreEntries(const void *arg1, const void *arg2)
{
    const HighscoreEntry *entry1 = (const HighscoreEntry *)arg1;
    const HighscoreEntry *entry2 = (const HighscoreEntry *)arg2;

    int result = entry2->score - entry1->score;

    if(result == 0)
        result = strcmp(entry1->name, entry2->name);

    return result;
}

// Create a new highscore entry from name and score.
static HighscoreEntry createHighscoreEntry(const char *name, int score)
{
    HighscoreEntry entry = {"", score};

    if(name != NULL)
    {
        strncpy(entry.name, name, MAX_PLAYER_NAME_LEN);
        entry.name[MAX_PLAYER_NAME_LEN-1] = '\0';
    }

    return entry;
}

// Calculate score based on time used and number of shown numbers.
static int calculateScore(double timeInSeconds, unsigned int len)
{
    return  (1000.0 - timeInSeconds) * len;
}

// Load highscores from file into memory.
void loadHighscores(const char *path)
{
    FILE *file = fopen(path, "r");

    if(file != NULL)
    {
        char buffer[MAX_LINE_LEN+1];

        while(fgets(buffer, MAX_LINE_LEN+1, file) != NULL)
        {
            char *name = strtok(buffer, ";\n");
            char *scoreStr = strtok(NULL, ";\n");

            if(name != NULL && scoreStr != NULL)
            {
                HighscoreEntry entry = createHighscoreEntry(name, strtol(scoreStr, NULL, 10));
                highscoreTree = addToTree(highscoreTree, &entry, sizeof(entry), compareHighscoreEntries, NULL);
            }
        }

        fclose(file);
    }
}

// Add a new highscore entry and return the calculated score.
int addHighscore(const char *name, double timeInSeconds, unsigned int len)
{
    HighscoreEntry entry = createHighscoreEntry(name, calculateScore(timeInSeconds, len));
    highscoreTree = addToTree(highscoreTree, &entry, sizeof(entry), compareHighscoreEntries, NULL);

    return entry.score;
}

// Print highscores (up to NUMBER_OF_SHOWN_HIGHSCORES) in a formatted table.
void showHighscores()
{
    const char *blanks = "                                                                                                                        ";
    const char *stripes = "------------------------------------------------------------------------------------------------------------------------";
    const char *header = "H I G H S C O R E S";
    const int lineWidth = MAX_PLAYER_NAME_LEN + MAX_PLAYER_NAME_LEN + 5;

    int blankSpace = (int)(lineWidth - strlen(header)) / 2;

    HighscoreEntry *entry = nextTreeData(highscoreTree);

    printf("+%*.*s+\n", lineWidth, lineWidth, stripes);
    printf("|%*.*s%s%*.*s|\n", blankSpace, blankSpace, blanks, header, blankSpace, blankSpace, blanks);
    printf("+%*.*s+\n", lineWidth, lineWidth, stripes);

    for(int i = 0; i < NUMBER_OF_SHOWN_HIGHSCORES && entry != NULL; i++)
    {
        printf("| %-*s | %*d |\n", MAX_PLAYER_NAME_LEN, entry->name, MAX_PLAYER_NAME_LEN, entry->score);
        printf("+%*.*s+\n", lineWidth, lineWidth, stripes);
        entry = nextTreeData(NULL);
    }
}

// Save highscores to file (up to NUMBER_OF_SHOWN_HIGHSCORES).
void saveHighscores(const char *path)
{
    FILE *file = fopen(path, "w");

    if(file != NULL)
    {
        HighscoreEntry *entry = nextTreeData(highscoreTree);

        for(int i = 0; i < NUMBER_OF_SHOWN_HIGHSCORES && entry != NULL; i++)
        {
            fprintf(file, "%s;%d\n", entry->name, entry->score);
            entry = nextTreeData(NULL);
        }

        fclose(file);
    }
}

// Free all memory used for highscores.
void clearHighscores()
{
    clearTree(highscoreTree);
    highscoreTree = NULL;
}