#include <ncurses.h>
#include <vector>
#include <utility>

#include "helpers.h"
#include "Bus.h"
#include "Frog.h"


int game();

int main() {
    initscr(); // Start ncurses
    noecho(); // Don't echo keypresses
    curs_set(0); // Don't display a cursor
    keypad(stdscr, TRUE); // Enable special keys
    cbreak(); // Disable line buffering
    start_color(); // Enable color
    
    init_pair(1, COLOR_WHITE, COLOR_WHITE); // Set up color pair
    init_pair(2, COLOR_MAGENTA, COLOR_MAGENTA); // Set up color pair
    init_pair(3, COLOR_RED, COLOR_RED); // Set up color pair
    init_pair(4, COLOR_GREEN, COLOR_GREEN); // Set up color pair
    init_pair(5, COLOR_BLUE, COLOR_BLUE); // Set up color pair
    init_pair(6, COLOR_YELLOW, COLOR_YELLOW); // Set up color pair
    init_pair(7, COLOR_BLACK, COLOR_BLACK); // Set up color pair for background
    init_pair(8, COLOR_CYAN, COLOR_CYAN); // Set up color pair for frog

    // This is the background color so that we can "erase" the bus as it moves
    bkgd(COLOR_PAIR(7)); // Set background color

    game();
    return 0;
}

int game() {
    // Init variables
    int x, y; // Screen dimensions
    getmaxyx(stdscr, y, x); // Get screen dimensions
    bool gameover = false; // Game over flag

    // Set up border
    box(stdscr, 0, 0);
    refresh();
    
    // Create buses
    // The buses we are creating will have random starting points, and random speeds
    srand(time(nullptr)); // Seed random number generator
    std::vector<Bus *> buses; // Vector to contain buses
    for (int i = 0; i < 10; i++) {
        Bus *bus = new Bus(1, random_x(y-1), random_x(1000), x-2, random_color());
        buses.push_back(bus);
    }

    // Create frog
    Frog frog(x/2, y-2);
    // Debug info here
    // for (int i = 0; i < buses.size(); i++) {
    //     std::pair<int, int> pos = buses[i]->get_position();
    //     mvprintw(5 + i, 10, "Bus %d: %d, %d %d", i, pos.first, pos.second, buses[i]->get_speed());
    // }
    // refresh();

    // Main game loop
    while(!gameover) {
        
        timeout(100); // Set timeout so we can move everything still
        int ch = getch(); // Get input
        frog.move(ch); // Handle input
        
        // Move all the buses
        for(Bus *bus : buses) {
            bus->move();
        }
        // Spawn new buses
        if (random_bus_chance() % 25 == 0) {
            Bus *bus = new Bus(1, random_x(y-1), random_x(1000), x-2, random_color());
            buses.push_back(bus);
        }
        // Check if frog is on a bus
        for(Bus *bus : buses) {
            std::pair<int, int> bus_pos = bus->get_position();
            std::pair<int, int> frog_pos = frog.get_position();
            if (bus_pos.first == frog_pos.first && bus_pos.second == frog_pos.second) {
                frog.lose_life();
            }
        }
        // Check if frog is out of lives
        if (frog.get_lives() == 0) {
            gameover = true;
        }
        refresh();
    }

    endwin();
    return 0;
}