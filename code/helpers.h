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

int random_color() {
    return rand() % 7 + 1;
}