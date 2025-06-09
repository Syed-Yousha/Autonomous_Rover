#include <iostream>
using namespace std;

const int N = 5;
const int x_sun = 0;
const int y_sun = 3;
int battery = 0;

void printSolution(int sol[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << sol[i][j] << " ";
        }
        cout << endl;
    }
}

bool isSafe(int map[N][N], int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N && map[x][y] == 1);
}

bool solvemap(int map[N][N], int x, int y, int sol[N][N]) {
    if (x == N - 1 && y == N - 1) {
        sol[x][y] = 1;
        return true;
    }

    if (isSafe(map, x, y)) {
        sol[x][y] = 1;

        if (map[x][y] == 9 && battery == 0) {
            cout << "\n\nBattery is dead when x:" << x << " and y: " << y << "\n\n";
            return false;
        }

        if (map[x][y] == 9) {
            battery--;
        }

        if (map[x][y] == 2) {
            battery++;
        }

        if (battery < 0) {
            cout << "\n\nBattery is dead when x:" << x << " and y: " << y << "\n\n";
            return false;
        }

        if (solvemap(map, x + 1, y, sol))
            return true;

        if (solvemap(map, x, y + 1, sol))
            return true;

        sol[x][y] = 0;
        return false;
    }

    return false;
}

bool charging_point(int map[N][N], int x, int y) {
    if (x == x_sun && y == y_sun && map[x][y] == 2) {
        cout << "\nBattery charging point found!!\n\n";
        battery = 1;
        return true;
    }

    if (isSafe(map, x, y)) {
        if (charging_point(map, x + 1, y))
            return true;

        if (charging_point(map, x, y + 1))
            return true;
    }

    return false;
}

int main() {
    int map[N][N] = {
        {1, 0, 0, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {2, 1, 0, 9, 0},
        {0, 0, 0, 1, 1}
    };

    int sol[N][N] = {0};

    if (charging_point(map, 0, 0)) {
        battery = 0;
        
        if (solvemap(map, 0, 0, sol)) {
            cout << "Solution exists. The path is:" << endl;
            printSolution(sol);
        } else {
            cout << "No solution exists." << endl;
        }
    } else {
        cout << "No charging point found. Drone cannot operate." << endl;
    }

    return 0;
}
