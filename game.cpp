#include "game.h"
#include "player.h"
#include "TwentyFour.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>

/**
* A function to update the score of a player who won the round in the 24 game.
* The function prompts the user to enter the ID number 
* (ranging from 1 to the number of players) of the winning player and
* updates their score accordingly.
*/
void Game::update_score() {
  int player_id;
  cout << "Please enter the player ID (number in order from 1 - number of "
          "players) of who won the round. If no one won, "
          "please type 0. ";
  cin >> player_id;
  if (player_id == 0) {
    return;
  }
  Player *update_player = players[player_id - 1];
  update_player->add_point();
}

/**
* A function to print a vector of doubles.
* @param vec a vector of doubles to be printed.
*/
void print_vector(vector<double> vec) {
  for (vector<double>::iterator it = vec.begin(); it != vec.end(); it++) {
    if (it + 1 == vec.end()) {
      cout << *it;
      return;
    }
    cout << *it << " ";
  }
}

/**
* A function to print a vector of strings representing possible solutions to the 24 game.
* @param solutions a vector of strings representing possible solutions.
*/
void print_solutions(vector<string> solutions) {
  for (const auto& solution : solutions) {
    cout << solution << " " << endl;
  }
}

// Print the message to pause the game so that players can discuss who won the round.
void print_message(){
    cout << "* Giving you some time to discuss who was the first player to " << endl;
    cout << "find a correct way to compute 24 using the given cards this round." << endl; 
    cout << "Please type 'k' when you are done! * " << endl;
    string k;
    cin >> k;
}

/**
* Function sets up each round of the game 24. It generates random solveable numbers, 
* prompts the user to solve the game within a certain time limit, 
* displays the possible solutions, updates the score, and clears the console.
* @param solution a TwentyFour game object.
*/

// CITE: https://www.softwaretestinghelp.com/cpp-sleep/
// DESC: Sleep makes the program wait for a given number of seconds 
// before excecuting the next line of code.

// CITE: https://stackoverflow.com/questions/17793059/
// clrscr-equivalent-in-codeblocks#:~:text=All%20you%20have%20to%20do%20is%20use%20printf.
// DESC: system("clear") clears the console.
void Game::round_keeper(TwentyFour solution) {
  for (long unsigned int i = 0; i < 5; i++) {
    vector<double> mode1_numbers = solution.generate_random_numbers();
    cout << "** Round " << i + 1 << " ** You have 30 seconds in this round! " << endl;
    cout << "\a" << "* Your numbers for this round are: ";
    print_vector(mode1_numbers);
    cout << " *" << endl;
    round_timer();
    cout << "Your time is up for this round!" << endl;
    vector<string> expression;
    print_message();
    cout << "* Possible Solutions: *" << endl;
    solution.final_solutions = solution.get_all_unique_solutions(mode1_numbers, expression);
    print_solutions(solution.final_solutions);
    update_score();
    wins_scoreboard();
    sleep(5);
    system("clear");
  }
  cout << "The Game is over!" << endl;
  winner();
}

/**
* A function to play a beep sound in the last 5 seconds of a round
* signaling the end of a round.
*/

// CITE: https://cplusplus.com/forum/beginner/219843/
// DESC: cout << "\a" makes a beep noise!
void beep_for_5seconds() {
  for (long unsigned int i = 0; i < 5; i++) {
    cout << "\a" << "You have " << 5 - i << " seconds remaining in this round!" << endl;
    sleep(2);
  }
}

/**
* A timer that sets 30 seconds for each round of the game 24.
*/
void Game::round_timer() {
  clock_t start_time = clock(); // Start timer
  double seconds_passed;
  cout << "... Begin!" << endl;
  bool boolean = true;
  while (boolean) {
    seconds_passed = (clock() - start_time) / CLOCKS_PER_SEC;
    if (seconds_passed == 25) {
      boolean = false;
      beep_for_5seconds();
    }
  }
}

/**
* Game class that initializes the number of players and creates
* Player objects for each player using the MIL version of the normal constructor.
* @param given_num_players an integer representing the number of players.
* @param player_names a vector of strings representing the names of the players.
*/
Game::Game(int given_num_players, vector<string> &player_names)
    : num_players(given_num_players) {
  create_players(player_names);
}

/**
* Create Player objects for each player in the game.
* @param player_names a vector of strings representing the names of the players.
*/
void Game::create_players(vector<string> player_names) {
  for (long unsigned int i = 0; i < num_players; i++) {
    string name = player_names[i];
    players.push_back(new Player(name, 0));
  }
}

/**
* Display the scores of each player in the game.
*/
void Game::wins_scoreboard() {
  for (long unsigned int i = 0; i < num_players; i++) {
    Player *player = players[i];
    player->get_player_score();
  }
}

/**
* A function to determine the winner(s) of the 24 game based on their score.
* If there is a tie, all players with the highest score are declared the winners of 24!
*/
void Game::winner() {
  int max_score;
  vector<Player *> max_score_players;
  for (long unsigned int i = 0; i < num_players; i++) {
    Player *player = players[i];
    int score = player->get_score();
    if (score > max_score) {
      max_score = score;
      max_score_players.clear();
      max_score_players.push_back(player);
    } else if (score == max_score) {
      max_score_players.push_back(player);
    }
  }
  // Print the names of the players with the maximum score
  if (max_score_players.size() == 1) {
    cout << "The winner of 24 is " << max_score_players[0]->get_name() << "!"
         << endl;
  } else {
    long unsigned int max_num = max_score_players.size();
    cout << "The winners with a score of " << max_score << " are:" << endl;
    for (long unsigned int i = 0; i < max_num; i++) {
      Player *player = max_score_players[i];
      cout << player->get_name() << endl;
    }
  }
}
