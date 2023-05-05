#ifndef PLAYER_H
#define PLAYER_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class Player {
private:
    string name;
    int score;
    Player() = delete;

public:
  Player(string, int);
  void get_player_score();
  void add_point();
  int get_score();
  string get_name();
};

#endif // PLAYER_H