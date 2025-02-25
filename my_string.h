#ifndef MY_STRING_H
#define MY_STRING_H
#include <stdlib.h>

void reverseString(char * str);
int isSubsetAlphabet(const char *str1, const char *alphabet);
int isZerosInIncorrectPosition(const char* newText);
int isMinusInIncorrectPos(const char* newText);
void createNewStr(char** buffer, size_t size, int* errorFlag);

#endif // MY_STRING_H
