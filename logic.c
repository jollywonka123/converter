#include "logic.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>

const char allAllowedSigns[] = "-0123456789ABCDEF";

void updateInputText(AppContext *context, const char *newText) {
    checkTextCorrect(context, newText);
    strncpy(context->input.theNumber,  newText, MAXSIZE+1);
    if (context->Error == inputSizeError) context->input.theNumber[MAXSIZE] = '\0';
}


int isSubsetAlphabet(const char *str1, const char *alphabet) {
    while (*str1) {
        if (!strchr(alphabet, toupper(*str1))) {
            return 0;
        }
        ++str1;
    }
    return 1;
}

//0 - correct, -1 - no minuses, 1 - incorrect
int isMinusInIncorrectPos(const char* newText) {
    int returnCode = 0;
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
                returnCode = 1;
            else if (newText[0] != '-')
                returnCode = 1;
        }
        else returnCode = -1;
    }
    return returnCode;
}


int isZerosInIncorrectPosition(const char* newText) {
    int returnCode = 0;
    if (newText != NULL)
    {
        int minusStatus = isMinusInIncorrectPos(newText);
        if ((minusStatus == 0) && (newText[1] == '0'))
            returnCode = 1;
        else if ((minusStatus == -1) && (strlen(newText) >= 2) && (newText[0] == '0'))
            returnCode = 1;
    }
    return returnCode;
}


char* createAdaptiveAlphabet(AppContext *context, const char* oldAlphabet) {
    char* newString = NULL;
    if (oldAlphabet != NULL) {
        int numSystem = context->input.numSystem;
        newString = (char*)malloc((numSystem+2) * sizeof(char));
        if (newString != NULL) {
            strncpy(newString, oldAlphabet, numSystem + 1);
            newString[numSystem+1] = '\0';
        }
        else context->Error = memmoryError;
    }
    return newString;
}

int isMoreThenMaxSize(AppContext *context, const char* newText) {
    int maxSize = MAXSIZE;
    int returnCode = 0;
    if (newText != NULL)
    {
        int lenth  = strlen(newText);
        int isMinus = newText[0] == '-' ? 1 : 0;
        if (!isMinus)
            maxSize--;
        if (lenth > (maxSize / (int)ceil(log2(context->input.numSystem))))
            returnCode = 1;
    }
    return returnCode;
}

void checkTextCorrect(AppContext *context, const char *newText) {
    int status = noError;
    if (newText != NULL)
    {
        char* newAlphabet = createAdaptiveAlphabet(context, allAllowedSigns);
        if (isMoreThenMaxSize(context, newText) == 1)
            status = inputSizeError;
        else if (isZerosInIncorrectPosition(newText) == 1 || isMinusInIncorrectPos(newText) == 1 || isSubsetAlphabet(newText, newAlphabet) == 0)
            status = wrongInpError;
        free(newAlphabet);
    }
    if (context->Error != status)
        context->Error = status;
}

void initialize(AppContext *context, int inputSystem, int outputSystem) {
    context->input.numSystem = inputSystem;
    context->output.numSystem = outputSystem;
    context->input.theNumber[0] = '\0';
    context->output.outputNumber[0] = '\0';
    context->Error = noError;
}

int getDecimal(AppContext *context) {
    int returnValue = 0;
    if ((context->input.theNumber[0] != '\0') && (context->Error == noError)) {
        returnValue = strtol(context->input.theNumber, NULL, context->input.numSystem);
    }
    return returnValue;
}

void convertToBase(AppContext *context) {
    if ((context->input.theNumber[0] != '\0') && (context->Error == noError)) {
        char* result = context->output.outputNumber;
        int* const base = &context->output.numSystem;
        char *buffer = (char*)malloc(MAXSIZE * sizeof(char));
        int decimal = getDecimal(context);
        int i = 0;
        int isNegative = 0;
        if (decimal < 0) {
            isNegative = 1;
            decimal = abs(decimal);
        }
        if (decimal == 0) {
            buffer[i++] = '0';
            buffer[i++] = '\0';
        }
        while (decimal > 0) {
            int remainder = decimal % *base;
            buffer[i] = allAllowedSigns[1 + remainder];
            decimal /= *base;
            i++;
        }
        if (isNegative) {
            buffer[i] = '-';
            i++;
        }
        buffer[i] = '\0';
        reverseString(buffer);
        if (buffer[0] != '\0') strncpy(result, buffer, MAXSIZE);
        else context->Error = convError;
        free(buffer);
    }
}

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



