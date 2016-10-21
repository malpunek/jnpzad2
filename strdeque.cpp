#include <iostream>
#include <deque>
#include <map>

using namespace std;

using mapIterator = map<unsigned long, deque<string> >::iterator;
map<unsigned long, deque<string> > dequeMap;
unsigned long availableId = 0;

unsigned long strdeque_new() {
    deque <string> kolejka;
	dequeMap.insert(make_pair(dostepneId, kolejka));
	return dostepneId++;
}

void strdeque_delete(unsigned long id) {
	dequeMap.erase(id);
}

size_t strdeque_size(unsigned long id) {
	mapIterator it = dequeMap.find(id);
    if (it != dequeMap.end())
        return (dequeMap.at(id)).size();
    return 0;
}

void strdeque_insert_at(unsigned long id, size_t pos, const char* value) {
	mapIterator it = dequeMap.find(id);
	if (it != dequeMap.end() and value != NULL and pos <= strdeque_size(id))
		(dequeMap.at(id)).insert((dequeMap.at(id)).begin() + pos, value);
}

void strdeque_remove_at(unsigned long id, size_t pos) {
    mapIterator it = dequeMap.find(id);
	if (it != dequeMap.end() and pos < strdeque_size(id))
		(dequeMap.at(id)).erase((dequeMap.at(id)).begin() + pos);
}

const char* strdeque_get_at(unsigned long id, size_t pos) {
	mapIterator it = dequeMap.find(id);
	if (it != dequeMap.end() and pos <= strdeque_size(id))
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
    else if (it1 != dequeMap.end() )
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
    strdeque_delete(2);

    return 0;
}
