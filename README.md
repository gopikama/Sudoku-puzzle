# Sudoku puzzle

Objective of this project is to take an initial sudoku configuration as input, fill each square in the sudoku ensuring that the game rule is satisfied, using A* final algorithm. The rule is that each row column and sub grid should have numbers from 1-9 without overlap.

The execution time (ET), the number of nodes generated (NG), the number of nodes expanded (NE), the depth of the tree (D), and effective branching factor b* (NG/D) and Total path (TP) for each run has been observed. Additionally, a comparative analysis of results with programs that utilize a different heuristic ahs been done. This analysis aims to provide insights into the efficacy of data structures, code logic, and heuristic functions used in the implementation.

Based on test case analysis candidate reduction heuristic performs better than zero counting heuristic. To know more about this program and its performance analysis please read the Sudoku_puzzle_analysis.pdf attached.

