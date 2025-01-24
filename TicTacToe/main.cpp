#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

class TicTacToe {
private:
    std::vector<std::vector<char>> board;
    char currentPlayer;

public:
    TicTacToe() : board(3, std::vector<char>(3, ' ')), currentPlayer('X') {}

    void displayBoard(const std::vector<std::pair<int, int>>& winningCells = {}) const {
        std::cout << "\n";
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (std::find(winningCells.begin(), winningCells.end(), std::make_pair(i, j)) != winningCells.end())
                    std::cout << "[" << board[i][j] << "]";
                else
                    std::cout << " " << board[i][j];
                if (j < 2) std::cout << " |";
            }
            std::cout << "\n";
            if (i < 2) std::cout << "---*---*---\n";
        }
        std::cout << "\n";
    }

    bool isMoveValid(int row, int col) const {
        return row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ';
    }

    void makeMove(int row, int col) {
        board[row][col] = currentPlayer;
    }

    bool checkWin(std::vector<std::pair<int, int>>& winningCells) const {
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) {
                winningCells = {{i, 0}, {i, 1}, {i, 2}};
                return true;
            }
            if (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer) {
                winningCells = {{0, i}, {1, i}, {2, i}};
                return true;
            }
        }
        if (board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) {
            winningCells = {{0, 0}, {1, 1}, {2, 2}};
            return true;
        }
        if (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer) {
            winningCells = {{0, 2}, {1, 1}, {2, 0}};
            return true;
        }
        return false;
    }

    bool isDraw() const {
        for (const auto& row : board)
            for (char cell : row)
                if (cell == ' ') return false;
        return true;
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    char getCurrentPlayer() const {
        return currentPlayer;
    }

    void reset() {
        board = std::vector<std::vector<char>>(3, std::vector<char>(3, ' '));
        currentPlayer = 'X';
    }
};

int main() {
    bool playAgain = true;

    while (playAgain) {
        TicTacToe game;
        bool gameOver = false;

        std::cout << "Welcome to Tic Tac Toe!\n";
        game.displayBoard();

        while (!gameOver) {
            int row, col;
            std::cout << "Player " << game.getCurrentPlayer() << ", enter your move:\n";
            std::cout << "Enter row (1-3): ";
            if (!(std::cin >> row) || row < 1 || row > 3) {
                std::cout << "Invalid input. Please enter a number between 1 and 3.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            std::cout << "Enter column (1-3): ";
            if (!(std::cin >> col) || col < 1 || col > 3) {
                std::cout << "Invalid input. Please enter a number between 1 and 3.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            row--; col--;

            if (!game.isMoveValid(row, col)) {
                std::cout << "Invalid move. The cell is already taken or out of bounds. Try again.\n";
                continue;
            }

            game.makeMove(row, col);
            std::vector<std::pair<int, int>> winningCells;
            game.displayBoard();

            if (game.checkWin(winningCells)) {
                std::cout << "Player " << game.getCurrentPlayer() << " wins!\n";
                game.displayBoard(winningCells);
                gameOver = true;
            } else if (game.isDraw()) {
                std::cout << "It's a draw!\n";
                gameOver = true;
            } else {
                game.switchPlayer();
            }
        }

        char replayChoice;
        std::cout << "Do you want to play again? (y/n): ";
        std::cin >> replayChoice;
        playAgain = (std::tolower(replayChoice) == 'y');

        if (playAgain) game.reset();
    }

    std::cout << "Thanks for playing Tic Tac Toe! Goodbye!\n";
    return 0;
}
