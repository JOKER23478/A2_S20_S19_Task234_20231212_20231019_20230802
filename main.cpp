#include "game1.h"
#include "game2.h"
#include "game3.h"
#include "game4.h"
#include "game5.h"
#include "game6.h"
#include "game7.h"
#include "game8.h"
#include "game9.h"
#include "BoardGame_Classes.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
void playgame1() {
    PyramidBoard board;
    string player1, player2;
    char x = 'X', o = 'O';
    int choice;

    cout << "Welcome to Pyramid Tic-Tac-Toe!\n";
    cout << "Choose game mode: (1) Player vs Player or (2) Player vs Computer: ";
    cin >> choice;

    if (choice == 1) {
        cout << "Enter Player 1 name: ";
        cin >> player1;
        cout << "Enter Player 2 name: ";
        cin >> player2;
    }
    else {
        cout << "Enter your name: ";
        cin >> player1;
        player2 = "Computer";
    }

    bool player1Turn = true;
    random_device rd;
    mt19937 gen(rd());

    while (true) {
        board.displayBoard();
        string currentPlayer = player1Turn ? player1 : player2;
        char currentSymbol = player1Turn ? x : o;

        int row, col;

        if (choice == 2 && !player1Turn) { // Computer's turn
            while (true) {
                uniform_int_distribution<> rowDist(1, 3); // Random row (1-3)
                row = rowDist(gen);

                uniform_int_distribution<> colDist(1, board.rowSize(row));
                col = colDist(gen);

                if (board.updateBoard(row, col, currentSymbol)) {
                    cout << "Computer played: Row " << row << ", Column " << col << endl;
                    break;
                }
            }
        }
        else { // Player's turn
            while (true) {
                cout << currentPlayer << ", enter the row (1-3): ";
                cin >> row;

                if (cin.fail() || row < 1 || row > 3) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid choice. Please try again.\n";
                    continue;
                }

                cout << currentPlayer << ", enter the column (1-" << board.rowSize(row) << "): ";
                cin >> col;

                if (cin.fail() || col < 1 || col > board.rowSize(row)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid choice. Please try again.\n";
                    continue;
                }

                if (board.updateBoard(row, col, currentSymbol)) {
                    break;
                }
                else {
                    cout << "Cell is already occupied. Please try again.\n";
                }
            }
        }

        char winner = board.checkWin();
        if (winner != ' ') {
            board.displayBoard();
            cout << (winner == x ? player1 : player2) << " wins!\n";
            break;
        }

        if (board.isFull()) {
            board.displayBoard();
            cout << "The game is a draw!\n";
            break;
        }

        player1Turn = !player1Turn;
    }
}
void playgame2() {
    FourInARowBoard board;
    FourInARowPlayer player1("Player 1", 'X');
    FourInARowPlayer player2("Player 2", 'O');
    player1.setBoard(&board);
    player2.setBoard(&board);
    Player<char>* players[2] = { &player1, &player2 };
    GameManager<char> gameManager(&board, players);
    gameManager.run();
}
void playgame3(){
    char mode;
    cout << "1 - Computer (Random Player)\n"
        << "2 - Real Player\n";
    cout << "Enter your choice: ";
    cin >> mode;

    if (mode == '1') {
        play3_5TicTacToe<char>(true);
    }
    else if (mode == '2') {
        play3_5TicTacToe<char>(false);
    }
    else {
        cout << "Invalid mode selected. Please try again.\n";
    }
}
void playgame4() {
    srand(time(0));
    game4 g;
    string f = "dic.txt";  // Dictionary file

    // Initialize the game with the dictionary file
    if (!g.initialize(f)) {
        return;  // Exit if dictionary loading fails
    }

    string p1, p2;
    bool isComputer = false;

    cout << "Welcome to Word Tic-Tac-Toe!\n";
    cout << "Player 1, enter your name: ";
    cin >> p1;
    cout << "Do you want to play against the computer? (yes/no): ";
    string ch;
    cin >> ch;

    // If Player 2 is the computer, set up the game accordingly
    if (ch == "yes") {
        p2 = "Computer";
        isComputer = true;
    }
    else {
        cout << "Player 2, enter your name: ";
        cin >> p2;
    }

    bool p1Turn = true;

    while (true) {
        g.displayBoard();
        string currentPlayer = p1Turn ? p1 : p2;
        char currentLetter;
        int x, y;

        // Computer's turn (random move and random letter)
        if (isComputer && !p1Turn) {
            cout << "Computer is making a move...\n";
            pair<int, int> compMove = g.getRandomMove();
            int compX = compMove.first;
            int compY = compMove.second;
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dist(0, 25);
            currentLetter = 'A' + dist(gen);  // Random letter
            x = compX;
            y = compY;
        }
        else {
            // Player's turn: choose letter and row/column
            cout << currentPlayer << ", enter your letter: ";
            string letterInput;
            cin >> letterInput;

            // Check for valid single letter
            if (letterInput.length() != 1 || !isalpha(letterInput[0])) {
                cout << "Error: Please enter a single alphabetical letter.\n";
                continue;
            }
            currentLetter = letterInput[0];

            cout << currentPlayer << ", enter the row (1-3): ";
            if (!(cin >> x) || x < 1 || x > 3) {
                cout << "Error: Invalid row. Please enter a number between 1 and 3.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            cout << currentPlayer << ", enter the column (1-3): ";
            if (!(cin >> y) || y < 1 || y > 3) {
                cout << "Error: Invalid column. Please enter a number between 1 and 3.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
        }

        // Place the letter on the board
        if (!g.placeLetter(x, y, currentLetter)) {
            continue;
        }

        // Check for a winner or a full board
        if (g.isWinner()) {
            g.displayBoard();
            cout << currentPlayer << " wins!\n";
            break;
        }

        if (g.isBoardFull()) {
            g.displayBoard();
            cout << "The game is a draw!\n";
            break;
        }

        // Switch turns
        p1Turn = !p1Turn;
    }
}
void playgame5(){
    NumericalTicTacToeBoard board;
    vector<int> odd_numbers = { 1, 3, 5, 7, 9 };
    vector<int> even_numbers = { 2, 4, 6, 8 };
    NumericalTicTacToePlayer player1("Player 1", 1, odd_numbers);
    NumericalTicTacToePlayer player2("Player 2", 2, even_numbers);
    player1.setBoard(&board);
    player2.setBoard(&board);
    Player<int>* players[2] = { &player1, &player2 };
    GameManager<int> gameManager(&board, players);
    gameManager.run();
}
void playgame6(){
    char mode;
    cout << "1 - Computer random player\n";
    cout << "2 - Real player\n";
    cout << "Enter your choice: ";
    cin >> mode;

    if (mode == '1') {
        playMisereTicTacToe(true);
    }
    else if (mode == '2') {
        playMisereTicTacToe(false);
    }
    else {
        cout << "Invalid choice. Please select 1 or 2.\n";
    }
}
void playgame8() {
    cout << "1 - Computer Random Player\n" << "2 - Real Player\n";
    cout << "Enter your choice: ";
    char mode; cin >> mode;
    UltimateBoard board;
    if (mode == '1') {
        player player1("Player 1", 'X');
        RandomComputerPlayer player2("Computer", 'O');
        play_game(board, player1, player2);
    }
    else {
        player player1("Player 1", 'X');
        player player2("Player 2", 'O');
        play_game(board, player1, player2);
    }
}
void playgame9() {
    char mode;
    cout << "Welcome to the SUS Game!\n";
    cout << "Select Game Mode:\n1. Player vs Player\n2. Player vs Computer\n";
    cin >> mode;
    SUSGameBoard board;
    Player<char>* players[2];
    if (mode == '1') {
        string name1, name2;
        cout << "Enter Player 1 name: ";
        cin >> name1;
        cout << "Enter Player 2 name: ";
        cin >> name2;

        players[0] = new HumanPlayer(name1, 'S');
        players[1] = new HumanPlayer(name2, 'U');
    }
    else { 
        string name1;
        cout << "Enter your name: ";
        cin >> name1;
        players[0] = new HumanPlayer(name1, 'S');
        players[1] = new SUSRandomPlayer('U');
    }
    players[0]->setBoard(&board);
    players[1]->setBoard(&board);
    GameManager<char> gameManager(&board, players);
    gameManager.run();
    delete players[0];
    delete players[1];
}
int main() {
    while (true) {
        char choice;
        cout << "Welcome to FCAI Arcade Games\n"
            << "1 - Pyramid Tic-Tac-Toe\n"
            << "2 - Four-in-a-Row\n"
            << "3 - 5x5 Tic-Tac-Toe\n"
            << "4 - Word Tic-Tac-Toe\n"
            << "5 - Numerical Tic-Tac-Toe\n"
            << "6 - Misere Tic-Tac-Toe\n"
            << "7 - 4x4 Tic-Tac-Toe\n"
            << "8 - Ultimate Tic-Tac-Toe\n"
            << "9 - SUS\n"
            << "0 - Exit\n";
        cout << "Choose from the menu the game number you want: ";
        cin >> choice;
        if (choice == '1')
            playgame1();
        else if (choice == '2')
            playgame2();
        else if (choice == '3')
            playgame3();
        else if (choice == '4')
            playgame4();
        else if (choice == '5')
            playgame5();
        else if (choice == '6')
            playgame6();
        else if (choice == '7') {
            srand(time(0));
            TicTacToe4x4 game;
            game.start_game();
        }
        else if (choice == '8')
            playgame8();
        else if (choice == '9')
            playgame9();
        else if (choice == '0')
            exit(0);
        else cout << "choose a number from the manu\n";
    }
    return 0;
}