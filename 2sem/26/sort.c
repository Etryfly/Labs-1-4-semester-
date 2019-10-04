#include "sort.h"

void sort(Udt* list) {
    for (int i = 0; i < udtSize(list); ++i) {
        search(list);
    }
}