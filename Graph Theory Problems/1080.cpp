// 1080. Map Coloring - http://acm.timus.ru/problem.aspx?space=1&num=1080

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 123;

vector<int> graph[MAX_N];
int n;

int main() {
    ios::sync_with_stdio(false);

    // freopen("input.txt", "r", stdin);

    cin >> n;
    int finish_vertex = 1;

    for (int start_vertex = 0; start_vertex < n; ++start_vertex) {
        while(cin >> finish_vertex) {
            if (finish_vertex == 0) {
                break;
            }
            --finish_vertex;
            graph[start_vertex].emplace_back(finish_vertex);
            graph[finish_vertex].emplace_back(start_vertex);
        }
    }

    queue<int> q;
    vector<int> color(MAX_N);
    vector<bool> visited(MAX_N, false);
    int start = 0;
    visited[start] = 0; // 0 stands for red, 1 stands for blue.
    q.push(start);

    while(!q.empty()) {
        int vertex = q.front();
        q.pop();
        for (int neighbour : graph[vertex]) {
            if (!visited[neighbour]) {
                visited[neighbour] = true;
                q.push(neighbour);
                color[neighbour] = 1 - color[vertex];
            }
        }
    }

    for (int start_vertex = 0; start_vertex < n; ++start_vertex) {
        for (int finish_vertex : graph[start_vertex]) {
            if (color[start_vertex] == color[finish_vertex]) {
                cout << -1;
                return 0;
            }
        }
    }

    for (int vertex = 0; vertex < n; ++vertex) {
        cout << color[vertex];
    }

    return 0;
}
