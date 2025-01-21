

/*
    @class
    Lane
    @brief
    This is the class for the lanes

    It will determine if the lane is water or road
    @param
    int y - The y position of the lane
    @param
    bool left - If the lane is on the left side of the screen
    @param
    bool water - If the lane is water

*/
class Lane {
    /// @brief 
    /// The y position of the lane
    int y;
    /// @brief
    /// If the lane is on the left side of the screen
    bool left;
    /// @brief 
    /// If the lane is water
    bool water;
    /// @brief 
    /// This will be the vector of buses that are in the lane
    std::vector<Bus *> buses;
    public:
        Lane() {}
        Lane(int y, bool left, bool water) : y(y), left(left), water(water) {}

        bool is_left() {
            return this->left;
        }

        /// Moves the entire lane 
        void move_lane() {
            for (int i=0; i < this->buses.size(); i++) {
                if (this->buses[i]->move()) {
                    this->buses.erase(this->buses.begin() + i);
                }
            }
        }
};


// Class for board which will actually determine what everything will be
class Board {
    int x, y;
    std::vector<Lane *> lanes;
    
    public:
        Board (int x, int y) : x(x), y(y) {}

        /*
            @brief
            This function will determin if the lane is water or road
            @note
            It is about a 25% chance for it to be water, otherwise it will be a road lane
            @param
            None
            @returns
            None
        
        */
        void determine_board() {
            // The Y-1 is for the spawn row for the frog
            // We don't want anything spawning there EXCEPT for the frog
            // Otherwise we have a 25% chance of the lane being water
            for(int i=0; i < this->y-1; i++) {
                if (random_water_chance()) {
                    this->lanes.push_back(new Lane(i, random_left(), true));
                } else {
                    this->lanes.push_back(new Lane(i, random_left(), false));
                }
            }
        }

        Lane get_lane(int y) {
            return *this->lanes[y];
        }


        /// @brief
        /// This will move all the items in the lanes, figure this will be easier to work on than the spawn function till I figure out what I want to do
        /// @param
        /// None
        /// @return
        /// Nothing
        void move_lane_children() {
            for (int i=0; i < this->lanes.size(); i++) {
                this->lanes[i]->move_lane();
            }
        }
};