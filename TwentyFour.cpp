#include "TwentyFour.h"
#include "stack.h"
#include "node.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <set>
using namespace std;

const double final_24 = 24.00000;

/**
* This function checks if there is a solution to the 24 game using a vector of numbers.
* @param numbers: the vector of numbers that are used to find the solution.
* @return: true if there is a solution, false if there is not.
*/
bool TwentyFour::is_there_solution(vector<double> numbers) {
  vector<string> expression;
  final_solutions = get_all_unique_solutions(numbers, expression);
  if (final_solutions.size() !=0){
    return true;
  }
  return false;
}

/**
* This function takes in two strings and a vector of expressions and 
* converts them to a math expression as a string.
* @param a: the first string in the math expression.
* @param b: the second string in the math expression.
* @param expr: the vector of expressions to convert to a string expression.
* @return result: a string representation of the expression.
*/
string convert_expr_to_string(string a, string b, vector<string> expr) {
  vector<string> temp;
  temp.push_back(a);
  temp.push_back(b);
  string result;
  result = "(" + temp[stoi(expr[0])] + ")" + expr[1] + "(" +
           temp[stoi(expr[2])] + ")";
  return result;
}

/**
* This function takes 2 double a and b and returns every possible positive
* solution to operations of a and b (multiplication addition subtraction division)
* and returns the solutions as a vector of doubles.
* @param a: the first double used in the math operation.
* @param b: the second double used in the math operation.
* @return results: a vector of the results of the math operation, 
* which includes sum, product, absolute difference (b-a or a-b), and quotient (if b and/or a is not zero).
*/
vector<double> operations(double a, double b) {
  double sum = double(a) + double(b);
  double product = double(a) * double(b);
  vector<double> result;
  result.push_back(sum);
  result.push_back(product);
  if (b > a) {
    result.push_back(b - a);
  } else {
    result.push_back(a - b);
  }
  if (b != 0) {
    double quotient = double(a) / double(b);
    result.push_back(quotient);
  }
  if (a != 0) {
    double quotient = double(b) / double(a);
    result.push_back(quotient);
  }
  return result;
}

/**
* This function takes the numbers given to make 24 and makes every possible
* combinations of 2 numbers as vectors and returns a vector of these vectors. The
* function also filters out duplicates i.e. (1 0) and (0 1) are duplicates.
* @param numbers: the vector of doubles to generate combinations from.
* @return possible_combinations: a 2D vector containing all possible unique combinations 
* of two numbers from the input vector.
*/
vector<vector<double>> combinations(vector<double> numbers) {
  vector<vector<double>> possible_combinations;
  for (int i = 0; i < numbers.size(); i++) {
    int a = numbers[i];
    for (int j = 0; j < numbers.size(); j++) {
      if (i == j) {
        continue;
      }
      int b = numbers[j];
      vector<double> combo;
      combo.push_back(a);
      combo.push_back(b);
      bool push = true;
      for (int i = 0; i < possible_combinations.size(); i++) {
        if (combo == possible_combinations[i]) {
          push = false;
        }
        if (combo[0] == possible_combinations[i][0] and
                combo[1] == possible_combinations[i][1] or
            combo[0] == possible_combinations[i][1] and
                combo[1] == possible_combinations[i][0]) {
          push = false;
        }
      }
      if (push != false) {
        possible_combinations.push_back(combo);
      }
    }
  }
  return possible_combinations;
}

/**
* Function takes in two numbers as strings and returns a vector of vector of strings,
* where each inner vector represents an math expression using the input numbers.
* @param a: the first string representing a number in the math expression.
* @param b: the second string representing a number in the math expression.
* @return expression: a vector of vector of strings, in which 
* each inner vector represents an arithmetic expression using the input numbers.
*/
vector<vector<string>> operation_expression(string a, string b) {
  vector<vector<string>> expression;
  expression.push_back({"0", "+", "1"});
  expression.push_back({"0", "*", "1"});
  int A = stoi(a);
  int B = stoi(b);
  if (B > A) {
    expression.push_back({"1", "-", "0"});
  } else {
    expression.push_back({"0", "-", "1"});
  }
  if (B != 0) {
    expression.push_back({"0", "/", "1"});
  }
  if (A != 0) {
    expression.push_back({"1", "/", "0"});
  }
  return expression;
}

