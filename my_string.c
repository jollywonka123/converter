#include <string.h>
#include <ctype.h>
#include "my_string.h"
#include "logic.h"

void reverseString(char * str) {
    int len = strlen(str);
    int left = 0, right = len - 1;
    while (left < right) {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}

int isSubsetAlphabet(const char *str1, const char *alphabet) {
    int returnValue = correct;
    while (*str1 && (returnValue == correct)) {
        if (!strchr(alphabet, toupper(*str1))) {
            returnValue = incorrect;
        }
        ++str1;
    }
    return returnValue;
}

int isZerosInIncorrectPosition(const char* newText) {
    int returnCode = incorrect;
    if (newText != NULL)
    {
        int isMinIncorrect = isMinusInIncorrectPos(newText);
        if ((isMinIncorrect == incorrect) && (newText[1] == '0'))
            returnCode = correct;
        else if ((isMinIncorrect == notFound) && (strlen(newText) >= 2) && (newText[0] == '0'))
            returnCode = correct;
    }
    return returnCode;
}


int isMinusInIncorrectPos(const char* newText) {
    int returnCode = incorrect;
    if (newText != NULL)
    {
        int minusCount = 0;
        int pointer = 0;
        while (newText[pointer]) {
            if (newText[pointer] == '-')
                minusCount++;
            pointer++;
        }
        if (minusCount != 0) {
            if (minusCount > 1)
                returnCode = correct;
            else if (newText[0] != '-')
                returnCode = correct;
        }
        else returnCode = notFound;
    }
    return returnCode;
}

void createNewStr(char** buffer, size_t size, int* errorFlag) {
    if (errorFlag != NULL)
    {
        *buffer = (char*)malloc(size * sizeof(char));
        if (*buffer == NULL) *errorFlag = memmoryError;
    }
}
