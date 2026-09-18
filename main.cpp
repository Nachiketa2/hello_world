#include <algorithm>
#include <array>
#include <iostream>
#include <limits>

using Board = std::array<char, 9>;

void show(const Board& b) {
    std::cout << "\n  " << b[0] << " | " << b[1] << " | " << b[2]
              << "\n ---+---+---\n  " << b[3] << " | " << b[4] << " | " << b[5]
              << "\n ---+---+---\n  " << b[6] << " | " << b[7] << " | " << b[8] << "\n\n";
}

bool won(const Board& b, char p) {
    constexpr int lines[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},
                                 {1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    for (const auto& line : lines)
        if (b[line[0]] == p && b[line[1]] == p && b[line[2]] == p) return true;
    return false;
}

bool full(const Board& b) {
    for (char cell : b) if (cell != 'X' && cell != 'O') return false;
    return true;
}

int minimax(Board& b, bool computerTurn) {
    if (won(b, 'O')) return 10;
    if (won(b, 'X')) return -10;
    if (full(b)) return 0;

    int best = computerTurn ? -100 : 100;
    for (int i = 0; i < 9; ++i) {
        if (b[i] == 'X' || b[i] == 'O') continue;
        b[i] = computerTurn ? 'O' : 'X';
        int score = minimax(b, !computerTurn);
        b[i] = static_cast<char>('1' + i);
        best = computerTurn ? std::max(best, score) : std::min(best, score);
    }
    return best;
}

int computerMove(Board& b) {
    int bestScore = -100;
    int move = 0;
    for (int i = 0; i < 9; ++i) {
        if (b[i] == 'X' || b[i] == 'O') continue;
        b[i] = 'O';
        int score = minimax(b, false);
        b[i] = static_cast<char>('1' + i);
        if (score > bestScore) { bestScore = score; move = i; }
    }
    return move;
}

int main() {
    std::cout << "\033[1;36m=== TIC-TAC-TOE ===\033[0m\n"
              << "You are X. The computer is O. Choose a square from 1 to 9.\n";

    char again = 'y';
    while (again == 'y' || again == 'Y') {
        Board board{'1','2','3','4','5','6','7','8','9'};
        show(board);

        while (!won(board, 'X') && !won(board, 'O') && !full(board)) {
            int choice;
            std::cout << "Your move: ";
            if (!(std::cin >> choice) || choice < 1 || choice > 9 ||
                board[choice - 1] == 'X' || board[choice - 1] == 'O') {
                std::cout << "Please choose an empty square from 1 to 9.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            board[choice - 1] = 'X';
            show(board);
            if (won(board, 'X') || full(board)) break;

            int move = computerMove(board);
            board[move] = 'O';
            std::cout << "Computer chose square " << move + 1 << ".\n";
            show(board);
        }

        if (won(board, 'X')) std::cout << "\033[1;32mYou win!\033[0m\n";
        else if (won(board, 'O')) std::cout << "\033[1;31mComputer wins!\033[0m\n";
        else std::cout << "\033[1;33mDraw!\033[0m\n";
        std::cout << "Play again? (y/n): ";
        std::cin >> again;
    }
    std::cout << "Thanks for playing!\n";
}