/**
* This function takes in a character and checks if it is an operator (+, -, *, /).
* @param c: the character to check if it is an operator.
* @return: a boolean value indicating whether the input character is an operator or not.
*/
bool is_operator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}

/**
* Function takes in a character and checks if it is a digit (0-9).
* @param c: the character to check if it is a digit.
* @return bool: a boolean value indicating whether the input character is a digit or not.
*/
bool is_digit(char c) {
  return c >= '0' && c <= '9';
}

/**
* Function takes in an expression as a string and tokenizes it into a vector of strings
* while ignoring any characters which are not numbers or math operators.
* @param expres_as_vec: the string expression to be tokenized.
* @param expression: a reference to a vector of strings where the character expres_as_vec will be stored.
*/
void TwentyFour::expression_to_vec(vector<string>& expres_as_vec, const string& expression) {
  for (int i = 0; i < expression.length(); i++) {
    char c = expression[i];
    if (c == '(' || c == ')' || is_operator(c) || is_digit(c)) {
      string str(1, c);
      expres_as_vec.push_back(str);
    }
  }
}

/**
* This function takes in a tokenized expression (as a vector of strings) 
* and is used to removes any extra spaces.
* @param expres_as_vec: the math expression as a vector of strings.
* @param indices: a vector of integers of the indices of spaces in the expression
* which are to be removed.
*/
void TwentyFour::remove_spaces(vector<string>& expres_as_vec, vector<int>& indices) {
  for (int i = 0; i < expres_as_vec.size(); i++) {
    if (is_operator(expres_as_vec[i][0])) {
      if (i > 0 && expres_as_vec[i - 1] == " ") {
        indices.push_back(i - 1);
      }
      if (i + 1 < expres_as_vec.size() && expres_as_vec[i + 1] == " ") {
        indices.push_back(i + 1);
      }
    }
  }
}

/**
* Function removes extra parentheses and records their indices.
* @param expres_as_vec: a vector of strings of the math expression.
* @param indices: a vector to record the indices of where in expression are 
* the extra parentheses to be removed.
*/
void TwentyFour::remove_extra_parentheses(vector<string>& expres_as_vec, vector<int>& indices) {
  Stack stack;
  for (int i = 0; i < expres_as_vec.size(); i++) {
    if (expres_as_vec[i] == "(") {
      stack.push(i);
    } else if (expres_as_vec[i] == ")") {
      if (stack.empty()) {
        indices.push_back(i);
      } else {
        int last_bracket_index = stack.top();
        stack.pop();
        string enclosed = "";
        for (int j = last_bracket_index + 1; j < i; j++) {
          enclosed += expres_as_vec[j];
        }
        bool is_enclosed_digit = true;
        for (char c : enclosed) {
          if (!is_digit(c)) {
            is_enclosed_digit = false;
            break;
          }
        }
        if (is_enclosed_digit) {
          indices.push_back(i);
          indices.push_back(last_bracket_index);
        }
      }
    }
  }
  while (!stack.empty()) {
    indices.push_back(stack.top());
    stack.pop();
  }
}

/**
* This function calls on previous helper functions to 
* clean up the input expression by removing extra spaces and parentheses.
* @param expression: the expression to be cleaned up.
* @return expression: the cleaned-up expression as a string.
*/
string TwentyFour::clean_brackets(string& expression) {
  vector<string> expres_as_vec;
  expression_to_vec(expres_as_vec, expression);
  vector<int> indices;
  remove_spaces(expres_as_vec, indices);
  remove_extra_parentheses(expres_as_vec, indices);
  sort(indices.begin(), indices.end());
  indices.erase(unique(indices.begin(), indices.end()), indices.end());
  string result = "";
  for (int i = 0; i < expres_as_vec.size(); i++) {
    if (find(indices.begin(), indices.end(), i) == indices.end()) {
      result += expres_as_vec[i];
    }
  }
  expression = result;
  return expression;
}

