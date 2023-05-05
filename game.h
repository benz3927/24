#ifndef GAME_H
#define GAME_H
#include "TwentyFour.h"
#include "player.h"
#include "stack.h"
#include "node.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

class Game {
private:
  Game() = delete;
  long unsigned int num_players;
  vector<Player *> players;
  void create_players(vector<string> player_names);

public:
  Game(int, vector<string> &player_names);
  void wins_scoreboard();
  void round_timer();
  void round_keeper(TwentyFour solution);
  void generate_solutions(TwentyFour solution, vector<double> mode1_numbers);
  void update_score();
  void winner();
};

#endif // GAME_H


