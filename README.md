# 🧩 C++ Programming Fundamentals (FP2)

A collection of C++ projects developed for the **Programming Fundamentals II** course. This repository showcases the progression from basic procedural programming with multidimensional arrays to Object-Oriented Programming (OOP) and algorithmic optimization.

## 📂 Project Structure

| Project | Focus Area | Key Concepts |
| :--- | :--- | :--- |
| **[Multidimensional_Arrays](./Multidimensional_Arrays)** | **Algorithmic Logic** | Competitive programming style exercises. Matrix manipulation and traversal algorithms. |
| **[Practica_Sudoku](./Practica_Sudoku)** | **Procedural C++** | Implementation of a classic Sudoku game using raw multidimensional arrays. Focuses on game loop logic and state validation. |
| **[Practica_Sudoku_2](./Practica_Sudoku_2)** | **OOP & Complexity Optimization** | Advanced Sudoku engine. Implements a custom `Multiset` class to manage game states, drastically **reducing time complexity** and eliminating redundant matrix searches. |

## 💡 Key Takeaways
* **Algorithmic Efficiency:** The transition from `Practica_Sudoku` to `Practica_Sudoku_2` demonstrates a practical application of Big O notation, upgrading from brute-force searches to optimized data structures.
* **Memory Management:** Safe handling of arrays and custom class destructors in C++.

## 🛠️ Technologies
* **Language:** C++ (Standard `std::c++11` or higher)
* **Paradigm:** Procedural & Object-Oriented Programming (OOP)

## 🚀 How to Run
*(Note: Ensure you have `g++` or another C++ compiler installed)*

1. Navigate to the desired project folder:
   ```bash
   cd Practica_Sudoku_2

2. Compile the source files (compiles all .cpp files in the directory):
    ```bash
    g++ -Wall -o sudoku *.cpp

3. Execute the game:
    ```bash
    ./sudoku