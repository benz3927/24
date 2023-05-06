// 24 Game in C++

/**
 *
 * @file TwentyFour.cpp
 * @authors Benjamin Zhao annd Leonardo Li
 * @date 5/4/2023
 */

#include "TwentyFour.h"
#include "game.h"
#include "player.h"
#include "stack.h"
#include "node.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <vector>

/**
 * @brief Read in the game mode 1 (for multiplayer) or 0 (solo freeplay) and the names
 * of the players who are playing the game from a txt file.
 * @param file_name: the text file with the excecutable shell script commands to be read in.
 * @param game_mode: a string for the game mode: 1 for multiplayer and 0 for solo freeplay.
 * @param names: the names of all players as a vector of strings.
 */
void read_file(string file_name, string &game_mode, vector<string> &names) {
    ifstream the_file(file_name);
    string command;
    while(the_file >> command) {
        if (command == "mode") {
            the_file >> game_mode;
            // Game mode 1 -> Competition - Multplayer Option
            // Game mode 0 -> Freeplay - Solo Option
        }
        if (command == "names") {
            string name;
            while (the_file >> name) {
                names.push_back(name);
            }
        }
    }
}

void print_vector_strings(vector<string> strings) {
  for (const auto& s : strings) {
    cout << s << " " << endl;
  }
}


/**
* Starts a multiplayer version of the game 24. The game object keeps track of the score and rounds
* for each player as they take turns solving randomly generated expressions.
* @param solution a reference to a TwentyFour object used to generate expressions and check solutions.
* @param players an integer representing the number of players in the game.
* @param names a vector of strings representing the names of the players.
*/
void multiplayer(int players, vector<string> names){
  TwentyFour solution;
  Game game(players, names);
  game.wins_scoreboard();
  game.round_keeper(solution);
}

/**
* Allows the user to input 4 numbers and generates all the possible solutions for the 24 game
* using those numbers. The function calls on helper functions and checkers to evaluate and validate
* expressions. The final solutions are stored in a vector of strings called all_solutions.
* @param solution an object of class TwentyFour that contains the functions to
* generate and validate solutions to game 24.
*/
void freeplay(){
  TwentyFour solution;
  vector<double> mode0_numbers;
  vector<string> expr;
  mode0_numbers.clear();
  string input;
  cout << "**  Please input 4 numbers separated by space: **" << endl;
  getline(cin, input);
  stringstream ss(input);
  double num;
  while (ss >> num) {
    mode0_numbers.push_back(num);
  }
  solution.final_solutions = solution.get_all_unique_solutions(mode0_numbers, expr);
  if (!solution.is_there_solution(mode0_numbers)) {
    cout << "There is no solution to these set of numbers." << endl;
    return;
  }
  else {
    solution.prompt_user();
    print_vector_strings(solution.final_solutions);
  }
}

/**
 * @brief Main function reads in a series of commands from given txt file.
 * @param argc: "the number of command line arguments, including the_file name of the 
 * program being excecuted" (from Lab 4 Handout).
 * @param argv: "an array of strings which are the command line arguments" (from Lab 4 Handout).
 */
int main(int argc, char ** argv) {
  srand((unsigned)time(NULL));
  string file_name = argv[1];
  string game_mode;
  int num_players;
  vector<string> names;
  read_file(file_name, game_mode, names);
  num_players = names.size();
  cout << "Welcome to the game of 24! 🏠" << endl;
  vector<string> expression;
  if (game_mode == "0"){
    freeplay();
  }
  if (game_mode == "1"){
    multiplayer(num_players, names);
  }
}
