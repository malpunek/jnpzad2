#include <iostream>
#include <deque>
#include <map>
#include <cassert>
#include <vector>

using namespace std;

namespace {
#ifdef NDEBUG
    static const bool debugMode = false;
#else
    static const bool debugMode = true;
#endif
    
    using mapIterator = map<unsigned long, deque<string> >::iterator;
    map<unsigned long, deque<string> > dequeMap;
    
    unsigned long availableId = 1;
    static const int emptyDequeId = 0;
    
    static string printId(unsigned long id) {
        if (id == emptyDequeId)
            return "the Empty Deque";
        else
            return to_string(id);
    }
    
    static int checkInsertAt(unsigned long id, size_t pos, const char* value) {
        if(debugMode) {
            cerr << "strdeque_insert_at(" << printId(id) << ", " << pos << ", ";
            
            if (value == NULL)
                cerr << "NULL" << ")" << endl;
            else
                cerr << "\"" << value << "\"" << ")" << endl;
        }
        
        if (id == emptyDequeId) {
            if (debugMode)
                cerr << "strdeque_insert_at: attempt to insert into the Empty Deque" << endl;
            return 1;
        }
        
        if (value == NULL) {
            if (debugMode)
                cerr << "strdeque_insert_at: attempt to insert NULL into a deque " << id << endl;
            return 1;
        }
        
        return 0;
    }
    
    static int compEmptyDeque(unsigned long id1, unsigned long id2) {
        if (id1 == emptyDequeId) {
            if (id2 == emptyDequeId) {
                if (debugMode)
                    cerr << "strdeque_comp: result of comparing the Empty Deque to the Empty Deque is 0" << endl;
                return 0;
            }
            else {
                if (debugMode)
                    cerr << "strdeque_comp: result of comparing the Empty Deque to deque " << id2 << " is 1" << endl;
                return 1;
            }
        }
        else {
            if (debugMode)
                cerr << "strdeque_comp: result of comparing deque " << id1 << " to the Empty Deque is -1" << endl;
            return -1;
        }
    }
    
    static int compNotExistingDeque(mapIterator it1, mapIterator it2, unsigned long id1, unsigned long id2) {
        int result;
        
        if (it1 == dequeMap.end() && it2 == dequeMap.end()) {
            if(debugMode)
                cerr << "strdeque_com: deque " << id1 << " and deque " << id2 << " do not exist" << endl;
            result = 0;
        }
        else if (it2 == dequeMap.end() ) {
            if(debugMode)
                cerr << "strdeque_comp: deque " << id2 << " does not exist" << endl;
            result = 1;
        }
        else {
            if(debugMode)
                cerr << "strdeque_comp: deque " << id1 << " does not exist" << endl;
            result = -1;
        }
        
        if (debugMode) {
            cerr << "strdeque_comp: result of comparing deque " << id1
            << " to deque " << id2 << " is " << result << endl;
        }
        
        return result;
    }
    
