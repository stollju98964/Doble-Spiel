#ifndef NUMBERS_H
#define NUMBERS_H

// Returns len random numbers between 1 and 2x len in random order which are all different, except for two entries.
// Returns NULL on errors. Use your implementation of the binary search tree to check for possible duplicates while
// creating random numbers.
unsigned int *createNumbers(unsigned int len);

// Returns only the only number in numbers which is present twice. Returns zero on errors.
unsigned int getDuplicate(const unsigned int *numbers, unsigned int len);

#endif