/**
* This function checks if a given set of numbers and expressions can be combined to form the number 24,
* returning true and saving the correct expression which makes 24, by reference. 
* If the function does not evaluate to 24, false is returned.
* @param numbers: a math combination of vector doubles to be checked for operations.
* @param expr: the string expression of the math combination.
* @param final_expression: a string reference parameter to store the final string expression.
* @return: a boolean value indicating whether the final expression is valid and equal to 24.
*/
bool TwentyFour::checker(vector<double> &numbers, vector<string> &expr,
             string &final_expression) {
  vector<string> string_nums;
  for (auto n : numbers) {
    int truncated_num = static_cast<int>(n);
    string string_num = to_string(truncated_num);
    string_nums.push_back(string_num);
  }
  if (numbers.size() == 2) {
    vector<double> answers = operations(numbers[0], numbers[1]);
    string A = string_nums[0];
    string B = string_nums[1];
    vector<vector<string>> answer_exps = operation_expression(A, B);
    for (size_t i = 0; i < answers.size(); i++) {
      double answer = answers[i];
      double threshold = pow(10.0, -5);
      if (abs(answer - final_24) <= threshold) {
        final_expression =
            convert_expr_to_string(expr[0], expr[1], answer_exps[i]);
        return true;
      }
    }
  }
  return false;
}

/**
* Returns the order of of the given math operation.
* @param op: the math operator to get the order for.
* @return double: the order in which operators are evaluated, with (2), meaning that multiplication and division
* would be computed before (1) addition and subtraction.
* Function returns 0 if the operator is not valid.
*/
double TwentyFour::order(char op){
  if(op == '+'||op == '-')
  return 1;
  if(op == '*'||op == '/')
  return 2;
  return 0;
}

/**
* Performs basic math operations (+, -, *, /) with high precision.
* @param a: the first double number in the operation.
* @param b: the second double number in the operation.
* @param op: the math operation to perform.
* @return double: the result of the math operation.
*/

// CITE: https://en.cppreference.com/w/cpp/language/switch
// DESC: I know what is a switch operator now. It is a shorter way of writing 
// if statements and returning values by cases.
double TwentyFour::math_precision_operations(double a, double b, char op){
  switch(op){
      case '+': return ((double)a + (double)b);
      case '-': return ((double)a - (double)b);
      case '*': return ((double)a * (double)b);
      case '/': return ((double)a / (double)b);
  }
  return -1;
}

/**
* Function computes math expression using a stack for the operations and a stack for the numbers.
* @param expres_as_vec: the arithmetic expression as a string.
* @param values: a Stack of doubles to store the numbers.
* @param operators: a Stack of characters to store the math operators.
* @return double: the result of the math expression.
*/
double TwentyFour::compute_expression(string expres_as_vec, StackD &values, StackC &operators){
  for(long unsigned int i = 0; i < expres_as_vec.length(); i++){
      if(expres_as_vec[i] == ' '){
          continue;
      }
      else if(expres_as_vec[i] == '('){
          push_op(operators, expres_as_vec[i]);
      }
      else if(isdigit(expres_as_vec[i])){
          push_number(expres_as_vec, i, values);
      }
      else if(expres_as_vec[i] == ')'){
          process_close_paren(operators, values);
      }
      else{
          process_operator(expres_as_vec[i], operators, values);
      }
  }
  process_remaining_operators(operators, values);
  return values.top();
}

/**
* This function pushes an operator onto the operator stack.
* @param operators: a Stack of characters representing the operator stack.
* @param op: a character representing the math operator to be pushed onto the stack.
*/
void TwentyFour::push_op(StackC& operators, char op){
    operators.push(op);
}

/**
* This function pushes numbers into a stack of double numbers.
* @param expres_as_vec: a math expression as a string.
* @param i: a long unsigned integer representing the current index in the string.
* @param values: a Stack of doubles used to store the operands.
*/
void TwentyFour::push_number(const string& expres_as_vec, long unsigned int& i, StackD& values){
    double val = 0;
    while(i < expres_as_vec.length() && isdigit(expres_as_vec[i])){
        val = (val*10) + (expres_as_vec[i]-'0');
        i++;
    }
    values.push(val);
    i--;
}

