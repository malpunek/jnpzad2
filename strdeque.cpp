#include <iostream>
#include <deque>
#include <map>
#include <cassert>

using namespace std;

using mapIterator = map<unsigned long, deque<string> >::iterator;
map<unsigned long, deque<string> > dequeMap;

unsigned long availableId = 0;

#ifndef NDEBUG
unsigned long strdeque_new() {
    cerr << "strdeque_new()" << endl;
    
    deque <string> kolejka;
    dequeMap.insert(make_pair(availableId, kolejka));
    
    cerr << "strdeque_new: deque " << availableId << " created" << endl;
    
    return availableId++;
}

void strdeque_delete(unsigned long id) {
    cerr << "strdeque_delete(" << id << ")" << endl;
    dequeMap.erase(id);
    cerr << "strdeque_delete: " << "deque " << id << " deleted" << endl;
}

size_t strdeque_size(unsigned long id) {
    cerr << "strdeque_size(" << id << ")" << endl;
    mapIterator it = dequeMap.find(id);
    if (it != dequeMap.end()) {
        cerr << "strdeque_size: " << "deque " << id << " contains " << (dequeMap.at(id)).size() << " elements" << endl;
        return (dequeMap.at(id)).size();
    }
    else
        cerr << "strdeque_size: " << "deque " << id << " does not exist" << endl;
    return (size_t) 0;
}

void strdeque_insert_at(unsigned long id, size_t pos, const char* value) {
    cerr << "strdeque_insert_at(" << id << ", " << pos << ", " << (value == NULL ? "NULL" : value) << ")" << endl;
    mapIterator it = dequeMap.find(id);
    if (it != dequeMap.end()) {
        if (value != NULL) {
            if (pos <= strdeque_size(id)) {
                cerr << "strdeque_insert_at: " << "deque " << id << ", element \"" << value;
                cerr << "\" inserted at " << pos << endl;
                (dequeMap.at(id)).insert((dequeMap.at(id)).begin() + pos, value);
            }
            else {
                cerr << "strdeque_insert_at: " << "deque " << id << ", element \"" << value;
                cerr << "\" inserted at the end" << endl;
                (dequeMap.at(id)).push_back(value);
            }
        }
        else
            cerr << "strdeque_insert_at: " << "value is NULL" << endl;
    }
    else
        cerr << "strdeque_insert_at: " << "deque " << id << " does not exist" << endl;
}

void strdeque_remove_at(unsigned long id, size_t pos) {
    cerr << "strdeque_remove_at(" << id << ", " << pos <<  ")" << endl;
    mapIterator it = dequeMap.find(id);
    if (it != dequeMap.end()) {
        if (pos < strdeque_size(id)) {
            (dequeMap.at(id)).erase((dequeMap.at(id)).begin() + pos);
            cerr << "strdeque_remove_at: " << "deque " << id << ", element at " << pos <<  " removed" << endl;
        }
        else
            cerr << "strdeque_remove_at: " << "deque " << id << ", position " << pos <<  " is greater than size" << endl;
    }
    else
        cerr << "strdeque_remove_at: " << "deque " << id << " does not exist" << endl;
}

const char* strdeque_get_at(unsigned long id, size_t pos) {
    cerr << "strdeque_get_at(" << id << ", " << pos <<  ")" << endl;
    mapIterator it = dequeMap.find(id);
    if (it != dequeMap.end()) {
        if (pos < strdeque_size(id)) {
            cerr << "strdeque_get_at: " << "deque " << id << ", element at " << pos;
            cerr << " is " << (dequeMap.at(id)).at(pos).c_str() << endl;
            return (dequeMap.at(id)).at(pos).c_str();
        }
        else
            cerr << "strdeque_get_at: " << "deque " << id << ", position " << pos << " is greater than size" << endl;
    }
    else
        cerr << "strdeque_get_at: " << "deque " << id << " does not exist" << endl;
    return NULL;
}

