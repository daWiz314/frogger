#include <ncurses.h>
#include <vector>
#include <utility>
#include <cstring>

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
    init_pair(4, COLOR_CYAN, COLOR_CYAN); // Set up color pair
    init_pair(5, COLOR_BLUE, COLOR_BLUE); // Set up color pair
    init_pair(6, COLOR_YELLOW, COLOR_YELLOW); // Set up color pair
    init_pair(7, COLOR_BLACK, COLOR_BLACK); // Set up color pair for background
    init_pair(8, COLOR_GREEN, COLOR_GREEN); // Set up color pair for frog
    init_pair(9, COLOR_WHITE, COLOR_BLACK); // Set up color pair for displaying text
    init_pair(10, COLOR_RED, COLOR_WHITE); // Set up color pair for displaying alert text

    // This is the background color so that we can "erase" the bus as it moves
    bkgd(COLOR_PAIR(7)); // Set background color

    game();
    return 0;
}

void draw_message(const char *message) {
    int x, y;
    getmaxyx(stdscr, y, x);
    attron(COLOR_PAIR(10));
    mvprintw(y/2, x/2 - strlen(message)/2, message);
    refresh();
    getch();
    return;
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
        attron(COLOR_PAIR(9));
        mvprintw(0, 0, "Score: %d Lives: %d", frog.get_score(), frog.get_lives());
        timeout(100); // Set timeout so we can move everything still
        int ch = getch(); // Get input
        if (ch == ERR) {
            frog.gain_move();
        } else {
            frog.handle_input(ch); // Handle input
        }
        
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

        // Check if frog is at the top
        if (frog.get_position().second == 1) {
            frog.gain_score();
            draw_message("You gained a point!");
            frog.restart();
        }
        refresh();
    }
    draw_message("Game Over!");

    endwin();
    return 0;
}