    static int compExistingDeques(unsigned long id1, unsigned long id2) {
        int result;
        
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

namespace jnp1 {
    extern "C" unsigned long strdeque_new() {
        if(debugMode)
            cerr << "strdeque_new()" << endl;
        
        deque <string> kolejka;
        dequeMap.insert(make_pair(availableId, kolejka));
        
        if(debugMode)
            cerr << "strdeque_new: deque " << availableId << " created" << endl;
        
        return availableId++;
    }
    
    extern "C" void strdeque_delete(unsigned long id) {
        if(debugMode)
            cerr << "strdeque_delete(" << printId(id) << ")" << endl;
        
        if (id == emptyDequeId) {
            if (debugMode)
                cerr << "strdeque_delete: attempt to remove the Empty Deque" << endl;
            return;
        }
        
        mapIterator it = dequeMap.find(id);
        
        if (it != dequeMap.end()) {
            dequeMap.erase(it);
            
            if(debugMode)
                cerr << "strdeque_delete: " << id << " deleted" << endl;
        }
        else if (debugMode)
            cerr << "strdeque_size: " << "deque " << id << " does not exist" << endl;
    }
    
    extern "C" size_t strdeque_size(unsigned long id) {
        if(debugMode)
            cerr << "strdeque_size(" << printId(id) << ")" << endl;
        
        if (id == emptyDequeId) {
            if (debugMode)
                cerr << "strdeque_size: the Empty Deque contains 0 elements" << endl;
            return (size_t) 0;
        }
        
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
    
    extern "C" void strdeque_insert_at(unsigned long id, size_t pos, const char* value) {
        if (checkInsertAt(id, pos, value) == 1)
            return;
        
        mapIterator it = dequeMap.find(id);
        
        if (it != dequeMap.end()) {
            if (pos <= strdeque_size(id)) {
                (dequeMap.at(id)).insert((dequeMap.at(id)).begin() + pos, string(value));
                
                if(debugMode) {
                    cerr << "strdeque_insert_at: " << "deque " << id << ", element \"" << value
                    << "\" inserted at " << pos << endl;
                }
            }
            else {
                (dequeMap.at(id)).push_back(string(value));
                
                if(debugMode) {
                    cerr << "strdeque_insert_at: " << "deque " << id << ", element \"" << value
                    << "\" inserted at the end" << endl;
                }
            }
        }
        else if(debugMode)
            cerr << "strdeque_insert_at: " << "deque " << id << " does not exist" << endl;
    }
    
    extern "C" void strdeque_remove_at(unsigned long id, size_t pos) {
        if(debugMode)
            cerr << "strdeque_remove_at(" << printId(id) << ", " << pos <<  ")" << endl;
        
        if (id == emptyDequeId) {
            if (debugMode)
                cerr << "strdeque_remove_at: attempt to remove from the Empty Deque" << endl;
            return;
        }
        
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
    
    extern "C" const char* strdeque_get_at(unsigned long id, size_t pos) {
        if(debugMode)
            cerr << "strdeque_get_at(" << printId(id) << ", " << pos <<  ")" << endl;
        
        if (id == emptyDequeId) {
            if (debugMode)
                cerr << "the Empty Deque does not contain an element at " << pos << endl;
            return NULL;
        }
        
        mapIterator it = dequeMap.find(id);
        if (it != dequeMap.end()) {
            if (pos < strdeque_size(id)) {
                if(debugMode) {
                    cerr << "strdeque_get_at: " << "deque " << id << ", element at " << pos
                    << " is \"" << (dequeMap.at(id)).at(pos).c_str() << "\"" << endl;
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
    
    extern "C" void strdeque_clear(unsigned long id) {
        if(debugMode)
            cerr << "strdeque_clear(" << printId(id) << ")" << endl;
        
        if (id == emptyDequeId) {
            if (debugMode)
                cerr << "attempt to clear the Empty Deque" << endl;
            return;
        }
        
        mapIterator it = dequeMap.find(id);
        if (it != dequeMap.end()) {
            (dequeMap.at(id)).clear();
            
            if(debugMode)
                cerr << "strdeque_clear: " << "deque " << id << " cleared" << endl;
        }
        else if(debugMode)
            cerr << "strdeque_clear: " << "deque " << id << " does not exist" << endl;
    }
    
    extern "C" int strdeque_comp(unsigned long id1, unsigned long id2) {
        if(debugMode)
            cerr << "strdeque_comp(" << printId(id1) << ", " << printId(id2) <<  ")" << endl;
        
        if (id1 == emptyDequeId || id2 == emptyDequeId)
            return compEmptyDeque(id1, id2);
        
        mapIterator it1 = dequeMap.find(id1);
        mapIterator it2 = dequeMap.find(id2);
        
        if (it1 == dequeMap.end() || it2 == dequeMap.end())
            return compNotExistingDeque(it1, it2, id1, id2);
        
        return compExistingDeques(id1, id2);
    }
}

int main (int args, char *argv[]) {
    unsigned long id1 = jnp1::strdeque_new();
    jnp1::strdeque_insert_at(id1, 2, "dsadsa");
    jnp1::strdeque_insert_at(id1, 0, "dasda");
    jnp1::strdeque_remove_at(id1, 2);
    jnp1::strdeque_remove_at(id1, 0);
    jnp1::strdeque_remove_at(0, 2);
    cerr << dequeMap.size() << endl;
    
    return 0;
}
