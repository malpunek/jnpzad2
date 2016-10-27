#include <iostream>
#include "strdequeconst.h"
#include "strdeque.h"

using namespace std;

namespace {
    const bool get_debug(){
    #ifdef NDEBUG
        static const bool debugMode = false;
    #else
        static const bool debugMode = true;
    #endif
        return debugMode;
    }
}

namespace jnp1 {
    extern "C" unsigned long emptystrdeque() {
        if (get_debug())
            cerr << "emptystrdeque()" << endl;
        static const unsigned long empty_deque_id = strdeque_new();
        return empty_deque_id;
    }
}
