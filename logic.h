#ifndef LOGIC_H
#define LOGIC_H

#include "appcontext.h"

enum Errors {
    noError,
    wrongInpError,
    memmoryError,
    inputSizeError,
    convError,
};

enum numSystems {
    binary = 2,
    quaternary = 4,
    octal = 8,
    decimal = 10,
    hexadecimal = 16,
};

extern const char allAllowedSigns[];

int isMinusInIncorrectPos(const char* newText);
int isZerosInIncorrectPosition(const char* newText);
int isSubsetAlphabet(const char *str1, const char *alphabet);
char* createAdaptiveAlphabet(AppContext *context, const char* oldAlphabet);
void checkTextCorrect(AppContext *context, const char *newText);
int isMoreThenMaxSize(AppContext *context, const char* newText);
void updateInputText(AppContext *context, const char *newText);
void initialize(AppContext *context, int inputSystem, int outputSystem);
int getDecimal(AppContext *context);
void convertToBase(AppContext *context);
void reverseString(char * str);

#endif // LOGIC_H
