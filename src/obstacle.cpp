#include "obstacle.h"
#include <iostream>
#include "SDL.h"

float Obstacle::speed = 0.08;
/*
Obstacle::Obstacle(float x_, float y_, int grid_width_, int grid_height_){
  speed += 0.02;
}*/


void Obstacle::UpdatePosition(){
  if (counter == 0){
    direction = std::rand()%4;
  }
  
  switch (direction){
    case 0:
      y -= speed/2;
      break;
    case 1:
      x -= speed/2;
      break;
    case 2:
      y += speed/2;
      break;
    case 3:
      x += speed/2;
      break;
  }

  x = fmod(x + grid_width, grid_width);
  y = fmod(y + grid_height, grid_height);

  counter++;
  if (counter>200){
    counter = 0;
  }
}