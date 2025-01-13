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
        attron(COLOR_PAIR(7));
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
    void move() {
        if (this->x >= this->max_x) {
            return;
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
    }
    std::pair<int, int> get_position() {
        return std::make_pair(this->x, this->y);
    }

    int get_speed() {
        return this->speed;
    }
private:
    void erase_bus() {
        attron(COLOR_PAIR(7));
        for (int i=0; i<this->max_length; i++) {
            mvprintw(this->y, this->x - i, " ");
        }
        mvprintw(this->y, this->x, " ");
        attron(COLOR_PAIR(7));
    }
    void draw_bus() {
        attron(colors["Yellow"]);
        for (int i=0; i<this->max_length; i++) {
            mvprintw(this->y, this->x - i, "B");
        }
        mvprintw(this->y, this->x, "B");
        attron(COLOR_PAIR(7));
    }
};