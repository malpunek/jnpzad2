#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;
using kolejkaDesc = pair<unsigned long, deque<string>>;

vector<kolejkaDesc> wektorKolejek;
unsigned long dostepneId = 0;

static const int idNum = 0;
static const int queue = 1;

vector<kolejkaDesc>::iterator szukajKolejki(unsigned long id) {
    if (id >= dostepneId)
        return wektorKolejek.begin()+id+1;

    auto lb_cmp = [](kolejkaDesc const &x, double d) -> bool { return x.first < d; };
    return std::lower_bound(wektorKolejek.begin(), wektorKolejek.end(), id, lb_cmp);
}

unsigned long strdeque_new() {
    deque <string> kolejka;
    wektorKolejek.push_back(make_pair(dostepneId, kolejka));
    dostepneId++;

    return dostepneId-1;
}

void strdeque_delete(unsigned long id) {
    auto it = szukajKolejki(id);
    
    if (it == wektorKolejek.begin()+id)
        wektorKolejek.erase(wektorKolejek.begin()+id);
}

size_t strdeque_size(unsigned long id) {
    auto it = szukajKolejki(id);
    
    if (it == wektorKolejek.begin()+id)
        return get<queue>(wektorKolejek[id]).size();

    return 0;
}

void strdeque_insert_at(unsigned long id, size_t pos, const char* value) {
    auto it = szukajKolejki(id);

    if (it == wektorKolejek.begin()+id && value != NULL) {
        deque<string> kolejka = get<queue>(wektorKolejek[id]);
        
        if (pos >= kolejka.size()) {
            kolejka.push_back(value);
        }
        else {
            kolejka.insert(kolejka.begin()+pos, value);
        }
    }
}

void strdeque_remove_at(unsigned long id, size_t pos) {
    auto it = szukajKolejki(id);

    if (it == wektorKolejek.begin()+id) {
        deque<string> kolejka = get<queue>(wektorKolejek[id]);
        
        if (pos < kolejka.size())
            kolejka.erase(kolejka.begin()+pos);
    }
}

const char* strdeque_get_at(unsigned long id, size_t pos) {
    auto it = szukajKolejki(id);

    if (it == wektorKolejek.begin()+id) {
        deque<string> kolejka = get<queue>(wektorKolejek[id]);
        
        if (pos < kolejka.size())
            return kolejka.at(pos).c_str();
    }

    return NULL;
}

void strdeque_clear(unsigned long id) {
    auto it = szukajKolejki(id);
    
    if (it == wektorKolejek.begin()+id) {
        get<queue>(wektorKolejek[id]).clear();
    }
}

int strdeque_comp(unsigned long id1, unsigned long id2) {
    auto it1 = szukajKolejki(id1);
    auto it2 = szukajKolejki(id2);

    if (it1 != wektorKolejek.begin()+id1 && it2 != wektorKolejek.begin()+id2) {
        return 0;
    }
    else if (it2 != wektorKolejek.begin()+id2) {
        return 1;
    }
    else if (it1 != wektorKolejek.begin()+id1) {
        return -1;
    }
    else {
        if (wektorKolejek[id1] < wektorKolejek[id2]) {
            return -1;
        }
        else if (wektorKolejek[id1] == wektorKolejek[id2]) {
            return 0;
        }
        else {
            return 1;
        }
    }
}

int main(int argc, const char * argv[]) {
    unsigned long id1 = strdeque_new();
    unsigned long id2 = strdeque_new();
    strdeque_delete(2);

    return 0;
}
