# Data Structures Final Project

This project analyzes and compares the efficiency of two data structures: **Binary Search Tree** and **AVL Tree**.

## Overview

The application reads a `.csv` file containing a list of games and their average play time. These data are stored in both trees.  
Then, a wishlist of games is processed, and each game is searched independently in both data structures.
The program computes the total estimated play time of the wishlist and outputs performance statistics for each tree.

## Collected Statistics

For each data structure, the following metrics are reported:
- Tree height
- Number of nodes
- Number of rotations
- Number of comparisons performed during the search

## Input Files

The executable receives **three command-line arguments**:
1. A `.csv` file containing game names and their average play time
2. A `.txt` file with the user's wishlist
3. A `.txt` output file where the results are written

## How to Run
```bash
datastructures-project.exe <games.csv> <wishlist.txt> <output.txt>
