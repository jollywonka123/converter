#ifndef APPCONTEXT_H
#define APPCONTEXT_H
#define MAXSIZE 32

struct InputData {
    int numSystem;
    char theNumber[MAXSIZE+1];
};

struct OutputData {
    int numSystem;
    char outputNumber[MAXSIZE+1];
};

typedef struct {
    struct InputData input;
    struct OutputData output;
    int Error;
} AppContext;

#endif // APPCONTEXT_H
