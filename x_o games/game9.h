#pragma once
#ifndef GAME9_H
#define GAME9_H
#include "boardgame_classes.h"
#include <iostream>
#include <cstdlib> // For rand()
#include <ctime>   // For seeding random numbers

using namespace std;

// SUSGameBoard: Derived from Board<char> (implements SUS game rules)
class SUSGameBoard : public Board<char> {
public:
    SUSGameBoard() {
        rows = columns = 3;
        board = new char* [rows];
        for (int i = 0; i < rows; i++) {
            board[i] = new char[columns];
            for (int j = 0; j < columns; j++) {
                board[i][j] = ' '; // Initialize board with empty spaces
            }
        }
    }

    bool update_board(int x, int y, char symbol) override {
        if (x >= 0 && x < rows && y >= 0 && y < columns && board[x][y] == ' ') {
            board[x][y] = symbol;
            n_moves++;
            return true;
        }
        cout << "Invalid move. Try again.\n";
        return false;
    }

    void display_board() override {
        cout << "\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                cout << board[i][j];
                if (j < columns - 1) cout << " | ";
            }
            cout << "\n";
            if (i < rows - 1) cout << "--|---|--\n";
        }
        cout << "\n";
    }

    bool is_win() override {
        // Check rows, columns, and diagonals for "SUS" pattern
        string sus = "SUS";

        // Check rows
        for (int i = 0; i < rows; i++) {
            string row = "";
            for (int j = 0; j < columns; j++) row += board[i][j];
            if (row == sus) return true;
        }

        // Check columns
        for (int j = 0; j < columns; j++) {
            string col = "";
            for (int i = 0; i < rows; i++) col += board[i][j];
            if (col == sus) return true;
        }

        // Check diagonals
        string diag1 = "", diag2 = "";
        for (int i = 0; i < rows; i++) {
            diag1 += board[i][i];
            diag2 += board[i][rows - 1 - i];
        }
        if (diag1 == sus || diag2 == sus) return true;

        return false;
    }

    bool is_draw() override {
        return (n_moves == rows * columns && !is_win());
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

// HumanPlayer: Inherits from Player<char>
class HumanPlayer : public Player<char> {
public:
    HumanPlayer(string n, char symbol) : Player<char>(n, symbol) {}
    void getmove(int& x, int& y) override {
        cout << name << " (" << symbol << "), enter your move (row and column): ";
        cin >> x >> y;
        x--; y--; // Convert to 0-based index
    }
};

// RandomPlayer (Computer): Inherits from Player<char>
class SUSRandomPlayer : public RandomPlayer<char> {
public:
    SUSRandomPlayer(char symbol) : RandomPlayer<char>(symbol) {
        srand(time(0));
    }

    void getmove(int& x, int& y) override {
        x = rand() % 3; // Random row (0-2)
        y = rand() % 3; // Random column (0-2)
        cout << "Computer (" << symbol << ") plays at (" << x + 1 << ", " << y + 1 << ")\n";
    }
};
#endif