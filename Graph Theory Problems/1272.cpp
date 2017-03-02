// 1272. Non-Yekaterinburg Subway - http://acm.timus.ru/problem.aspx?space=1&num=1272

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 10001;
int n, k, m;
int num_of_connected_components = 0;

vector<int> g[MAX_N];
vector<bool> visited(MAX_N, false);
 
void dfs(int vertex) {
    visited[vertex] = true;
    for (const auto & neighbour : g[vertex]) {
        if (!visited[neighbour])
            dfs(neighbour);
    }
}

void find_comps() {
    for (int vertex = 0; vertex < n; ++vertex) {
        if (!visited[vertex]) {
            dfs(vertex);
            ++num_of_connected_components;
       }
    }
}
 
int main() {
    ios::sync_with_stdio(false);

    // freopen("input.txt", "r", stdin);
    cin >> n >> k >> m;
    int start, finish;
    for (int tunnel = 0; tunnel < k; ++tunnel) {
        cin >> start >> finish;
        --start;
        --finish;
        g[start].emplace_back(finish);
        g[finish].emplace_back(start);
    }

    find_comps();

    cout << num_of_connected_components - 1;
    
    return 0;
}
