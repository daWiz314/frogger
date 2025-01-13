#include <map>

// Class for water
class Water {
    int y;
    bool left;
    public:
        Water() {}
        Water(int y, bool left) : y(y), left(left) {}

        bool is_left() {
            return this->left;
        }
};

// Class for road
class Road {
    int y;
    bool left;
    public:
        Road() {}
        Road(int y, bool left) : y(y), left(left) {}

        bool is_left() {
            return this->left;
        }
};


// This is just to organize the map
struct types_of_road {
    Water water;
    Road road;
};


// Class for board which will actually determin what everything will be
class Board {
    int x, y;
    std::map<int, types_of_road> roads;
    public:
        Board (int x, int y) : x(x), y(y) {}

        void determin_board() {
            for(int i=0; i < this->y; i++) {
                if (random_water_chance()) {
                    this->roads[i].water = Water(i, random_left());
                } else {
                    this->roads[i].road = Road(i, random_left());
                }
            }
        }
        types_of_road get_road(int y) {
            return this->roads[y];
        }
};