/**
* This function processes closes parentheses in the math operation.
* @param operators: a Stack of characters representing the math operators in the stack.
* @param values: a Stack of doubles representing the numbers in the stack.
*/
void TwentyFour::process_close_paren(StackC& operators, StackD& values){
    while(!operators.empty() && operators.top() != '('){
        double num2 = values.top();
        values.pop();
        double num1 = values.top();
        values.pop();
        char op = operators.top();
        operators.pop();
        double operators_res = math_precision_operations(num1, num2, op);
        values.push(operators_res);
    }
    if(!operators.empty())
        operators.pop();
}

/**
* Function processes the math operators and performs the calculations in 
* the math expression.
* @param op: the math operator as a character.
* @param operators: a Stack of characters representing the math operators in the stack.
* @param values: a Stack of doubles representing the numbers in the stack.
*/
void TwentyFour::process_operator(char op, StackC& operators, StackD& values){
    while(!operators.empty() && order(operators.top()) >= order(op)){
        double num2 = values.top();
        values.pop();
        double num1 = values.top();
        values.pop();
        char op1 = operators.top();
        operators.pop();
        double operation_result = math_precision_operations(num1, num2, op1);
        values.push(operation_result);
    }
    operators.push(op);
}

/**
* Function does calculations on any remaining operators.
* @param operators: a Stack of characters representing the math operators in the stack.
* @param values: a Stack of doubles representing the numbers in the stack.
*/
void TwentyFour::process_remaining_operators(StackC& operators, StackD& values){
    while(!operators.empty()){
        double num2 = values.top();
        values.pop();       
        double num1 = values.top();
        values.pop();
        char op = operators.top();
        operators.pop();
        double op_res = math_precision_operations(num1, num2, op);
        values.push(op_res);
    }
}

/**
* Function checks to 5 decimal places if the string_result is sufficiently close to the constant number 24.
* @param final_expression: the math expression as a string.
* @return: a boolean true or false whether the expression evaluates to 24.
*/
bool TwentyFour::final_checker(string final_expression){
  StackD values;
  StackC operators;
 double result = compute_expression(final_expression, values, operators);
 double difference = abs(((double)result - (double)final_24));
 if (difference < threshold){
  return true;
  }
 return false;
}

/**
* This helper function takes in a vector of double numbers and generates 
* a vector of initial expressions that represent the numbers as strings.
* @param numbers: a vector of double numbers to generate expressions from.
* @return vector<string>: a vector of string expressions generated from the input numbers.
*/
vector<string> generate_initial_expr(vector<double>& numbers) {
  vector<string> expr;
  for (auto n : numbers) {
    int truncated_num = static_cast<int>(n);
    string string_num = to_string(truncated_num);
    expr.push_back(string_num);
  }
  return expr;
}


/**
* This helper function takes in a vector of double numbers and generates 
* all possible pairs of numbers that can be generated from the input vector.
* @param numbers: a vector of double numbers to generate pairs from.
* @return vector<vector<double>>: a vector of vector pairs of double numbers.
*/
vector<vector<double>> generate_number_pairs(vector<double>& numbers) {
  vector<vector<double>> pairs;
  for (int i = 0; i < numbers.size(); i++) {
    for (int j = i + 1; j < numbers.size(); j++) {
      pairs.push_back({numbers[i], numbers[j]});
    }
  }
  return pairs;
}

/**
* This helper function takes in two double numbers and generates all possible values that can be
* obtained from applying the basic operations (+, -, *, /) to the input numbers.
* @param a: a double number, could be initial number from list or a higher layer result from math operation(s).
* @param b: a double number, could be initial number from list or a higher layer result from math operation(s).
* @return vector<double>: a vector of double numbers representing all possible values that can
*/
vector<double> generate_possible_values(double a, double b) {
  return operations(a, b);
}

/**
* This helper function takes in two double numbers and generates all possible expressions that can
* be obtained from applying the basic operations (+, -, *, /) to the input numbers.
* @param a: a double number.
* @param b: a double number.
* @return vector<vector<string>>: a vector of vector strings representing all possible
* expressions that can be obtained from applying the basic operations to the input numbers.
*/
vector<vector<string>> generate_possible_expressions(double a, double b) {
  string C = to_string(a);
  string D = to_string(b);
  return operation_expression(C, D);
}

