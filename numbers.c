#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "numbers.h"
#include "bintree.h"

//TODO: getDuplicate und createNumbers implementieren
/*  *   * Erzeugen eines Arrays mit der vom Nutzer eingegebenen Anzahl an Zufallszahlen.
  * Sicherstellen, dass beim Befüllen keine Duplikate entstehen.
  * Duplizieren eines zufälligen Eintrags im Array.
  * in `getDuplicate()`: Sortieren des Arrays und Erkennen der doppelten Zahl durch Vergleich benachbarter Elemente. */

// Returns len random numbers between 1 and 2x len in random order which are all different, except for two entries.
// Returns NULL on errors. Use your implementation of the binary search tree to check for possible duplicates while
// creating random numbers.
unsigned int *createNumbers(unsigned int len)
{
    if (len < 3 || len > 1000) return NULL;

    unsigned int *numbers = malloc(len * sizeof(unsigned int));
    if (!numbers) return NULL;

    TreeNode *tree = NULL;
    unsigned int range = 2 * len;
    unsigned int count = 0;

    srand((unsigned int)time(NULL));

    // Generate unique random numbers
    while (count < len - 1) {
        unsigned int num = 1 + rand() % range;
        int isDup = 0;
        tree = addToTree(tree, &num, sizeof(num), 
            [](const void *a, const void *b) {
                unsigned int ua = *(const unsigned int *)a;
                unsigned int ub = *(const unsigned int *)b;
                return (ua > ub) - (ua < ub);
            }, &isDup);
        if (!isDup) {
            numbers[count++] = num;
        }
    }

    // Pick one of the already chosen numbers to duplicate
    unsigned int dupIdx = rand() % (len - 1);
    numbers[count++] = numbers[dupIdx];

    // Optional: shuffle array for random order
    for (unsigned int i = len - 1; i > 0; i--) {
        unsigned int j = rand() % (i + 1);
        unsigned int tmp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = tmp;
    }

    clearTree(tree);
    return numbers;
}

// Returns only the only number in numbers which is present twice. Returns zero on errors.
unsigned int getDuplicate(const unsigned int numbers[], unsigned int len)
{

}