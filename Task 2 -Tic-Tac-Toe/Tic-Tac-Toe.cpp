#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const char HUMAN = 'X';
const char AI = 'O';
const char EMPTY = ' ';

// Function prototypes
void printBoard(const vector<vector<char>>& board);
bool isMovesLeft(const vector<vector<char>>& board);
int evaluate(const vector<vector<char>>& board);
int minimax(vector<vector<char>>& board, int depth, bool isMax);
int findBestMove(vector<vector<char>>& board);

// Function to print the board
void printBoard(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (char cell : row) {
            cout << (cell == EMPTY ? '-' : cell) << " ";
        }
        cout << endl;
    }
}

// Function to check if moves are left on the board
bool isMovesLeft(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (char cell : row) {
            if (cell == EMPTY) return true;
        }
    }
    return false;
}

// Function to evaluate the board
int evaluate(const vector<vector<char>>& board) {
    // Check rows for a win
    for (int row = 0; row < 3; ++row) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == AI) return +10;
            else if (board[row][0] == HUMAN) return -10;
        }
    }

    // Check columns for a win
    for (int col = 0; col < 3; ++col) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == AI) return +10;
            else if (board[0][col] == HUMAN) return -10;
        }
    }

    // Check diagonals for a win
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == AI) return +10;
        else if (board[0][0] == HUMAN) return -10;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == AI) return +10;
        else if (board[0][2] == HUMAN) return -10;
    }

    // If no winner
    return 0;
}

// Minimax algorithm
int minimax(vector<vector<char>>& board, int depth, bool isMax) {
    int score = evaluate(board);

    // If AI wins
    if (score == 10) return score - depth;

    // If HUMAN wins
    if (score == -10) return score + depth;

    // If no moves left and no winner
    if (!isMovesLeft(board)) return 0;

    if (isMax) {
        int best = numeric_limits<int>::min();
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = AI;
                    best = max(best, minimax(board, depth + 1, false));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    } else {
        int best = numeric_limits<int>::max();
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = HUMAN;
                    best = min(best, minimax(board, depth + 1, true));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    }
}

// Function to find the best move for AI
int findBestMove(vector<vector<char>>& board) {
    int bestVal = numeric_limits<int>::min();
    int bestMove = -1;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == EMPTY) {
                board[i][j] = AI;
                int moveVal = minimax(board, 0, false);
                board[i][j] = EMPTY;

                if (moveVal > bestVal) {
                    bestMove = i * 3 + j;
                    bestVal = moveVal;
                }
            }
        }
    }

    return bestMove;
}

int main() {
    vector<vector<char>> board = {
        { EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY }
    };

    cout << "Welcome to Tic-Tac-Toe! You are X, AI is O." << endl;

    while (true) {
        printBoard(board);
        
        int humanMove;
        cout << "Enter your move (1-9): ";
        cin >> humanMove;

        if (humanMove < 1 || humanMove > 9) {
            cout << "Invalid move. Try again." << endl;
            continue;
        }

        int row = (humanMove - 1) / 3;
        int col = (humanMove - 1) % 3;

        if (board[row][col] != EMPTY) {
            cout << "Invalid move. Try again." << endl;
            continue;
        }

        board[row][col] = HUMAN;

        if (evaluate(board) == -10) {
            printBoard(board);
            cout << "You win!" << endl;
            break;
        }

        if (!isMovesLeft(board)) {
            printBoard(board);
            cout << "It's a draw!" << endl;
            break;
        }

        int bestMove = findBestMove(board);
        board[bestMove / 3][bestMove % 3] = AI;

        if (evaluate(board) == 10) {
            printBoard(board);
            cout << "AI wins!" << endl;
            break;
        }

        if (!isMovesLeft(board)) {
            printBoard(board);
            cout << "It's a draw!" << endl;
            break;
        }
    }

    return 0;
}
