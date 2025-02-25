#include "logic.h"
#include <string.h>
#include <stdlib.h>
#include "my_string.h"
#include <stdio.h>
#include <math.h>

const char allAllowedSigns[] = "-0123456789ABCDEF";

void updateInputText(AppContext *context, const char *newText) {
    checkTextCorrect(context, newText);
    strncpy(context->input.theNumber,  newText, MAXSIZE+1);
    if (context->Error == inputSizeError) context->input.theNumber[MAXSIZE] = '\0';
}


char* createAdaptiveAlphabet(AppContext *context, const char* oldAlphabet) {
    char* newString = NULL;
    if (oldAlphabet != NULL) {
        int numSystem = context->input.numSystem;
        createNewStr(&newString, numSystem+2, &context->Error);
        if (context->Error != memmoryError) {
            strncpy(newString, oldAlphabet, numSystem + 1);
            newString[numSystem+1] = '\0';
        }
    }
    return newString;
}

int isMoreThenMaxSize(AppContext *context, const char* newText) {
    int maxSize = MAXSIZE;
    int returnCode = incorrect;
    if (newText != NULL)
    {
        int lenth  = strlen(newText);
        int isMinus = newText[0] == '-' ? 1 : 0;
        if (!isMinus)
            maxSize--;
        if (lenth > (maxSize / (int)ceil(log2(context->input.numSystem))))
            returnCode = correct;
    }
    return returnCode;
}

void checkTextCorrect(AppContext *context, const char *newText) {
    int status = noError;
    if (newText != NULL)
    {
        char* newAlphabet = createAdaptiveAlphabet(context, allAllowedSigns);
        if (isMoreThenMaxSize(context, newText) == correct)
            status = inputSizeError;
        else if (isZerosInIncorrectPosition(newText) == correct || isMinusInIncorrectPos(newText) == correct || isSubsetAlphabet(newText, newAlphabet) == incorrect)
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
        char *buffer;
        createNewStr(&buffer, MAXSIZE, &context->Error);
        int decimal = getDecimal(context);
        int i = 0;
        int isNegative = incorrect;
        if (decimal < 0) {
            isNegative = correct;
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
        if (isNegative == correct) {
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

