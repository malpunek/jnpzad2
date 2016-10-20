#ifndef strdeque_h
#define strdeque_h

/* Tworzy nową, pustą kolejkę dwustronną ciągów znaków i zwraca jej identyfikator. */
unsigned long strdeque_new();

/* Jeżeli istnieje kolejka dwustronna o identyfikatorze id, usuwa ją, 
 a w przeciwnym przypadku nic nie robi. */
void strdeque_delete(unsigned long id);

/* Jeżeli istnieje kolejka dwustronna o identyfikatorze id, zwraca liczbę jej
 elementów, a w przeciwnym przypadku zwraca 0. */
size_t strdeque_size(unsigned long id);

/* Jeżeli istnieje kolejka dwustronna o identyfikatorze id oraz value != NULL,
 wstawia element value przed pozycją pos lub na koniec kolejki, jeżeli pos
 wykracza poza kolejkę.
 Gwarancje odnośnie kosztów wstawienia na początku, na końcu i w środku
 mają być takie same jak w przypadku kontenera deque (plus koszt
 odnalezienia kolejki o danym identyfikatorze).
 Jeżeli kolejka dwustronna nie istnieje lub value == NULL, to nic nie robi.
 Pozycje w kolejce numerowane są od zera.*/
void strdeque_insert_at(unsigned long id, size_t pos, const char* value);

/* Jeżeli istnieje kolejka dwustronna o identyfikatorze id i pos nie wykracza
 poza nią, usuwa element na pozycji pos, a w przeciwnym przypadku nic nie
 robi. */
void strdeque_remove_at(unsigned long id, size_t pos);

/* Jeżeli istnieje kolejka dwustronna o identyfikatorze id i pos nie wykracza
 poza kolejkę, zwraca wskaźnik do elementu na pozycji pos, a w przeciwnym
 przypadku zwraca NULL. */
const char* strdeque_get_at(unsigned long id, size_t pos);

/* Jeżeli istnieje kolejka dwustronna o identyfikatorze id, usuwa wszystkie
 jej elementy, a w przeciwnym przypadki nic nie robi. */
void strdeque_clear(unsigned long id);

/*Porównuje leksykograficznie kolejki dwustronne o identyfikatorach id1 i id2, zwracając:
 -1, gdy kolejka(id1) < kolejka(id2),
 0, gdy kolejka(id1) = kolejka(id2),
 1, gdy kolejka(id1) > kolejka(id2).
 Jeżeli kolejka dwustronna o którymś z identyfikatorów nie istnieje, to jest
 traktowana jako leksykograficznie równa liście pustej. */
int strdeque_comp(unsigned long id1, unsigned long id2);

#endif /* strdeque_h */
