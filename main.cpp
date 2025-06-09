#include <iostream>
using namespace std;

// map size
const int N = 5;

//Drone cordinates for sunlight  
const int x_sun = 0;
const int y_sun = 3;
int battery = 0;


// Function to print the solution matrix
void printSolution(int sol[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << sol[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to check if a cell is a valid position
bool isSafe(int map[N][N], int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N && map[x][y] == 1);
}
//--------------------------------------------------------------------------------------------------------------

//Solving map
bool solvemap(int map[N][N], int x, int y, int sol[N][N]);

// Find the path for sunlight
bool charging_point(int map[N][N], int x, int y, int sol[N][N]) {
    // If the rat reaches the destination (charging point)
    if (x == x_sun && y == y_sun && map[x][y] == 2) {
        cout << "\nBattery charging point found!!\n\n";
        sol[x][y] = 1;
        battery = 1;
        printSolution(sol);
        solvemap(map, x, y, sol);
    }

    // Check if the current cell is valid
    if (isSafe(map, x, y)) {
        sol[x][y] = 1;

        // Move right
        if (charging_point(map, x + 1, y, sol))
            return true;

        // Move down
        if (charging_point(map, x, y + 1, sol))
            return true;

        // If no path is found, unmark the cell and backtrack
        sol[x][y] = 0;
        return false;
    }

    return false;
}



void sunlight(int map[N][N],int x,int y)
{
	int sol[N][N] = {0};
	
	cout<<"\nFinding path to charge rover: \n";
	charging_point(map, x, y, sol);
	
}
//--------------------------------------------------------------------------------------------------------------




// Recursive function to solve the Rat in a map problem
bool solvemap(int map[N][N], int x, int y, int sol[N][N]) {
    // If the rat reaches the destination
    if (x == N - 1 && y == N - 1) {
        sol[x][y] = 1;
        return true;
    }

    // Check if the current cell is valid
    if (isSafe(map, x, y)) {
        sol[x][y] = 1;

        // Battery becomes dead
        if (map[x][y] == 9 && battery == 0) {
            cout << "\n\nBattery is dead when x:" << x << " and y: " << y << "\n\n";
            return false;
        }
        
        //battery is charged 
        if(map[x][y] == 9 && battery == 1)
        {
        	map[x][y] = 1;
        	solvemap(map, x, y, sol);
		}

        // Move right
        if (solvemap(map, x + 1, y, sol))
            return true;

        // Move down
        if (solvemap(map, x, y + 1, sol))
            return true;

        // If no path is found, unmark the cell and backtrack
        sol[x][y] = 0;
        return false;
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

    if (solvemap(map, 0, 0, sol)) {
        cout << "Solution exists. The path is:" << endl;
        printSolution(sol);
    } else {
        cout << "No solution exists." << endl;
    }
	
    return 0;
}
