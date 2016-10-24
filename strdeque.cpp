#include <iostream>
#include <deque>
#include <map>
#include <cassert>

using namespace std;

namespace {
#ifdef NDEBUG
    static const bool debugMode = false;
#else
    static const bool debugMode = true;
#endif
    
    using mapIterator = map<unsigned long, deque<string> >::iterator;
    map<unsigned long, deque<string> > dequeMap;
    
    unsigned long availableId = 0;
}

//@TODO
//	
//
//	-przerobić zgodnie z czytankami ifdef NDEBUG   - Mateusz (ZROBIONE)
//	-Pusta Kolejka									- Kacper
//	-Zmienne globalne w anonimowym namespace{}, albo jakiś inny sposób ukrycia przed światem -Stasiek	
//	-asercje (?)									- Kacper
//	-Extern "C"										- Stasiek
//	-Zamknąć wszystko w namespace jnp1{}			- Stasiek
//	-Zmienić nazwy plików na .cc					- Stasiek

unsigned long strdeque_new() {
    if(debugMode)
        cerr << "strdeque_new()" << endl;

    deque <string> kolejka;
    dequeMap.insert(make_pair(availableId, kolejka));

    if(debugMode)
        cerr << "strdeque_new: deque " << availableId << " created" << endl;

    return availableId++;
}

void strdeque_delete(unsigned long id) {
    if(debugMode)
        cerr << "strdeque_delete(" << id << ")" << endl;

    dequeMap.erase(id);

    if(debugMode)
        cerr << "strdeque_delete: " << "deque " << id << " deleted" << endl;
}

size_t strdeque_size(unsigned long id) {
    if(debugMode)
        cerr << "strdeque_size(" << id << ")" << endl;
    
    mapIterator it = dequeMap.find(id);
    
    if (it != dequeMap.end()) {
        if (debugMode) {
            cerr << "strdeque_size: " << "deque " << id << " contains "
                 << (dequeMap.at(id)).size() << " elements" << endl;
        }

        return (dequeMap.at(id)).size();
    }
    else if (debugMode)
        cerr << "strdeque_size: " << "deque " << id << " does not exist" << endl;

    return (size_t) 0;
}

void strdeque_insert_at(unsigned long id, size_t pos, const char* value) {
    if(debugMode) {
        cerr << "strdeque_insert_at(" << id << ", " << pos << ", ";

        if (value == NULL)
            cerr << "NULL" << ")" << endl;
        else
            cerr << "\"" << value << "\"" << ")" << endl;
    }

    mapIterator it = dequeMap.find(id);
    if (it != dequeMap.end()) {
        if (value != NULL) {
            if (pos <= strdeque_size(id)) {
                (dequeMap.at(id)).insert((dequeMap.at(id)).begin() + pos, string(value));
                
                if(debugMode) {
                    cerr << "strdeque_insert_at: " << "deque " << id << ", element \"" << value;
                    cerr << "\" inserted at " << pos << endl;
                }
            }
            else {
                (dequeMap.at(id)).push_back(string(value));
                
                if(debugMode) {
                    cerr << "strdeque_insert_at: " << "deque " << id << ", element \"" << value;
                    cerr << "\" inserted at the end" << endl;
                }
            }
        }
        else if(debugMode)
            cerr << "strdeque_insert_at: " << "value is NULL" << endl;
    }
    else if(debugMode)
        cerr << "strdeque_insert_at: " << "deque " << id << " does not exist" << endl;
}

void strdeque_remove_at(unsigned long id, size_t pos) {
    if(debugMode)
        cerr << "strdeque_remove_at(" << id << ", " << pos <<  ")" << endl;
    
    mapIterator it = dequeMap.find(id);
    if (it != dequeMap.end()) {
        if (pos < strdeque_size(id)) {
            (dequeMap.at(id)).erase((dequeMap.at(id)).begin() + pos);

            if(debugMode) {
                cerr << "strdeque_remove_at: " << "deque " << id << ", element at "
                     << pos <<  " removed" << endl;
            }
        }
        else if(debugMode) {
            cerr << "strdeque_remove_at: " << "deque " << id << ", position "
                 << pos <<  " is greater than size" << endl;
        }
    }
    else if(debugMode)
        cerr << "strdeque_remove_at: " << "deque " << id << " does not exist" << endl;
}

const char* strdeque_get_at(unsigned long id, size_t pos) {
    if(debugMode)
        cerr << "strdeque_get_at(" << id << ", " << pos <<  ")" << endl;
    
    mapIterator it = dequeMap.find(id);
    if (it != dequeMap.end()) {
        if (pos < strdeque_size(id)) {
            if(debugMode) {
                cerr << "strdeque_get_at: " << "deque " << id << ", element at " << pos;
                cerr << " is \"" << (dequeMap.at(id)).at(pos).c_str() << "\"" << endl;
            }

            return (dequeMap.at(id)).at(pos).c_str();
        }
        else if(debugMode) {
            cerr << "strdeque_get_at: " << "deque " << id << ", position "
                 << pos << " is greater than size" << endl;
        }
    }
    else if(debugMode)
        cerr << "strdeque_get_at: " << "deque " << id << " does not exist" << endl;

    return NULL;
}

void strdeque_clear(unsigned long id) {
    if(debugMode)
        cerr << "strdeque_clear(" << id << ")" << endl;

    mapIterator it = dequeMap.find(id);
    if (it != dequeMap.end()) {
        (dequeMap.at(id)).clear();
        
        if(debugMode)
            cerr << "strdeque_clear: " << "deque " << id << " cleared" << endl;
    }
    else if(debugMode)
        cerr << "strdeque_clear: " << "deque " << id << " does not exist" << endl;
}

int strdeque_comp(unsigned long id1, unsigned long id2) {
    if(debugMode)
        cerr << "strdeque_comp(" << id1 << ", " << id2 <<  ")" << endl;

    mapIterator it1 = dequeMap.find(id1);
    mapIterator it2 = dequeMap.find(id2);
    int result;

    if (it1 == dequeMap.end() && it2 == dequeMap.end()) {
        if(debugMode)
            cerr << "strdeque_com: deque " << id1 << " and deque " << id2 << " do not exist" << endl;
        return 0;
    }
    else if (it2 == dequeMap.end() ) {
        if(debugMode)
            cerr << "strdeque_comp: deque " << id2 << " does not exist" << endl;
        return 1;
    }
    else if (it1 == dequeMap.end() ) {
        if(debugMode)
            cerr << "strdeque_comp: deque " << id1 << " does not exist" << endl;
        return -1;
    }
    else {
        if (dequeMap[id1] < dequeMap[id2]) {
            result = -1;
        }
        else if (dequeMap[id1] == dequeMap[id2]) {
            result = 0;
        }
        else {
            result = 1;
        }
        
        if (debugMode) {
            cerr << "strdeque_comp: result of comparing deque " << id1
                 << " to deque " << id2 << " is " << result << endl;
        }
        return result;
    }
}
