#include <iostream>
#include <deque>
#include <map>
#include <cassert>
#include <vector>
#include "strdequeconst.h"

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
    
    using mapIterator = map<unsigned long, deque<string> >::iterator;
    map<unsigned long, deque<string> > &get_dequeMap(){
        static map<unsigned long, deque<string> > dequeMap;
        return dequeMap;
    };
    
    unsigned long &get_availableId() {
        static unsigned long availableId = 0;
        return availableId;
    };
    
    const unsigned long get_emptyId() {
        static const unsigned long emptyId = jnp1::emptystrdeque();
        return emptyId;
    };
    
    static string printId(unsigned long id) {
        if (id == get_emptyId())
            return "the Empty Deque";
        else
            return to_string(id);
    }
    
    static string printDequeId(unsigned long id) {
        if (id == get_emptyId())
            return "the Empty Deque";
        else
            return "deque " + to_string(id);
    }
    
    static int checkInsertAt(unsigned long id, size_t pos, const char* value) {
        if (get_debug()) {
            cerr << "strdeque_insert_at(" << printId(id) << ", " << pos << ", ";
            
            if (value == NULL)
                cerr << "NULL" << ")" << endl;
            else
                cerr << "\"" << value << "\"" << ")" << endl;
        }
        
        if (id == get_emptyId()) {
            if (get_debug())
                cerr << "strdeque_insert_at: attempt to insert into the Empty Deque" << endl;
            return 1;
        }
        
        if (value == NULL) {
            if (get_debug())
                cerr << "strdeque_insert_at: attempt to insert NULL into a deque " << id << endl;
            return 1;
        }
        
        return 0;
    }
    
    static int compDeques(unsigned long id1, unsigned long id2) {
        int result;
        
        if (get_dequeMap()[id1] < get_dequeMap()[id2]) {
            result = -1;
        }
        else if (get_dequeMap()[id1] == get_dequeMap()[id2]) {
            result = 0;
        }
        else {
            result = 1;
        }
        
        return result;
    }
}

namespace jnp1 {
    extern "C" unsigned long strdeque_new() {
        if (get_debug())
            cerr << "strdeque_new()" << endl;
        
        deque <string> kolejka;
        get_dequeMap().insert(make_pair(get_availableId(), kolejka));
        
        if (get_debug())
            cerr << "strdeque_new: deque " << get_availableId() << " created" << endl;
        
        return get_availableId()++;
    }
    
    extern "C" void strdeque_delete(unsigned long id) {
        if (get_debug())
            cerr << "strdeque_delete(" << printId(id) << ")" << endl;
        
        if (id == get_emptyId()) {
            if (get_debug())
                cerr << "strdeque_delete: attempt to remove the Empty Deque" << endl;
            return;
        }
        
        mapIterator it = get_dequeMap().find(id);
        
        if (it != get_dequeMap().end()) {
            get_dequeMap().erase(it);
            
            if (get_debug())
                cerr << "strdeque_delete: " << id << " deleted" << endl;
        }
        else if (get_debug())
            cerr << "strdeque_size: " << "deque " << id << " does not exist" << endl;
    }
    
    extern "C" size_t strdeque_size(unsigned long id) {
        if (get_debug())
            cerr << "strdeque_size(" << printId(id) << ")" << endl;
        
        if (id == get_emptyId()) {
            if (get_debug())
                cerr << "strdeque_size: the Empty Deque contains 0 elements" << endl;
            return (size_t) 0;
        }
        
        mapIterator it = get_dequeMap().find(id);
        
        if (it != get_dequeMap().end()) {
            if (get_debug()) {
                cerr << "strdeque_size: " << "deque " << id << " contains "
                << (get_dequeMap().at(id)).size() << " elements" << endl;
            }
            
            return (get_dequeMap().at(id)).size();
        }
        else if (get_debug())
            cerr << "strdeque_size: " << "deque " << id << " does not exist" << endl;
        
        return (size_t) 0;
    }
    
