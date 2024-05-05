#include "game.h"
#include <iostream>
#include <thread>
#include <future>
#include <fstream>
#include "SDL.h"
#include "obstacle.h"

Game::Game(std::size_t grid_width, std::size_t grid_height, std::string&& name)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      name(name) {
  obstacles.emplace_back(std::make_shared<Obstacle>(static_cast<float>(random_w(engine)),static_cast<float>(random_h(engine)),snake.getGridWidth(),snake.getGridHeight()));
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food, obstacles);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }

  SaveScore();
}

void Game::SaveScore(){
  if (name != "1"){
    //opens score.txt file in write mode
    std::ofstream file("../score.txt");
    //writes the score and player to the score.txt file 
    if (file){
      file << name << ": " << score << ";" << std::endl; 
      file.close();
    }else{
      std::cout << "Couldn't open and write to the score.txt file" << std::endl;
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}


void Game::Update() {
  if (!snake.alive) return;
  
  std::future<void> ftr = std::async([this](){
    int num_obstacles = (this->obstacles).size();
    for (int i = 0; i < num_obstacles; i++){
      (this->obstacles[i])->UpdatePosition();
    }
  });
  ftr.wait();
  
  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;

    // Add moving obstacles as the score increases
    if (score%10 == 0){
      obstacles.emplace_back(std::make_shared<Obstacle>(static_cast<float>(random_w(engine)),static_cast<float>(random_h(engine)),snake.getGridWidth(),snake.getGridHeight()));
    }
  }

  // Check if the snake's head hit an obstacle
  int num_obstacles = obstacles.size();
  for (int i = 0; i < num_obstacles; i++){
    int obs_x = static_cast<int>(obstacles[i]->getX());
    int obs_y = static_cast<int>(obstacles[i]->getY());
    if (new_x == obs_x && new_y == obs_y){
      snake.alive = false;
    }
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }