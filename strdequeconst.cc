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

namespace jnp1 {
    extern "C" unsigned long emptystrdeque() {
        if (debugMode)
            cerr << "emptystrdeque()" << endl;
        return 0;
    }
}
