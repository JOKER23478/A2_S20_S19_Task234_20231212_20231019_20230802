#pragma once
#ifndef GAME1_H
#define GAME1_H
#include <iostream>
#include <vector>
#include <random>
#include <string>
using namespace std;
class PyramidBoard {
private:
    vector<vector<char>> board;

public:
    PyramidBoard() {
        board = { {' '}, {' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' '} }; // Pyramid shape
    }
    void displayBoard() {
        for (size_t i = 0; i < board.size(); ++i) {
            for (int j = 0; j < (board.size() - 1 - i) * 3; ++j) cout << " "; // Center alignment
            for (size_t j = 0; j < board[i].size(); ++j) {
                cout << "|_" << board[i][j] << "_";
            }
            cout << "|" << endl;
        }
    }
    bool updateBoard(int row, int col, char symbol) {
        row -= 1; // Convert 1-based to 0-based indexing
        col -= 1;

        if (row >= 0 && row < static_cast<int>(board.size()) &&
            col >= 0 && col < static_cast<int>(board[row].size()) &&
            board[row][col] == ' ') {
            board[row][col] = symbol;
            return true;
        }
        return false;
    }

    char checkWin() {
        // Check rows
        for (const auto& row : board) {
            for (size_t i = 0; i + 2 < row.size(); ++i) {
                if (row[i] != ' ' && row[i] == row[i + 1] && row[i] == row[i + 2]) {
                    return row[i];
                }
            }
        }

        // Check verticals and diagonals
        for (size_t i = 0; i < board.size(); ++i) {
            for (size_t j = 0; j < board[i].size(); ++j) {
                // Vertical
                if (i + 2 < board.size() && board[i][j] != ' ' &&
                    j < board[i + 1].size() && board[i][j] == board[i + 1][j] &&
                    j < board[i + 2].size() && board[i][j] == board[i + 2][j]) {
                    return board[i][j];
                }

                // Diagonal
                if (i + 2 < board.size() && j + 2 < board[i + 1].size() && board[i][j] != ' ' &&
                    board[i][j] == board[i + 1][j + 1] && board[i][j] == board[i + 2][j + 2]) {
                    return board[i][j];
                }

                if (i + 2 < board.size() && j >= 2 && board[i][j] != ' ' &&
                    board[i][j] == board[i + 1][j - 1] && board[i][j] == board[i + 2][j - 2]) {
                    return board[i][j];
                }
            }
        }
        return ' '; // No winner yet
    }

    int rowSize(int row) const {
        row -= 1; // Convert 1-based to 0-based indexing
        if (row >= 0 && row < static_cast<int>(board.size())) {
            return static_cast<int>(board[row].size());
        }
        return 0;
    }

    bool isFull() const {
        for (const auto& row : board) {
            for (char cell : row) {
                if (cell == ' ') return false;
            }
        }
        return true;
    }
};
#endif