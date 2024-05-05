#ifndef OBSTACLE_H
#define OBSTACLE_H

class Obstacle{
    public:
    static float speed;
    Obstacle(const float &x, const float &y, const int &grid_width, const int &grid_height):x(x),y(y),grid_width(grid_width),grid_height(grid_height){speed += 0.02;};

    //getter functions
    float getY() {return y;}
    float getX() {return x;}

    //function to change the position of obstacles
    void UpdatePosition();

    private:
    float x;
    float y;
    int grid_width;
    int grid_height;
    int counter{0};
    int direction; 
};

#endif