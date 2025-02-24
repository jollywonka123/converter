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


void doOperation(enum Actions action, AppContext *context, ...);


#endif // ENTRYPOINT_H
