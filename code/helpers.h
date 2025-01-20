#include <cstdlib>
#include <ctime>

int random_x(int max) {
    int num = rand() % max;
    if (num == 0) {
        return 1;
    }
    return num;
}

int random_bus_length() {
    return rand() % 10 + 1;
}

int random_bus_chance() {
    return rand() % 100;
}

bool random_water_chance() {
    return (rand() % 100) % 25 == 0; // If this is true, then it will be water
}

bool random_left() {
    return rand() % 2 == 0;
}