#include <iostream>
#include "strdequeconst.h"

using namespace std;

namespace {
#ifdef NDEBUG
    static const bool debugMode = false;
#else
    static const bool debugMode = true;
#endif
}

unsigned long emptystrdeque() {
    if (debugMode)
        cerr << "emptystrdeque()" << endl;
    return 0;
}
