#pragma once
#ifndef GAME3_H
#define GAME3_H
#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;
// Base class: Board
template <typename T>
class Board67 {
protected:
    int rows, columns;
    T** board;
    int n_moves;

public:
    virtual ~Board67() {
        for (int i = 0; i < rows; i++) {
            delete[] board[i];
        }
        delete[] board;
    }

    virtual bool update_board(int x, int y, T symbol) = 0;
    virtual void display_board() = 0;
    virtual bool is_win() = 0;
    virtual bool is_draw() = 0;
    virtual bool game_is_over() = 0;

    int get_rows() const { return rows; }
    int get_columns() const { return columns; }
};

// Derived class: X_O_Board
template <typename T>
class X_O_Board : public Board67<T> {
public:
    X_O_Board();
    ~X_O_Board();

    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;

    int get_x_wins() const { return x_wins; }
    int get_o_wins() const { return o_wins; }

private:
    int x_wins = 0;
    int o_wins = 0;
    int check_rows(T symbol);
    int check_columns(T symbol);
    int check_diagonals(T symbol);
    int count_sequences(T symbol);
};

// Constructor
template <typename T>
X_O_Board<T>::X_O_Board() {
    this->rows = this->columns = 5;
    this->board = new T * [this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = ' '; 
        }
    }
    this->n_moves = 0;
}

// Destructor
template <typename T>
X_O_Board<T>::~X_O_Board() {
    for (int i = 0; i < this->rows; i++) {
        delete[] this->board[i];
    }
    delete[] this->board;
}

// Update board
template <typename T>
bool X_O_Board<T>::update_board(int x, int y, T symbol) {
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != ' ') {
        return false;
    }
    this->board[x][y] = symbol;
    ++this->n_moves;
    int wins = count_sequences(symbol);
    if (symbol == 'X') x_wins = wins;
    else if (symbol == 'O') o_wins = wins;

    return true; 
}

// Display board
template <typename T>
void X_O_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << setw(2) << (this->board[i][j] != ' ' ? this->board[i][j] : ' ') << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// Check if the game is won
template <typename T>
bool X_O_Board<T>::is_win() {
    return (x_wins > 0 || o_wins > 0);
}

// Check if the game is a draw
template <typename T>
bool X_O_Board<T>::is_draw() {
    return this->n_moves == this->rows * this->columns && !is_win();
}

// Check if the game is over
template <typename T>
bool X_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

// Check rows
template <typename T>
int X_O_Board<T>::check_rows(T symbol) {
    int count = 0;
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j <= this->columns - 3; j++) {
            if (this->board[i][j] == symbol &&
                this->board[i][j + 1] == symbol &&
                this->board[i][j + 2] == symbol) {
                count++;
            }
        }
    }
    return count;
}

// Check columns
template <typename T>
int X_O_Board<T>::check_columns(T symbol) {
    int count = 0;
    for (int j = 0; j < this->columns; j++) {
        for (int i = 0; i <= this->rows - 3; i++) {
            if (this->board[i][j] == symbol &&
                this->board[i + 1][j] == symbol &&
                this->board[i + 2][j] == symbol) {
                count++;
            }
        }
    }
    return count;
}

// Check diagonals
template <typename T>
int X_O_Board<T>::check_diagonals(T symbol) {
    int count = 0;
    for (int i = 0; i <= this->rows - 3; i++) {
        for (int j = 0; j <= this->columns - 3; j++) {
            if (this->board[i][j] == symbol &&
                this->board[i + 1][j + 1] == symbol &&
                this->board[i + 2][j + 2] == symbol) {
                count++;
            }
        }
    }
    for (int i = 0; i <= this->rows - 3; i++) {
        for (int j = 2; j < this->columns; j++) {
            if (this->board[i][j] == symbol &&
                this->board[i + 1][j - 1] == symbol &&
                this->board[i + 2][j - 2] == symbol) {
                count++;
            }
        }
    }
    return count;
}
// Count all sequences for a symbol
template <typename T>
int X_O_Board<T>::count_sequences(T symbol) {
    return check_rows(symbol) + check_columns(symbol) + check_diagonals(symbol);
}

// Player class
template <typename T>
class Player53 {
protected:
    string name;
    T symbol;
    Board67<T>* boardPtr;

public:
    Player53(string n, T sym) : name(n), symbol(sym), boardPtr(nullptr) {};
    virtual ~Player53() {}
    virtual void getmove(int& x, int& y) = 0;
    void setBoard(Board67<T>* b) { boardPtr = b; }
    string getName() const { return name; }
};

// RealPlayer class
template <typename T>
class RealPlayer : public Player53<T> {
public:
    RealPlayer(string n, T sym) : Player53<T>(n, sym) {}

    void getmove(int& x, int& y) override {
        cout << this->name << "'s turn. Enter row (0-4) and column (0-4): ";
        cin >> x >> y;
        while (!this->boardPtr->update_board(x, y, this->symbol)) {
            cout << "Invalid move. Try again: ";
            cin >> x >> y;
        }
    }
};

// RandomPlayer class
template <typename T>
class RandomPlayer20 : public Player53<T> {
public:
    RandomPlayer20(T sym) : Player53<T>("Random Player", sym) {
        srand(static_cast<unsigned>(time(0))); 
    }
    void getmove(int& x, int& y) override {
        do {
            x = rand() % this->boardPtr->get_rows();
            y = rand() % this->boardPtr->get_columns();
        } while (!this->boardPtr->update_board(x, y, this->symbol));
    }
};

// Play function
template <typename T>
void play3_5TicTacToe(bool isRandomPlayer) {
    X_O_Board<T> board;
    Player53<T>* player1;
    Player53<T>* player2;
    cout << "enter the name of player 1 : ";
    string kanke; cin >> kanke;
    cout << endl;
    if (isRandomPlayer) {
        player1 = new RandomPlayer20<T>('X');
    }
    else {
        cout << "enter the name of player 2 : ";
        string kanke2; cin >> kanke2;
        player1 = new RealPlayer<T>(kanke2, 'X');
    }
    player2 = new RealPlayer<T>(kanke, 'O');

    player1->setBoard(&board);
    player2->setBoard(&board);

    int x, y;
    while (!board.game_is_over()) {
        system("cls"); // Clear screen
        board.display_board();
        cout << "Player X winning sequences: " << board.get_x_wins() << "\n";
        cout << "Player O winning sequences: " << board.get_o_wins() << "\n";

        // Player 1 move
        player1->getmove(x, y);
        if (board.is_win() || board.is_draw()) break;

        system("cls"); // Clear screen
        board.display_board();
        cout << "Player X winning sequences: " << board.get_x_wins() << "\n";
        cout << "Player O winning sequences: " << board.get_o_wins() << "\n";

        // Player 2 move
        player2->getmove(x, y);
        if (board.is_win() || board.is_draw()) break;
    }

    board.display_board(); // Final board
    if (board.is_win()) {
        cout << "We have a winner!\n";
    }
    else if (board.is_draw()) {
        cout << "It's a draw!\n";
    }

    delete player1;
    delete player2;
}

#endif
