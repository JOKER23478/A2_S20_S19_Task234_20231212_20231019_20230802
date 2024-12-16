#pragma once
#ifndef GAME5_H
#define GAME5_H
#include <iostream>
#include "BoardGame_Classes.h"
#include <vector>
#include <algorithm>
using namespace std;
class NumericalTicTacToeBoard : public Board<int> {
public:
    NumericalTicTacToeBoard() {
        rows = 3;
        columns = 3;
        board = new int* [rows];
        for (int i = 0; i < rows; ++i) {
            board[i] = new int[columns];
            for (int j = 0; j < columns; ++j) {
                board[i][j] = 0;
            }
        }
    }

    bool update_board(int x, int y, int number) override {
        if (x < 0 || x >= rows || y < 0 || y >= columns || board[x][y] != 0) {
            return false;
        }
        board[x][y] = number;
        n_moves++;
        return true;
    }

    void display_board() override {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                if (board[i][j] == 0) {
                    cout << "| ";
                }
                else {
                    cout << "|" << board[i][j];
                }
            }
            cout << "|\n";
        }
    }

    bool is_win() override {
        for (int i = 0; i < rows; ++i) {
            if (board[i][0] + board[i][1] + board[i][2] == 15) return true;
        }
        for (int j = 0; j < columns; ++j) {
            if (board[0][j] + board[1][j] + board[2][j] == 15) return true;
        }
        if (board[0][0] + board[1][1] + board[2][2] == 15) return true;
        if (board[0][2] + board[1][1] + board[2][0] == 15) return true;
        return false;
    }

    bool is_draw() override {
        return n_moves == rows * columns;
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

class NumericalTicTacToePlayer : public Player<int> {
private:
    vector<int> available_numbers;
public:
    NumericalTicTacToePlayer(string n, int symbol, vector<int> numbers) : Player(n, symbol), available_numbers(numbers) {}

    void getmove(int& x, int& y) override {
        int number;
        cout << name << ", enter move (row column number): ";
        cin >> x >> y >> number;
        while (find(available_numbers.begin(), available_numbers.end(), number) == available_numbers.end()) {
            cout << "Invalid number. Enter a valid number: ";
            cin >> number;
        }
        available_numbers.erase(remove(available_numbers.begin(), available_numbers.end(), number), available_numbers.end());
    }
};
#endif