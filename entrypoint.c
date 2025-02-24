#include "entrypoint.h"
#include "logic.h"
#include <stdarg.h>


void doOperation(enum Actions action, AppContext *context, ...) {
    va_list args;
    va_start(args, context);
    switch (action) {
    case initialization: {
        int inputSystem = va_arg(args, int);
        int outputSystem = va_arg(args, int);
        initialize(context, inputSystem, outputSystem);
    }
        break;
    case textUpdating: {
        char* newText = va_arg(args, char*);
        updateInputText(context, newText);
    }
        break;
    case checkInputs: {
        char* newText1 = va_arg(args, char*);
        checkTextCorrect(context, newText1);
    }
        break;
    case convert:
        convertToBase(context);
        break;
    default:
        break;
    }
    va_end(args);
}
