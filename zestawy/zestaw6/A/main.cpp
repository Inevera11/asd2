#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

const int N = 8;

std::vector<std::pair<int, int>> getLegalMoves(std::pair<int, int> position)
{
    std::vector<std::pair<int, int>> moves;

    int offsets[8][2] = {
        {2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};

    for (auto offset : offsets)
    {
        int x = position.first + offset[0];
        int y = position.second + offset[1];
        if (x >= 0 && x < N && y >= 0 && y < N)
            moves.emplace_back(x, y);
    }

    return moves;
}

// sort moves by the number of onward moves
void sort_moves(std::vector<std::pair<int, int>> &moves, std::vector<std::vector<int>> &board)
{
    std::sort(moves.begin(), moves.end(), [&](auto &a, auto &b)
              { return getLegalMoves(a).size() < getLegalMoves(b).size(); });
}

bool knightTour(std::vector<std::vector<int>> &board, int x, int y, int move)
{
    board[x][y] = move;

    if (move == N * N)
        return true;

    std::vector<std::pair<int, int>> moves = getLegalMoves({x, y});
    sort_moves(moves, board);

    for (auto [nx, ny] : moves)
    {
        if (board[nx][ny] == 0)
        {
            if (knightTour(board, nx, ny, move + 1))
                return true;
        }
    }

    board[x][y] = 0; // backtracking
    return false;
}

void print_board(const std::vector<std::vector<int>> &board)
{
    for (const auto &row : board)
    {
        for (auto cell : row)
        {
            printf("%2d ", cell);
        }
        std::cout << '\n';
    }
}

int main()
{
    std::vector<std::vector<int>> board(N, std::vector<int>(N, 0));
    int start_x = 0, start_y = 0;

    if (knightTour(board, start_x, start_y, 1))
    {
        print_board(board);
    }
    else
    {
        std::cout << "Brak rozwiązania\n";
    }

    return 0;
}
