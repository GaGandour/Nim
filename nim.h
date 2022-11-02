#include <cstdlib>

int randFromInclusiveRange(int min, int max) {
    return rand()%(max - min + 1) + min;
}