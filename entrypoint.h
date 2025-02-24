#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "appcontext.h"
#include "logic.h"


enum Actions {
    textUpdating,
    initialization,
    checkInputs,
    convert,
};


void doOperation(enum Actions action, AppContext *context, const char *newText, int inputSystem, int outputSystem);


#endif // ENTRYPOINT_H
