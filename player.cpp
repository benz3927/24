#include "player.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

// Using a member initialization list (MIL) constructor for the 
// Player object, as we learned from Professor Perkins
Player::Player(string given_name, int given_score)
    : name(given_name), score(given_score) {}

// Print the score of the player.
void Player::get_player_score() {
  if (score == 1){
    cout << name << " has " << score << " win." << endl;
  }
  else{
    cout << name << " has " << score << " wins." << endl;
  }
}

// Return the score (number of wins) of the player
// as an integer.
int Player::get_score() {
    return score;
}

// Get the name of the player as a string.
string Player::get_name() {
    return name;
}

// Add a point to a player's score if the player wins a round
// and gets the solution fastest.
void Player::add_point() {
  score += 1;
  cout << "** " << name << " won the round! **" << endl;
}