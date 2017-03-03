// 1280. Topological Sorting - http://acm.timus.ru/problem.aspx?space=1&num=1280

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100001;
int n, m;
vector<int> graph[MAX_N];
vector<int> color(MAX_N, 0);

bool dfs(int vertex) {
    color[vertex] = 1; // in
    for (const auto &neighbour : graph[vertex]) {
        if (color[neighbour] == 1) return true;
        else if (color[neighbour] == 0) {
            // return dfs(neighbour);
            // ERROR:
            // 1 -> 8 -> 2 -> 7
            // 1 -> 1 -> 1 -> 2
            // Fails to color vertex №8 into 2:
            // 111000210
            // And then 3 -> 8 where color[8] = 1 => cycle
            
            if (dfs(neighbour)) return true;
        }
    }
    
    color[vertex] = 2; // out
    
    return false;
}

bool isAcyclic() {
    for (int vertex = 0; vertex < n; ++vertex) {
        if (color[vertex] == 0 && dfs(vertex)) {
            return false;
        }
    }
    return true;
}

void print(bool result) {
    cout << (result ? "YES" : "NO");
}

bool existsEdge(int start, int finish) {
    for (const auto &neighbour : graph[start]) {
        if (neighbour == finish) {
            return true;
        }
    }
    return false;
}

bool check(vector<int> &ans) {
    for (int start = n - 1; start >= 0; --start) {
        for (int finish = start - 1; finish >= 0; --finish) {
            if (existsEdge(ans[start] - 1, ans[finish] - 1)) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    
    // freopen("input.txt", "r", stdin);
    
    cin >> n >> m;
    
    int start, finish;
    for (int edge = 0; edge < m; ++edge) {
        cin >> start >> finish;
        
        --start;
        --finish;
        
        graph[start].emplace_back(finish);
    }
    vector<int> ans(n);
    for (int vertex = 0; vertex < n; ++vertex) {
        cin >> ans[vertex];
    }
    
    if (isAcyclic()) {
        print(check(ans));
    } else {
        print(false);
    }
    
    return 0;
}
