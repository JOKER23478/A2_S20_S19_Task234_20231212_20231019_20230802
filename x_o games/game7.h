#pragma once
#ifndef GAME7_H
#define GAME7_H
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <random>
#include <ctime>
using namespace std;
class TicTacToe4x4 {
private:
    vector<vector<char>> b;
    string p1, p2;
    bool is_ai;

    void init_board() {
        b = {
            {'X', 'O', 'X', 'O'},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {'O', 'X', 'O', 'X'}
        };
    }

    void show_board() {
        cout << "  1   2   3   4\n";
        for (int x = 0; x < 4; ++x) {
            cout << x + 1 << " ";
            for (int y = 0; y < 4; ++y) {
                cout << "| " << b[x][y] << " ";
            }
            cout << "|\n";
        }
        cout << "\n";
    }

    bool valid_move(int r1, int c1, int r2, int c2, char t) {
        r1--;
        c1--;
        r2--;
        c2--;

        if (r2 < 0 || r2 >= 4 || c2 < 0 || c2 >= 4) return false;
        if (b[r2][c2] != ' ') return false;
        if (b[r1][c1] != t) return false;
        if (abs(r1 - r2) + abs(c1 - c2) != 1) return false; // Ensure adjacency
        return true;
    }

    bool check_win(char t) {
        // Check rows
        for (int x = 0; x < 4; ++x) {
            for (int y = 0; y < 2; ++y) {
                if (b[x][y] == t && b[x][y + 1] == t && b[x][y + 2] == t) {
                    return true;
                }
            }
        }

        // Check columns
        for (int y = 0; y < 4; ++y) {
            for (int x = 0; x < 2; ++x) {
                if (b[x][y] == t && b[x + 1][y] == t && b[x + 2][y] == t) {
                    return true;
                }
            }
        }

        // Check diagonals
        for (int x = 0; x < 2; ++x) {
            for (int y = 0; y < 2; ++y) {
                if (b[x][y] == t && b[x + 1][y + 1] == t && b[x + 2][y + 2] == t) {
                    return true;
                }
                if (b[x][y + 2] == t && b[x + 1][y + 1] == t && b[x + 2][y] == t) {
                    return true;
                }
            }
        }

        return false;
    }

    pair<int, int> comp_move(char t) {
        vector<pair<int, int>> valid_moves;

        for (int x = 0; x < 4; ++x) {
            for (int y = 0; y < 4; ++y) {
                if (b[x][y] == t) {
                    int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
                    for (auto dir : directions) {
                        int nx = x + dir[0];
                        int ny = y + dir[1];
                        if (nx >= 0 && nx < 4 && ny >= 0 && ny < 4 && b[nx][ny] == ' ') {
                            valid_moves.emplace_back(x * 4 + y, nx * 4 + ny);
                        }
                    }
                }
            }
        }

        if (!valid_moves.empty()) {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dist(0, valid_moves.size() - 1);
            int move_index = dist(gen);
            return valid_moves[move_index];
        }

        return { -1, -1 };  // No valid moves
    }

    void player_input(const string& p, char t, int& r1, int& c1, int& r2, int& c2) {
        while (true) {
            cout << p << ", select the token row (1-4): ";
            cin >> r1;
            if (cin.fail() || r1 < 1 || r1 > 4) {
                cout << "Error: Invalid choice. Try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            cout << p << ", select the token column (1-4): ";
            cin >> c1;
            if (cin.fail() || c1 < 1 || c1 > 4) {
                cout << "Error: Invalid choice. Try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            cout << p << ", select the new row (1-4): ";
            cin >> r2;
            if (cin.fail() || r2 < 1 || r2 > 4) {
                cout << "Error: Invalid choice. Try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            cout << p << ", select the new column (1-4): ";
            cin >> c2;
            if (cin.fail() || c2 < 1 || c2 > 4) {
                cout << "Error: Invalid choice. Try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (valid_move(r1, c1, r2, c2, t)) {
                break;
            }
            else {
                cout << "Invalid move. Try again.\n";
            }
        }
    }

public:
    TicTacToe4x4() : is_ai(false) { init_board(); }

    void start_game() {
        cout << "Welcome to 4x4 Tic-Tac-Toe!\n";
        cout << "Enter Player 1 name: ";
        cin >> p1;

        cout << "Do you want to play against the computer? (yes/no): ";
        string choice;
        cin >> choice;
        if (choice == "yes") {
            p2 = "Computer";
            is_ai = true;
        }
        else {
            cout << "Enter Player 2 name: ";
            cin >> p2;
        }

        char token = 'X';
        string player = p1;

        while (true) {
            show_board();

            int r1, c1, r2, c2;

            if (is_ai && player == p2) {
                cout << "Computer is making a move...\n";
                auto move = comp_move(token);  
                auto from = move.first;       
                auto to = move.second;       
                if (from == -1) {
                    cout << "No valid moves for Computer.\n";
                    break;
                }
                r1 = from / 4 + 1;
                c1 = from % 4 + 1;
                r2 = to / 4 + 1;
                c2 = to % 4 + 1;
            }
            else {
                player_input(player, token, r1, c1, r2, c2);
            }

            b[r2 - 1][c2 - 1] = token;
            b[r1 - 1][c1 - 1] = ' ';

            if (check_win(token)) {
                show_board();
                cout << player << " wins!\n";
                break;
            }
            token = (token == 'X') ? 'O' : 'X';  // Corrected 'x' to 'X'
            player = (player == p1) ? p2 : p1;

        }


        cout << "Game over!\n";
    }
};
#endif