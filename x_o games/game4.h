#pragma once
#ifndef GAME4_H
#define GAME4_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>
using namespace std;

class game4 {
private:
    vector<vector<char>> b;  // Board (3x3 grid)
    vector<string> dic;      // Dictionary to check valid words

    // Load dictionary from file
    bool loaddic(const string& f) {
        ifstream file(f);
        if (!file) {
            cerr << "Error: Unable to open dictionary file!" << endl;
            return false;
        }

        string w;
        while (file >> w) {
            dic.push_back(w);
        }
        file.close();
        return true;
    }

    // Check if the word exists in the dictionary
    bool isValidWord(const string& w) const {
        return find(dic.begin(), dic.end(), w) != dic.end();
    }

    // Check if there's a winner on the board
    bool checkWinningCondition() {
        // Check rows
        for (int i = 0; i < 3; ++i) {
            string r = "";
            for (int j = 0; j < 3; ++j) {
                r += b[i][j];
            }
            if (isValidWord(r)) return true;
        }

        // Check columns
        for (int j = 0; j < 3; ++j) {
            string c = "";
            for (int i = 0; i < 3; ++i) {
                c += b[i][j];
            }
            if (isValidWord(c)) return true;
        }

        // Check diagonals
        string d1 = "", d2 = "";
        for (int i = 0; i < 3; ++i) {
            d1 += b[i][i];
            d2 += b[i][2 - i];
        }
        if (isValidWord(d1) || isValidWord(d2)) return true;

        return false;
    }

public:
    // Constructor: Initializes the board (3x3 with empty spaces)
    game4() : b(3, vector<char>(3, ' ')) {}

    // Initialize the game by loading the dictionary from a file
    bool initialize(const string& f) {
        return loaddic(f);
    }

    // Display the game board
    void displayBoard() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout << "|_" << (b[i][j] == ' ' ? ' ' : b[i][j]) << "_";
            }
            cout << "|\n";
        }
    }

    // Place a letter on the board at the specified position (1-indexed)
    bool placeLetter(int x, int y, char l) {
        if (x < 1 || x > 3 || y < 1 || y > 3 || b[x - 1][y - 1] != ' ') {
            cout << "Invalid move. Try again.\n";
            return false;
        }
        b[x - 1][y - 1] = l;
        return true;
    }

    // Check if there's a winner
    bool isWinner() {
        return checkWinningCondition();
    }

    // Check if the board is full
    bool isBoardFull() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (b[i][j] == ' ') return false;
            }
        }
        return true;
    }

    // Get a random move for the computer
    pair<int, int> getRandomMove() {
        vector<pair<int, int>> emptyCells;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (b[i][j] == ' ') {
                    emptyCells.emplace_back(i + 1, j + 1);
                }
            }
        }
        if (!emptyCells.empty()) {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dist(0, emptyCells.size() - 1);
            return emptyCells[dist(gen)];
        }
        return { -1, -1 };
    }
};

#endif

