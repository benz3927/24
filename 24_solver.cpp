/**
 * Standalone 24 Game Solver
 * A comprehensive brute-force solver that finds all solutions to the 24 game
 * using any 4 numbers with basic arithmetic operations (+, -, *, /)
 * 
 * Usage: g++ -o solver solver_24_standalone.cpp && ./solver
 * 
 * Authors: Benjamin Zhao, Leonardo Li
 * Updated: 2025 - Added comprehensive solver with all parenthesization patterns
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <sstream>
using namespace std;

class TwentyFourSolver {
private:
    const double THRESHOLD = 1e-9;
    
    // Perform arithmetic operation with error handling
    double calculate(double a, double b, char op) {
        switch(op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': return (b != 0) ? a / b : -999;
            default: return -999;
        }
    }
    
    // Check if result is approximately 24
    bool isTarget(double result) {
        return abs(result - 24.0) < THRESHOLD;
    }
    
    // Try all 5 parenthesization patterns for given numbers and operators
    bool findSolution(double a, double b, double c, double d, char op1, char op2, char op3, string& solution) {
        vector<char> operators = {'+', '-', '*', '/'};
        
        // Pattern 1: ((a op1 b) op2 c) op3 d
        double temp1 = calculate(a, b, op1);
        if (temp1 != -999) {
            double temp2 = calculate(temp1, c, op2);
            if (temp2 != -999) {
                double result = calculate(temp2, d, op3);
                if (isTarget(result)) {
                    solution = "((" + to_string((int)a) + string(1,op1) + to_string((int)b) + ")" + 
                              string(1,op2) + to_string((int)c) + ")" + string(1,op3) + to_string((int)d);
                    return true;
                }
            }
        }
        
        // Pattern 2: (a op1 (b op2 c)) op3 d  
        temp1 = calculate(b, c, op2);
        if (temp1 != -999) {
            double temp2 = calculate(a, temp1, op1);
            if (temp2 != -999) {
                double result = calculate(temp2, d, op3);
                if (isTarget(result)) {
                    solution = "(" + to_string((int)a) + string(1,op1) + "(" + to_string((int)b) + 
                              string(1,op2) + to_string((int)c) + "))" + string(1,op3) + to_string((int)d);
                    return true;
                }
            }
        }
        
        // Pattern 3: a op1 ((b op2 c) op3 d)
        temp1 = calculate(b, c, op2);
        if (temp1 != -999) {
            double temp2 = calculate(temp1, d, op3);
            if (temp2 != -999) {
                double result = calculate(a, temp2, op1);
                if (isTarget(result)) {
                    solution = to_string((int)a) + string(1,op1) + "((" + to_string((int)b) + 
                              string(1,op2) + to_string((int)c) + ")" + string(1,op3) + to_string((int)d) + ")";
                    return true;
                }
            }
        }
        
        // Pattern 4: a op1 (b op2 (c op3 d))
        temp1 = calculate(c, d, op3);
        if (temp1 != -999) {
            double temp2 = calculate(b, temp1, op2);
            if (temp2 != -999) {
                double result = calculate(a, temp2, op1);
                if (isTarget(result)) {
                    solution = to_string((int)a) + string(1,op1) + "(" + to_string((int)b) + 
                              string(1,op2) + "(" + to_string((int)c) + string(1,op3) + to_string((int)d) + "))";
                    return true;
                }
            }
        }
        
        // Pattern 5: (a op1 b) op2 (c op3 d)
        temp1 = calculate(a, b, op1);
        double temp2 = calculate(c, d, op3);
        if (temp1 != -999 && temp2 != -999) {
            double result = calculate(temp1, temp2, op2);
            if (isTarget(result)) {
                solution = "(" + to_string((int)a) + string(1,op1) + to_string((int)b) + ")" + 
                          string(1,op2) + "(" + to_string((int)c) + string(1,op3) + to_string((int)d) + ")";
                return true;
            }
        }
        
        return false;
    }

public:
    // Main solver function - finds first solution for given 4 numbers
    string solve(vector<int> numbers) {
        if (numbers.size() != 4) {
            return "Error: Need exactly 4 numbers";
        }
        
        vector<char> operators = {'+', '-', '*', '/'};
        
        // Try all permutations of numbers
        sort(numbers.begin(), numbers.end());
        do {
            double a = numbers[0], b = numbers[1], c = numbers[2], d = numbers[3];
            
            // Try all combinations of operators
            for (char op1 : operators) {
                for (char op2 : operators) {
                    for (char op3 : operators) {
                        string solution;
                        if (findSolution(a, b, c, d, op1, op2, op3, solution)) {
                            return solution;
                        }
                    }
                }
            }
        } while (next_permutation(numbers.begin(), numbers.end()));
        
        return "No solution found";
    }
    
    // Find all unique solutions
    vector<string> findAllSolutions(vector<int> numbers) {
        if (numbers.size() != 4) {
            return {"Error: Need exactly 4 numbers"};
        }
        
        vector<string> allSolutions;
        vector<char> operators = {'+', '-', '*', '/'};
        
        // Try all permutations of numbers
        sort(numbers.begin(), numbers.end());
        do {
            double a = numbers[0], b = numbers[1], c = numbers[2], d = numbers[3];
            
            // Try all combinations of operators
            for (char op1 : operators) {
                for (char op2 : operators) {
                    for (char op3 : operators) {
                        string solution;
                        if (findSolution(a, b, c, d, op1, op2, op3, solution)) {
                            // Check if this solution is already found
                            bool isDuplicate = false;
                            for (const string& existing : allSolutions) {
                                if (existing == solution) {
                                    isDuplicate = true;
                                    break;
                                }
                            }
                            if (!isDuplicate) {
                                allSolutions.push_back(solution);
                            }
                        }
                    }
                }
            }
        } while (next_permutation(numbers.begin(), numbers.end()));
        
        if (allSolutions.empty()) {
            allSolutions.push_back("No solution found");
        }
        
        return allSolutions;
    }
};

// Interactive main function
int main() {
    TwentyFourSolver solver;
    
    cout << "=== 24 Game Solver ===" << endl;
    cout << "Find expressions using 4 numbers that equal 24" << endl;
    cout << "Operations allowed: + - * /" << endl << endl;
    
    while (true) {
        cout << "Enter 4 integers (or 'quit' to exit): ";
        string input;
        getline(cin, input);
        
        if (input == "quit" || input == "q") {
            cout << "Thanks for using the 24 Game Solver!" << endl;
            break;
        }
        
        // Parse input
        vector<int> numbers;
        istringstream iss(input);
        int num;
        while (iss >> num) {
            numbers.push_back(num);
        }
        
        if (numbers.size() != 4) {
            cout << "Please enter exactly 4 numbers." << endl << endl;
            continue;
        }
        
        cout << "Numbers: ";
        for (int n : numbers) cout << n << " ";
        cout << endl;
        
        // Find all solutions
        vector<string> solutions = solver.findAllSolutions(numbers);
        
        if (solutions.size() == 1 && solutions[0] == "No solution found") {
            cout << "No solution exists for these numbers." << endl;
        } else {
            cout << "Found " << solutions.size() << " solution(s):" << endl;
            for (int i = 0; i < solutions.size(); i++) {
                cout << "  " << (i + 1) << ". " << solutions[i] << " = 24" << endl;
            }
        }
        cout << endl;
    }
    
    return 0;
}