void strdeque_clear(unsigned long id) {
    cerr << "strdeque_clear(" << id << ")" << endl;
    mapIterator it = dequeMap.find(id);
    if (it != dequeMap.end()) {
        cerr << "strdeque_clear: " << "deque " << id << " cleared" << endl;
        (dequeMap.at(id)).clear();
    }
    else
        cerr << "strdeque_clear: " << "deque " << id << " does not exist" << endl;
}

int strdeque_comp(unsigned long id1, unsigned long id2) {
    cerr << "strdeque_comp(" << id1 << ", " << id2 <<  ")" << endl;
    mapIterator it1 = dequeMap.find(id1);
    mapIterator it2 = dequeMap.find(id2);
    if (it1 == dequeMap.end() && it2 == dequeMap.end()) {
        cerr << "strdeque_com: deque " << id1 << " and deque " << id2 << " do not exist" << endl;
        return 0;
    }
    else if (it2 == dequeMap.end() ) {
        cerr << "strdeque_comp: deque " << id2 << " does not exist" << endl;
        return 1;
    }
    else if (it1 == dequeMap.end() ) {
        cerr << "strdeque_comp: deque " << id1 << " does not exist" << endl;
        return -1;
    }
    else {
        cerr << "strdeque_comp: result of comparing deque " << id1 << " to deque " << id2 << " is ";
        if (dequeMap[id1] < dequeMap[id2]) {
            cerr << "-1" << endl;
            return -1;
        }
        else if (dequeMap[id1] == dequeMap[id2]) {
            cerr << "0" << endl;
            return 0;
        }
        else {
            cerr << "1" << endl;
            return 1;
        }
    }
}
#else
unsigned long strdeque_new() {
    deque <string> kolejka;
    dequeMap.insert(make_pair(availableId, kolejka));
    return availableId++;
}

void strdeque_delete(unsigned long id) {
    dequeMap.erase(id);
}

size_t strdeque_size(unsigned long id) {
    mapIterator it = dequeMap.find(id);
    if (it != dequeMap.end())
        return (dequeMap.at(id)).size();
    return (size_t) 0;
}

void strdeque_insert_at(unsigned long id, size_t pos, const char* value) {
    mapIterator it = dequeMap.find(id);
    if (it != dequeMap.end() and value != NULL) {
        if (pos <= strdeque_size(id))
            (dequeMap.at(id)).insert((dequeMap.at(id)).begin() + pos, value);
        else
            (dequeMap.at(id)).push_back(value);
    }
    
}

void strdeque_remove_at(unsigned long id, size_t pos) {
    mapIterator it = dequeMap.find(id);
    if (it != dequeMap.end() and pos < strdeque_size(id))
        (dequeMap.at(id)).erase((dequeMap.at(id)).begin() + pos);
}

const char* strdeque_get_at(unsigned long id, size_t pos) {
    mapIterator it = dequeMap.find(id);
    if (it != dequeMap.end() and pos < strdeque_size(id))
        return (dequeMap.at(id)).at(pos).c_str();
    return NULL;
}

void strdeque_clear(unsigned long id) {
    mapIterator it = dequeMap.find(id);
    if (it != dequeMap.end())
        (dequeMap.at(id)).clear();
}

int strdeque_comp(unsigned long id1, unsigned long id2) {
    mapIterator it1 = dequeMap.find(id1);
    mapIterator it2 = dequeMap.find(id2);
    if (it1 == dequeMap.end() && it2 == dequeMap.end())
        return 0;
    else if (it2 == dequeMap.end() )
        return 1;
    else if (it1 == dequeMap.end() )
        return -1;
    else {
        if (dequeMap[id1] < dequeMap[id2])
            return -1;
        else if (dequeMap[id1] == dequeMap[id2])
            return 0;
        else return 1;
    }
}

int main(int argc, const char * argv[]) {
    unsigned long id1 = strdeque_new();
    unsigned long id2 = strdeque_new();
    
    return 0;
}
#endif

void assertTest(const char *value) {
    assert(value == NULL);
#ifndef NDEBUG
    cout << "udalo sie" << endl;
#endif
}


int main(int argc, const char * argv[]) {
    unsigned long id1 = strdeque_new();
    unsigned long id2 = strdeque_new();
    
    strdeque_insert_at(id1, 1, "aa");
    
    return 0;
}
