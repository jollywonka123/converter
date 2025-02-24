#include "entrypoint.h"
#include "logic.h"


void doOperation(enum Actions action, AppContext *context, const char *newText, int inputSystem, int outputSystem) {
    switch (action) {
    case initialization:
        initialize(context, inputSystem, outputSystem);
        break;
    case textUpdating:
        updateInputText(context, newText);
        break;
    case checkInputs:
        checkTextCorrect(context, newText);
        break;
    case convert:
        convertToBase(context);
        break;
    default:
        break;
    }
}
