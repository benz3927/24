#ifndef TWENTY_FOUR_H
#define TWENTY_FOUR_H
#include "stack.h"
#include "node.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class TwentyFour {
private: 
  double threshold = pow(10.0, -5);
  char math_operators[4] = {'+', '-', '/', '*'};
  void expression_to_vec(vector<string>& expres_as_vec, const string& expression);
  void remove_spaces(vector<string>& expres_as_vec, vector<int>& indices);
  void remove_extra_parentheses(vector<string>& expres_as_vec, vector<int>& indices);
  string clean_brackets(string& expression);
  bool checker(vector<double> &numbers, vector<string> &expr, string &final_expression);
  void solve_24_recursive_helper(vector<double> numbers, vector<string> expr, vector<string>& all_solutions);
  void solve_24(vector<double>& numbers, vector<string>& all_solutions);
  double order(char op);
  double math_precision_operations(double a, double b, char op);
  void push_op(StackC& operators, char op);
  void push_number(const string& expres_as_vec, long unsigned int& i, StackD& values);
  void process_close_paren(StackC& operators, StackD& values);
  void process_operator(char op, StackC& operators, StackD& values);
  void process_remaining_operators(StackC& operators, StackD& values);
  double compute_expression(string expres_as_vec, StackD &values, StackC &operators);

public:
  vector<string> final_solutions;
  bool is_there_solution(vector<double> numbers);
  vector<double> generate_random_numbers();
  vector<string> get_all_unique_solutions(vector<double> &original_numbers, vector<string> expression);
  void prompt_user();
  bool final_checker(string final_expression);
};

#endif // TWENTY_FOUR_H