/**
* This helper function takes in the vector of double numbers and vector of string expressions
* and gives a possible expression.
* @param numbers: a vector of double numbers.
* @param expr: a vector of string expressions.
* @param a_index: an integer representing the index of the first number to replace.
* @param b_index: an integer representing the index of the second number to replace.
* @param value: the result of applying an operation to the input numbers.
* @param expr_string: a string representing the expression used to obtain the result.
*/
void replace_numbers_and_expression(vector<double>& numbers, vector<string>& expr, 
  int a_index, int b_index, int value, string expr_string) {
  numbers.erase(numbers.begin() + b_index);
  numbers.erase(numbers.begin() + a_index);
  expr.erase(expr.begin() + b_index);
  expr.erase(expr.begin() + a_index);
  numbers.push_back(value);
  expr.push_back(expr_string);
}

/**
* A helper function to solve the game 24 recursively. It generates all possible combinations
* of pairs of numbers and evaluates them using all possible arithmetic operations.
* Helper functions and checkers above are called to evaluate and validate expressions.
* @param numbers a vector of 4 doubles representing the numbers to be used for generating
* possible solutions.
* @param expr a vector of strings representing the expressions generated so far for the given
* numbers.
* @param all_solutions a vector of strings that will store all the valid
* solutions to the 24 game.
*/
void TwentyFour::solve_24_recursive_helper(vector<double> numbers, vector<string> expr, 
  vector<string>& all_solutions) {
  string final_expression;
  vector<vector<double>> pairs = generate_number_pairs(numbers);
  for (auto pair : pairs) {
    vector<double> possible_values = generate_possible_values(pair[0], pair[1]);
    vector<vector<string>> possible_expr = generate_possible_expressions(pair[0], pair[1]);
    for (int i = 0; i < possible_values.size() - 1; i++) {
      int value = possible_values[i];
      vector<string> expression = possible_expr[i];
      int a_index = find(numbers.begin(), numbers.end(), pair[0]) - numbers.begin();
      int b_index = find(numbers.begin(), numbers.end(), pair[1]) - numbers.begin();
      if (a_index == b_index) {
        b_index = find(numbers.begin() + a_index + 1, numbers.end(), pair[1]) - numbers.begin();
      }
      string expr_string = convert_expr_to_string(expr[a_index], expr[b_index], expression);
      vector<double> new_numbers = numbers;
      vector<string> new_expr = expr;
      replace_numbers_and_expression(new_numbers, new_expr, a_index, b_index, value, expr_string);
      solve_24_recursive_helper(new_numbers, new_expr, all_solutions);
      final_expression = "";
      if (checker(new_numbers, new_expr, final_expression)) {
        final_expression = clean_brackets(final_expression);
        if (final_checker(final_expression)) {
          all_solutions.push_back(final_expression);
        }
        return;
      }
    }
  }
}

/**
* This function is called to solve the game 24. It generates an initial set of expressions
* for the given numbers and calls on the solve_24_recursive_helper() function to find all the valid
* solutions to the problem, which are passed by reference in a vector of strings.
* @param numbers a reference to a vector of 4 doubles representing the numbers to be used for generating
* possible solutions.
* @param all_solutions a reference to a vector of strings that will store all the solutions to 24.
*/
void TwentyFour::solve_24(vector<double>& numbers, vector<string>& all_solutions) {
  vector<string> expr = generate_initial_expr(numbers);
  solve_24_recursive_helper(numbers, expr, all_solutions);
}

/**
* This function is used in the multiplayer mode of 24.
* This program keeps generating random numbers till we have a set of 4 numbers
* each between 1 and 13 (like in the physical card game) solveable for 24.
*/
// CITE: https://cplusplus.com/reference/cstdlib/rand/
// DESC: rand() helps generate random numbers from a range of numbers.
vector<double> TwentyFour::generate_random_numbers(){
  vector<double> v;
    for (int i = 0; i < 4; i++) {
      int rand_int = rand() % 13 + 1;
      v.push_back(rand_int);
  }
  vector<string> expr;
  if (!is_there_solution(v)){
    v = generate_random_numbers();
    return v;
  }
  return v;
}

