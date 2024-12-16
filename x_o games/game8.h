#pragma once
#ifndef GAME8_H
#define GAME8_H
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Represents the smaller 3x3 Tic Tac Toe board
class SmallBoard {
public:
    char board[3][3]; 
    SmallBoard() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                board[i][j] = ' ';
            }
        }
    }
    bool update_board(int x, int y, char symbol) {
        if (x >= 0 && x < 3 && y >= 0 && y < 3 && board[x][y] == ' ') {
            board[x][y] = symbol;
            return true;
        }
        return false;
    }
    bool is_win() const {
        for (int i = 0; i < 3; ++i) {
            if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) return true;
            if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) return true;
        }
        if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) return true;
        if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) return true;
        return false;
    }
    bool is_draw() const {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == ' ') return false;
            }
        }
        return !is_win();
    }
};

// Represents the Ultimate Tic Tac Toe board
class UltimateBoard : public Board<char> {
private:
    SmallBoard subBoards[3][3]; 
    char mainBoard[3][3];
public:
    UltimateBoard() {
        rows = columns = 9; 
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                mainBoard[i][j] = ' ';
            }
        }
    }
    void display_board() override {
        for (int bigRow = 0; bigRow < 3; ++bigRow) { 
            for (int subRow = 0; subRow < 3; ++subRow) { 
                for (int bigCol = 0; bigCol < 3; ++bigCol) {
                    for (int col = 0; col < 3; ++col) { 
                        cout << subBoards[bigRow][bigCol].board[subRow][col]; 
                        if (col < 2) cout << "|";
                    }
                    if (bigCol < 2) cout << " || ";
                }
                cout << endl;
            }
            if (bigRow < 2) {
                cout << "-+-+- || -+-+- || -+-+-\n"
                    << "-+-+- || -+-+- || -+-+-\n";
            }
        }
    }
    bool update_board(int x, int y, char symbol) override {
        int mainX = x / 3, mainY = y / 3;
        int subX = x % 3, subY = y % 3;

        if (mainBoard[mainX][mainY] == ' ' && subBoards[mainX][mainY].update_board(subX, subY, symbol)) {
            if (subBoards[mainX][mainY].is_win()) {
                mainBoard[mainX][mainY] = symbol;
            }
            ++n_moves; 
            return true;
        }
        return false;
    }
    bool is_win() override {
        for (int i = 0; i < 3; ++i) {
            if (mainBoard[i][0] != ' ' && mainBoard[i][0] == mainBoard[i][1] && mainBoard[i][1] == mainBoard[i][2]) return true;
            if (mainBoard[0][i] != ' ' && mainBoard[0][i] == mainBoard[1][i] && mainBoard[1][i] == mainBoard[2][i]) return true;
        }
        if (mainBoard[0][0] != ' ' && mainBoard[0][0] == mainBoard[1][1] && mainBoard[1][1] == mainBoard[2][2]) return true;
        if (mainBoard[0][2] != ' ' && mainBoard[0][2] == mainBoard[1][1] && mainBoard[1][1] == mainBoard[2][0]) return true;
        return false;
    }
    bool is_draw() override {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (mainBoard[i][j] == ' ') return false;
            }
        }
        return !is_win();
    }
    bool game_is_over() override {
        return is_win() || is_draw();
    }
};
class player {
public:
    string name; 
    char symbol;
    player(string name, char symbol) : name(name), symbol(symbol) {}
    virtual void get_move(int& x, int& y) const {
        cout << name << " (" << symbol << "), enter your move (row, col)(1-3): ";
        cin >> x >> y;
    }
};
class RandomComputerPlayer : public player {
public:
    RandomComputerPlayer(string name, char symbol) : player(name, symbol) {
        srand(time(0));
    }
    void get_move(int& x, int& y) const override {
        x = rand() % 9;
        y = rand() % 9;
        cout << name << " (" << symbol << ") is making a random move..." << endl;
    }
};
void play_game(UltimateBoard& board, player& player1, player& player2) {
    int x, y;
    player* currentPlayer = &player1;
    while (!board.game_is_over()) {
        system("cls");
        board.display_board();
        currentPlayer->get_move(x, y);
        while (!board.update_board(x, y, currentPlayer->symbol)) {
            cout << "Invalid move. Try again." << endl;
            currentPlayer->get_move(x, y);
        }
        currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
    }
    board.display_board();
    if (board.is_win()) {
        cout << (currentPlayer == &player1 ? player2.name : player1.name) << " wins!" << endl;
    }
    else {
        cout << "It's a draw!" << endl;
    }
}
#endif