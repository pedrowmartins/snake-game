#ifndef GAME_H
#define GAME_H

#include <random>
#include <string>
#include <mutex>
#include <vector>
#include <memory>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "obstacle.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, std::string&& name);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  Snake snake;
  SDL_Point food;
  //vector of game objects
  std::vector<std::shared_ptr<Obstacle>> obstacles;
  std::mutex mtx;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  std::string name;

  void PlaceFood();
  void Update();
  //new function to save game score to a text file 
  void SaveScore();
};

#endif