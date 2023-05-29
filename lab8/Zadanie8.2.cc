#include <iostream>
#include <vector>
#include <omp.h>

bool canPlaceQueen(const std::vector<int>& queens, int row, int col) {
    for (int i = 0; i < row; i++) {
        if (queens[i] == col || queens[i] - col == i - row || queens[i] - col == row - i) {
            return false;
        }
    }
    return true;
}

void solveNQueens(int N, int row, std::vector<int>& queens, int& solutionsCount) {
    if (row == N) {
        #pragma omp atomic
        solutionsCount++;
        return;
    }

    for (int col = 0; col < N; col++) {
        if (canPlaceQueen(queens, row, col)) {
            queens[row] = col;
            solveNQueens(N, row + 1, queens, solutionsCount);
        }
    }
}

int main() {
    int N = 8;  
    int solutionsCount = 0;  

    std::vector<int> queens(N, -1);  

    #pragma omp parallel for
    for (int col = 0; col < N; col++) {
        queens[0] = col;
        solveNQueens(N, 1, queens, solutionsCount);
    }

    std::cout << "Liczba rozmieszczeń N hetmanów: " << solutionsCount << std::endl;

    return 0;
}
