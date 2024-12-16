#pragma once
#ifndef GAME2_H
#define GAME2_H
#include <iostream>
#include "BoardGame_Classes.h"
#include <cstdlib>
#include <ctime>
using namespace std;
class FourInARowBoard : public Board<char> {
public:
    FourInARowBoard() {
        rows = 6;
        columns = 7;
        board = new char* [rows];
        for (int i = 0; i < rows; ++i) {
            board[i] = new char[columns];
            for (int j = 0; j < columns; ++j) {
                board[i][j] = ' ';
            }
        }
    }
    bool update_board(int x, int y, char symbol) override {
        if (x < 0 || x >= rows || y < 0 || y >= columns || board[x][y] != ' ') {
            return false;
        }
        board[x][y] = symbol;
        n_moves++;
        return true;
    }

    void display_board() override {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                cout << "|" << board[i][j];
            }
            cout << "|\n";
        }
    }

    bool is_win() override {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                if (board[i][j] != ' ' && (
                    check_direction(i, j, 1, 0) ||
                    check_direction(i, j, 0, 1) ||
                    check_direction(i, j, 1, 1) ||
                    check_direction(i, j, 1, -1)))
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool is_draw() override {
        return n_moves == rows * columns;
    }

    bool game_is_over() override {
        if (is_win()) {
            display_board();
            cout << "Game Over! We have a winner!\n";
            return true;
        }
        return is_draw();
    }

    int getRows() const { return rows; }
    int getColumns() const { return columns; }
    char** getBoard() const { return board; }

private:
    bool check_direction(int x, int y, int dx, int dy) {
        char symbol = board[x][y];
        for (int k = 1; k < 4; ++k) {
            int nx = x + k * dx;
            int ny = y + k * dy;
            if (nx < 0 || nx >= rows || ny < 0 || ny >= columns || board[nx][ny] != symbol) {
                return false;
            }
        }
        return true;
    }
};

class FourInARowPlayer : public Player<char> {
public:
    FourInARowPlayer(string n, char symbol) : Player(n, symbol) {}

    void getmove(int& x, int& y) override {
        cout << name << ", enter move (column): ";
        cin >> y;
        x = static_cast<FourInARowBoard*>(boardPtr)->getRows() - 1;
        while (x >= 0 && static_cast<FourInARowBoard*>(boardPtr)->getBoard()[x][y] != ' ') {
            x--;
        }
    }
};
#endif