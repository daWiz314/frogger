#include <utility>

class Bus {
    int x, y, wait_time, speed, max_x, max_length;
public:
    Bus(int x, int y, int speed, int max_x) {
        this->max_length = random_bus_length();
        this->x = x + this->max_length;
        this->y = y;
        this->speed = speed;
        this->wait_time = 0;
        this->max_x = max_x;
        // Draw bus
        attron(colors["Yellow"]);
        for (int i=0; i<this->max_length; i++) {
            mvprintw(this->y, this->x - i, "B");
        }
        mvprintw(this->y, this->x, "B");
        attron(colors["Black"]);
    };
    bool check_next_spot() {
        // Check if the next spot is occupied with another bus
        int x = this->x + 1;
        char next = mvinch(this->y, this->x + 1);
        if (next == 'B') {
            return true;
        } else {
            return false;
        }
    }
    bool move() { // Bool if true kill it from the vector
    // Or as I like to call it, kill yourself
        if (this->x-this->max_length >= this->max_x+1) {
            this->erase_bus(); 
            return true;

        } else {
            if (this->wait_time >= this->speed) {
                if (this->check_next_spot()) {
                    this->wait_time = this->speed;
                } else {
                    this->wait_time = 0;
                    this->erase_bus();
                    this->x++;
                    this->draw_bus();
                }
            } else {
                this->wait_time += 100;
            }
        }
        return false;
    }
    std::tuple<int, int, int> get_position() {
        return std::make_tuple(this->x, this->y, this->x - this->max_length);
    }

    int get_speed() {
        return this->speed;
    }
private:
    void erase_bus() {
        attron(colors["Black"]);
        for (int i=0; i<this->max_length; i++) {
            mvprintw(this->y, this->x - i, " ");
        }
        mvprintw(this->y, this->x, " ");
        attron(colors["Black"]);
    }
    void draw_bus() {
        attron(colors["Yellow"]);
        for (int i=0; i<this->max_length; i++) {
            mvprintw(this->y, this->x - i, "B");
        }
        mvprintw(this->y, this->x, "B");
        attron(colors["Black"]);
    }
};