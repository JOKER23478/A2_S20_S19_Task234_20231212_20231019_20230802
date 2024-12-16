#pragma once
#ifndef GAME6_H
#define GAME6_H
#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime> 
using namespace std;
class MisereTicTacToe {
private:
    vector<vector<char>> board;
    int moves;
    char currentPlayer;
    bool checkRows(char symbol);
    bool checkColumns(char symbol);
    bool checkDiagonals(char symbol);
public:
    MisereTicTacToe();
    void displayBoard();
    bool makeMove(int x, int y);
    bool isGameOver();
    bool isLoss(char symbol);
    void switchPlayer();
    char getCurrentPlayer();
};
MisereTicTacToe::MisereTicTacToe() {
    board = vector<vector<char>>(3, vector<char>(3, ' '));
    moves = 0;
    srand(time(0));
    currentPlayer = (rand() % 2 == 0) ? 'X' : 'O';
}
void MisereTicTacToe::displayBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << " " << (board[i][j] != ' ' ? board[i][j] : ' ') << " ";
            if (j < 2) cout << "|";
        }
        cout << "\n";
        if (i < 2) cout << "---|---|---\n";
    }
    cout << "\n";
}
bool MisereTicTacToe::makeMove(int x, int y) {
    if (x < 0 || x >= 3 || y < 0 || y >= 3 || board[x][y] != ' ') {
        cout << "Invalid move! Try again.\n";
        return false;
    }

    board[x][y] = currentPlayer;
    moves++;
    return true;
}
bool MisereTicTacToe::checkRows(char symbol) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) {
            return true;
        }
    }
    return false;
}
bool MisereTicTacToe::checkColumns(char symbol) {
    for (int j = 0; j < 3; j++) {
        if (board[0][j] == symbol && board[1][j] == symbol && board[2][j] == symbol) {
            return true;
        }
    }
    return false;
}
bool MisereTicTacToe::checkDiagonals(char symbol) {
    return (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) ||
        (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol);
}
bool MisereTicTacToe::isLoss(char symbol) {
    return checkRows(symbol) || checkColumns(symbol) || checkDiagonals(symbol);
}
bool MisereTicTacToe::isGameOver() {
    return moves == 9 || isLoss(currentPlayer);
}
void MisereTicTacToe::switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}
char MisereTicTacToe::getCurrentPlayer() {
    return currentPlayer;
}
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear"); // For UNIX-like systems
#endif
}
void playMisereTicTacToe(bool isComputerPlayer) {
    MisereTicTacToe game;
    srand(time(0));
    cout << "Welcome to Misere Tic Tac Toe!\n";
    cout << "Players take turns placing their symbol (X or O) on the board.\n";
    cout << "The player who completes three in a row, column, or diagonal loses the game.\n\n";
    game.displayBoard();
    while (!game.isGameOver()) {
        int x, y;
        if (isComputerPlayer && game.getCurrentPlayer() == 'O') {
            do {
                x = rand() % 3;
                y = rand() % 3;
            } while (!game.makeMove(x, y));

            cout << "Computer (O) made its move: " << x << ", " << y << "\n";
        }
        else {
            cout << "Player " << game.getCurrentPlayer() << "'s turn. Enter row (0-2) and column (0-2): ";
            cin >> x >> y;
            if (!game.makeMove(x, y)) {
                cout << "Invalid move, try again.\n";
                continue;
            }
        }clearScreen();
        game.displayBoard();
        if (game.isLoss(game.getCurrentPlayer())) {
            cout << "Player " << game.getCurrentPlayer() << " loses! Game over.\n";
            return;
        }
        game.switchPlayer();
    }
    cout << "It's a draw! No one loses.\n";
}
#endif