#include <iostream>
#include <vector>
#include <queue>
#include <chrono>

using namespace std;

// Maze dimensions
const int mazeWidth = 20;
const int mazeHeight = 10;

// Maze data (0: open, 1: wall)
vector<vector<int>> maze = {
    {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0},
    {0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0},
    {1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

struct Point {
    int x, y;
};

// Directions for BFS
vector<Point> directions = {
    {0, 1},  // Down
    {1, 0},  // Right
    {0, -1}, // Up
    {-1, 0}  // Left
};

// Display the maze with the solution path
void displayMaze(const vector<vector<int>>& maze, const vector<vector<bool>>& path) {
    for (int y = 0; y < mazeHeight; y++) {
        for (int x = 0; x < mazeWidth; x++) {
            if (path[y][x]) {
                cout << "* ";  // Solution path
            } else if (maze[y][x] == 1) {
                cout << "# ";  // Wall
            } else {
                cout << ". ";  // Open path
            }
        }
        cout << endl;
    }
}

// BFS function to find the shortest path in the maze
bool bfs(const Point& start, const Point& end, vector<vector<int>>& maze, vector<vector<bool>>& path) {
    auto startTime = chrono::high_resolution_clock::now();

    queue<Point> queue;
    queue.push(start);

    vector<vector<bool>> visited(mazeHeight, vector<bool>(mazeWidth, false));
    vector<vector<Point>> parent(mazeHeight, vector<Point>(mazeWidth, {-1, -1}));
    visited[start.y][start.x] = true;

    while (!queue.empty()) {
        Point current = queue.front();
        queue.pop();

        if (current.x == end.x && current.y == end.y) {
            // Path found, reconstruct the solution path
            Point trace = end;
            while (trace.x != -1 && trace.y != -1) {
                path[trace.y][trace.x] = true;
                trace = parent[trace.y][trace.x];
            }

            auto endTime = chrono::high_resolution_clock::now();
            chrono::duration<double, milli> duration = endTime - startTime;
            cout << "Path found in " << duration.count() << " milliseconds." << endl;
            return true;
        }

        for (const Point& dir : directions) {
            int newX = current.x + dir.x;
            int newY = current.y + dir.y;

            if (newX >= 0 && newX < mazeWidth && newY >= 0 && newY < mazeHeight &&
                maze[newY][newX] == 0 && !visited[newY][newX]) {
                queue.push({newX, newY});
                visited[newY][newX] = true;
                parent[newY][newX] = current;
            }
        }
    }

    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = endTime - startTime;
    cout << "No solution found. Search took " << duration.count() << " milliseconds." << endl;
    return false;
}

int main() {
    Point start = {0, 0};
    Point end = {19, 9};
    vector<vector<bool>> path(mazeHeight, vector<bool>(mazeWidth, false));

    cout << "Maze Solver - BFS Pathfinding\n" << endl;
    if (bfs(start, end, maze, path)) {
        cout << "Solution path:\n";
        displayMaze(maze, path);
    } else {
        cout << "No solution exists for the maze." << endl;
    }

    return 0;
}
