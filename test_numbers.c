#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "numbers.h"
void setUp(void) {}
void tearDown(void) {}

// Hilfsfunktion: prüft, ob ein Wert im Array vorkommt
static int contains(const unsigned int *arr, unsigned int len, unsigned int val) {
    for (unsigned int i = 0; i < len; ++i)
        if (arr[i] == val) return 1;
    return 0;
}

int main(void) {
    // Test 1: createNumbers gibt ein Array der richtigen Länge zurück
    unsigned int len = 10;
    unsigned int *numbers = createNumbers(len);
    assert(numbers != NULL);

    // Test 2: Es gibt genau ein Duplikat
    unsigned int duplicate = getDuplicate(numbers, len);
    assert(duplicate != 0);

    // Test 3: Das Duplikat kommt genau zweimal vor
    int count = 0;
    for (unsigned int i = 0; i < len; ++i)
        if (numbers[i] == duplicate) count++;
    assert(count == 2);

    // Test 4: Alle anderen Zahlen kommen nur einmal vor
    for (unsigned int i = 0; i < len; ++i) {
        if (numbers[i] == duplicate) continue;
        int c = 0;
        for (unsigned int j = 0; j < len; ++j)
            if (numbers[j] == numbers[i]) c++;
        assert(c == 1);
    }

    // Test 5: createNumbers gibt NULL bei ungültiger Länge
    assert(createNumbers(2) == NULL);
    assert(createNumbers(0) == NULL);
    assert(createNumbers(1001) == NULL);

    free(numbers);

    printf("Alle numbers-Tests bestanden.\n");
    return 0;
}