#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#define NUMBER_OF_SHOWN_HIGHSCORES 10

// When called, loads highscores from disk into static module variable. One highscore entry should consist of a player
// name and the achieved score.
void loadHighscores(const char *path);

// Adds current player name, time and number of shown numbers as a highscore entry. Returns the achieved score.
int addHighscore(const char *name, double timeInSeconds, unsigned int len);

// Show currently available highscores, but only up to NUMBER_OF_SHOWN_HIGHSCORES.
void showHighscores();

// Save currently available highscores to disk, but only up to NUMBER_OF_SHOWN_HIGHSCORES. One line should start with
// the player name and end with the score. Both values are separated by a semicolon (;). The scores should be organized
// in descending order, starting in the first line with the highest score and ending in the last line with the lowest
// score.
void saveHighscores(const char *path);

// Release all memory used to organize the highscores.
void clearHighscores();

#endif
