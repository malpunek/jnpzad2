#include <iostream>
#include "strdequeconst.h"

using namespace std;

#ifndef NDEBUG
unsigned long emptystrdeque() {
    cerr << "emptystrdeque()" << endl;
    return 0;
}
#else
unsigned long emptystrdeque() {
    return 0;
}
#endif
