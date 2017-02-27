// 1033. Labyrinth - http://acm.timus.ru/problem.aspx?space=1&num=1033

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 34;

vector<string> field(MAX_N);
set<pair<int, int>> visited;
set<pair<int, int>> empty;
int n;

int num_of_walls;

void bfs(int row, int column) {
    if (row < 0 || row >= n ||
        column < 0 || column >= n ||
        field[row][column] == '#') {
        if (empty.find({row, column}) == empty.end()) {
            ++num_of_walls;
        }
        return;
    }

    if (visited.find({row, column}) != visited.end()) {
        return;
    }

    visited.insert({row, column});

    // Go right.
    bfs(row + 1, column);

    // Go left.
    bfs(row - 1, column);

    // Go up.
    bfs(row, column + 1);

    // Go down.
    bfs(row, column - 1);
}

int main() {
    ios::sync_with_stdio(false);

    // freopen("input.txt", "r", stdin);
    cin >> n;
    
    for (int line_index = 0; line_index < n; ++line_index) {
        cin >> field[line_index];
    }

    empty.insert({0, -1});
    empty.insert({-1, 0});
    empty.insert({n, n - 1});
    empty.insert({n - 1, n});
    

    bfs(0, 0);
    bfs(n - 1, n - 1);

    cout << 9 * num_of_walls;

    return 0;
}
