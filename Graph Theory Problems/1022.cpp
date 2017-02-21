// 1022. Genealogical Tree - http://acm.timus.ru/problem.aspx?space=1&num=1022

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 101;

int n;
vector<int> graph[MAX_N];
vector<bool> visited(MAX_N, false);
vector<int> ans;

void dfs(int vertex) {
    visited[vertex] = true;

    for (int neighbour : graph[vertex]) {
        if (!visited[neighbour]) {
            dfs(neighbour);
        }
    }

    ans.emplace_back(vertex);
}

void top_sort() {
    for (int vertex = 0; vertex < n; ++vertex) {
        if (!visited[vertex]) {
            dfs(vertex);
        }
    }

    reverse(ans.begin(), ans.end());
}


int main() {
    ios::sync_with_stdio(false);

    // freopen("input.txt", "r", stdin);
    
    cin >> n;

    int neighbour;
    for (int member = 0; member < n; ++member) {
        cin >> neighbour;
        while(neighbour != 0) {
            --neighbour;
            graph[member].emplace_back(neighbour);
            cin >> neighbour;
        }
    }

    top_sort();

    for (int vertex : ans) {
        cout << vertex + 1 << " ";
    }

    return 0;
}
