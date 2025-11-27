# 24 Game

A C++ implementation of the mathematical card game "24" with multiple game modes including single-player, multiplayer, and freeplay options.

**Authors:** Benjamin Zhao, Leonardo Li  
**Institution:** Hamilton College  
**Course:** Computer Science, Data Structures & Algorithms

---

## Overview

The 24 Game challenges players to use four numbers and basic arithmetic operations (+, −, ×, ÷) to reach the target number 24. This implementation uses recursive algorithms, stacks, and expression parsing to generate and validate solutions.

**Key Features:**
- Automatic solution generation for any valid set of 4 numbers
- Multiple game modes (single-player, multiplayer, freeplay)
- Expression validation and evaluation using custom stack implementation
- Generates all unique solutions with proper parenthesization

---

## Game Modes

### Freeplay Mode
Players enter their own four numbers and attempt to solve for 24.

<img src="Screenshot 2024-02-08 at 4.42.00 PM.png" alt="Freeplay Mode" width="600">

*Example: Given numbers 13, 5, 1, 9, the solution (13-9)×(5+1) evaluates to 24*

### Multiplayer Mode
Compete against other players with randomly generated numbers.

<img src="Screenshot 2024-02-08 at 4.45.52 PM.png" alt="Multiplayer Mode" width="600">

*Players have 20 seconds to find a solution. The program verifies answers and shows all possible solutions*

---

## Installation

### Prerequisites
- C++ compiler (g++ recommended)
- Make utility

### Build Instructions

```bash
# Clone the repository
git clone https://github.com/benz3927/24.git
cd 24

# Compile using make
make

# Run the program
./main input.txt
```

---

## Usage

### Input Format

Create an `input.txt` file with space-separated numbers:
```
13 5 1 9
```

### Running the Game

```bash
./main input.txt
```

The program will:
1. Read the four numbers from the input file
2. Give you 20 seconds to solve
3. Prompt for your solution
4. Validate your answer
5. Display all possible solutions

---

## Algorithm

### Solution Generation

The program uses a **recursive approach** to generate all possible solutions:

1. **Generate pairs**: Create all possible pairs of numbers from the input
2. **Apply operations**: For each pair, apply +, −, ×, ÷ operations
3. **Recurse**: Replace the pair with the result and recursively solve with remaining numbers
4. **Validate**: Check if the expression evaluates to 24 (within 10⁻⁵ tolerance)

### Expression Evaluation

Uses **two-stack algorithm** for expression parsing:
- **Values stack**: Stores operands
- **Operators stack**: Stores operators with precedence handling
- Supports parenthesized expressions with proper order of operations

### Key Data Structures

- **Stack**: Custom stack implementation for expression evaluation
- **Vectors**: Store numbers, expressions, and solutions
- **Recursion**: Generate all permutations and combinations

---

## Technical Highlights

### Expression Parsing
```cpp
// Cleans up expressions by removing unnecessary parentheses
string clean_brackets(string& expression);

// Evaluates expressions using two-stack algorithm
double compute_expression(string expres_as_vec, StackD &values, StackC &operators);
```

### Solution Validation
```cpp
// Checks if expression evaluates to 24 (within 10^-5 tolerance)
bool final_checker(string final_expression);

// Verifies all original numbers are used
bool all_numbers_present(const vector<double>& original_numbers, const string& solution);
```

### Random Number Generation
```cpp
// Generates solvable sets of 4 random numbers (1-13)
vector<double> generate_random_numbers();
```

---

## Project Structure

```
24/
├── TwentyFour.cpp       # Core game logic and algorithms
├── TwentyFour.h         # TwentyFour class header
├── stack.cpp            # Custom stack implementation
├── stack.h              # Stack class header
├── node.cpp             # Node implementation for stack
├── node.h               # Node class header
├── game.cpp             # Game mode implementations
├── game.h               # Game class header
├── player.cpp           # Player management
├── player.h             # Player class header
├── main.cpp             # Entry point
├── makefile             # Build configuration
└── input.txt            # Sample input file
```

---

## Example Solutions

For numbers **13, 5, 1, 9**:
```
(13-9)×(5+1) = 24
(5+1)×(13-9) = 24
(13-9)×(1+5) = 24
(1+5)×(13-9) = 24
```

For numbers **3, 3, 8, 8**:
```
8÷(3-8÷3) = 24
```

---

## Implementation Details

### Precision Handling
- Uses double precision for intermediate calculations
- Validates final result within 10⁻⁵ tolerance to handle floating-point errors
- Properly handles division by zero

### Expression Generation
- Generates all permutations of input numbers
- Creates all possible operator combinations
- Removes duplicate solutions
- Validates that original numbers are preserved

---

## Features

✅ **Automatic solution generation** - Finds all unique solutions  
✅ **Expression validation** - Verifies arithmetic correctness  
✅ **Multiple game modes** - Single-player, multiplayer, freeplay  
✅ **Timed challenges** - 20-second solve timer  
✅ **Clean parenthesization** - Removes unnecessary brackets  
✅ **Robust parsing** - Handles complex nested expressions  

---

## Compilation

```bash
# Using make
make

# Manual compilation
g++ -std=c++11 -o main main.cpp TwentyFour.cpp stack.cpp node.cpp game.cpp player.cpp
```

---

## Testing

Example test cases included:
```
13 5 1 9    → Multiple solutions
3 3 8 8     → Requires division
1 1 1 1     → No solution (program regenerates in multiplayer)
```

---

## Contributors

- **Benjamin Zhao** ([@benz3927](https://github.com/benz3927))
- **Leonardo Li** ([@bzhao3927](https://github.com/bzhao3927))

---

## Acknowledgments

- **Data Structures & Algorithms Course** - Hamilton College
- Inspired by the classic 24 card game
- Uses custom stack implementation for expression evaluation

---

## License

Educational project - Hamilton College Computer Science

---

## Contact

**Benjamin Zhao** - bzhao@hamilton.edu  
Hamilton College, Computer Science Department