/**
 * Checks if a vector is present in a 2D vector
 * @param vec_2d: the 2D vector to search for the vector
 * @param vec: the vector to search for
 * @return true if vec is found in vec_2d, false otherwise
 */
bool is_vector_in_2d_vector(vector<vector<double>>& vec_2d, vector<double>& vec) {
  for (auto v : vec_2d) {
      if (v == vec) {
          return true;
      }
  }
  return false;
}

/**
 * Generates all possible permutations of 4 numbers.
 * @param numbers: the numbers to permute
 * @param permutations: the 2D vector to store the permutations
 * @param combo: the current combination being generated
 * @param count: the current count of numbers in the combination
 */
void generate_permutations(vector<double>& numbers, 
  vector<vector<double>>& permutations, vector<double>& combo, int count) {
    if (count == 4) {
        if (!is_vector_in_2d_vector(permutations, combo)) {
            permutations.push_back(combo);
        }
        return;
    }
    for (int i = 0; i < numbers.size(); i++) {
        combo[count] = numbers[i];
        generate_permutations(numbers, permutations, combo, count + 1);
    }
}

/**
* Generates all possible permutations of 4 numbers from the input vector.
* @param numbers The input vector of numbers.
* @return A vector of vectors representing all possible permutations of 4 numbers.
*/
vector<vector<double>> permutations_of_4(vector<double> numbers) {
    vector<vector<double>> permutations;
    vector<double> combo(4);
    generate_permutations(numbers, permutations, combo, 0);
    return permutations;
}

/**
 * Checks if the characters in a vector match the characters in a string.
 * @param vec: the vector of characters to check.
 * @param str: the string to compare against.
 * @return true if the counts of characters in vec match the counts in str, false otherwise.
 */
bool check_correct_numbers(const vector<char>& vec, const string& str) {
  vector<int> vec_count(4, 0);
  vector<int> str_count(4, 0);
  for (int i = 0; i < vec.size(); i++) {
      vec_count[i] = count(vec.begin(), vec.end(), vec[i]);
  }
  for (int i = 0; i < str.length(); i++) {
      char ch = str[i];
      if (find(vec.begin(), vec.end(), ch) != vec.end()) {
          int index = distance(vec.begin(), find(vec.begin(), vec.end(), ch));
          str_count[index]++;
      }
  }
  // Check if the counts for each character matches
  for (int i = 0; i < vec_count.size(); i++) {
      if (vec_count[i] != str_count[i]) {
          return false;
      }
  }
  return true;
}

/**
* Remove solutions from the vector of strings that have incorrect numbers
* @param nums a vector of doubles of the original numbers.
* @param solutions a vector of strings of all possible solutions.
*/
bool all_numbers_present(const vector<double>& original_numbers, const string& solution) {
  vector<int> nums(original_numbers.size());
    transform(original_numbers.begin(), original_numbers.end(), nums.begin(), [](double d) {
      return static_cast<int>(d);
  });
  string temp = solution;
  for (int num : nums) {
    size_t found = temp.find(to_string(num));
    if (found == string::npos) {
      return false;
    }
    temp.erase(found, 1);
  }
  return true;
}

/**
 * Generates all unique solutions for the game 24.
 * @param original_numbers: the original numbers to use in the game
 * @param expression: the expression to evaluate to 24 as a vector of strings.
 * @return a vector of unique solutions that evaluate to 24
 */
vector<string> TwentyFour::get_all_unique_solutions(vector<double> &original_numbers,
  vector<string> expression){
  vector<vector<double>> all_permutations = permutations_of_4(original_numbers);
  vector<string> all_solutions;
  for (int i = 0; i < all_permutations.size(); i++) {
    solve_24(all_permutations[i], all_solutions);
  }
  vector<string> unique_solutions;
  for (int i = 0; i < all_solutions.size(); i++) {
    bool push = true;
    for (int k = 0; k < unique_solutions.size(); k++) {
      if (all_solutions[i] == unique_solutions[k]) {
        push = false;
      }
    }
    if (push == true and (all_numbers_present(original_numbers, all_solutions[i]))) {
      unique_solutions.push_back(all_solutions[i]);
    }
  }
  return unique_solutions;
}
