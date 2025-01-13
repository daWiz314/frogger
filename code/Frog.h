#include <ncurses.h>
#include <utility>

class Frog {
    int x, y, score, lives;
    int DEFAULT_X, DEFAULT_Y;
public:
    Frog(int x, int y) : x(x), y(y), score(0), lives(3), DEFAULT_X(x), DEFAULT_Y(y) {
        
        // Draw frog
        attron(COLOR_PAIR(8));
        mvprintw(this->y, this->x, "F");
    }

    int get_lives() {
        return this->lives;
    }

    int get_score() {
        return this->score;
    }

    std::pair<int, int> get_position() {
        return std::make_pair(this->x, this->y);
    }

    void lose_life() {
        this->lives--;
        this->erase_frog();
        this->x = this->DEFAULT_X;
        this->y = this->DEFAULT_Y;
        this->draw_frog();

    }
    
    void move(int key) {
        switch (key) {
            case KEY_UP:
                this->erase_frog();
                this->y--;
                this->draw_frog();
                break;
            case KEY_DOWN:
                this->erase_frog();
                this->y++;
                this->draw_frog();
                break;
            case KEY_LEFT:
                this->erase_frog();
                this->x--;
                this->draw_frog();
                break;
            case KEY_RIGHT:
                this->erase_frog();
                this->x++;
                this->draw_frog();
                break;
            case 'q':
                this->lives = 0;
                break;
        }
    }
private:
    void draw_frog() {
        attron(COLOR_PAIR(8));
        mvprintw(this->y, this->x, "F");
        attron(COLOR_PAIR(7));
    }
    void erase_frog() {
        attron(COLOR_PAIR(7));
        mvprintw(this->y, this->x, " ");
        attron(COLOR_PAIR(7));
    }
};