    extern "C" void strdeque_insert_at(unsigned long id, size_t pos, const char* value) {
        if (checkInsertAt(id, pos, value) == 1)
            return;
        
        mapIterator it = get_dequeMap().find(id);
        
        if (it != get_dequeMap().end()) {
            if (pos <= strdeque_size(id)) {
                (get_dequeMap().at(id)).insert((get_dequeMap().at(id)).begin() + pos, string(value));
                
                if (get_debug()) {
                    cerr << "strdeque_insert_at: " << "deque " << id << ", element \"" << value
                    << "\" inserted at " << pos << endl;
                }
            }
            else {
                (get_dequeMap().at(id)).push_back(string(value));
                
                if (get_debug()) {
                    cerr << "strdeque_insert_at: " << "deque " << id << ", element \"" << value
                    << "\" inserted at the end" << endl;
                }
            }
        }
        else if (get_debug())
            cerr << "strdeque_insert_at: " << "deque " << id << " does not exist" << endl;
    }
    
    extern "C" void strdeque_remove_at(unsigned long id, size_t pos) {
        if (get_debug())
            cerr << "strdeque_remove_at(" << printId(id) << ", " << pos <<  ")" << endl;
        
        if (id == get_emptyId()) {
            if (get_debug())
                cerr << "strdeque_remove_at: attempt to remove from the Empty Deque" << endl;
            return;
        }
        
        mapIterator it = get_dequeMap().find(id);
        if (it != get_dequeMap().end()) {
            if (pos < strdeque_size(id)) {
                (get_dequeMap().at(id)).erase((get_dequeMap().at(id)).begin() + pos);
                
                if (get_debug()) {
                    cerr << "strdeque_remove_at: " << "deque " << id << ", element at "
                    << pos <<  " removed" << endl;
                }
            }
            else if (get_debug()) {
                cerr << "strdeque_remove_at: " << "deque " << id << ", position "
                << pos <<  " is greater than size" << endl;
            }
        }
        else if (get_debug())
            cerr << "strdeque_remove_at: " << "deque " << id << " does not exist" << endl;
    }
    
    extern "C" const char* strdeque_get_at(unsigned long id, size_t pos) {
        if (get_debug())
            cerr << "strdeque_get_at(" << printId(id) << ", " << pos <<  ")" << endl;
        
        if (id == get_emptyId()) {
            if (get_debug())
                cerr << "the Empty Deque does not contain an element at " << pos << endl;
            return NULL;
        }
        
        mapIterator it = get_dequeMap().find(id);
        if (it != get_dequeMap().end()) {
            if (pos < strdeque_size(id)) {
                if (get_debug()) {
                    cerr << "strdeque_get_at: " << "deque " << id << ", element at " << pos
                    << " is \"" << (get_dequeMap().at(id)).at(pos).c_str() << "\"" << endl;
                }
                
                return (get_dequeMap().at(id)).at(pos).c_str();
            }
            else if (get_debug()) {
                cerr << "strdeque_get_at: " << "deque " << id << ", position "
                << pos << " is greater than size" << endl;
            }
        }
        else if (get_debug())
            cerr << "strdeque_get_at: " << "deque " << id << " does not exist" << endl;
        
        return NULL;
    }
    
    extern "C" void strdeque_clear(unsigned long id) {
        if (get_debug())
            cerr << "strdeque_clear(" << printId(id) << ")" << endl;
        
        if (id == get_emptyId()) {
            if (get_debug())
                cerr << "attempt to clear the Empty Deque" << endl;
            return;
        }
        
        mapIterator it = get_dequeMap().find(id);
        if (it != get_dequeMap().end()) {
            (get_dequeMap().at(id)).clear();
            
            if (get_debug())
                cerr << "strdeque_clear: " << "deque " << id << " cleared" << endl;
        }
        else if (get_debug())
            cerr << "strdeque_clear: " << "deque " << id << " does not exist" << endl;
    }
    
    extern "C" int strdeque_comp(unsigned long id1, unsigned long id2) {
        unsigned long dq1 = id1;
        if (get_dequeMap().find(dq1) == get_dequeMap().end())
            dq1 = get_emptyId();
        unsigned long dq2 = id2;
        if (get_dequeMap().find(dq2) == get_dequeMap().end())
            dq2 = get_emptyId();

        if (get_debug())
            cerr << "strdeque_comp(" << printId(id1) << ", " << printId(id2) <<  ")" << endl;
        
        int result = compDeques(dq1, dq2);
        
        if (get_debug()) {
            cerr << "strdeque_comp: result of comparing " << printDequeId(id1) << " to "
            << printDequeId(id2) << " is " << result << endl;
        }
        
        return result;
    }
}
