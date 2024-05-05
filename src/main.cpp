#include <iostream>
#include <fstream>
#include <string>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
  std::string name;
  std::cout << "Welcome to the Snake Game! If you wish to save your score and name, please write your name down in the terminal. If not, enter the character 1" << std::endl;
  std::cout << "Enter your name: " << std::endl;
  std::cin >> name;
  if (name != "1"){
    std::cout << "Thank you for entering your name! At the the end of the game your name and score will be saved to the score.txt file" << std::endl;
  }

  
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight, std::move(name));
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";

  return 0;
}