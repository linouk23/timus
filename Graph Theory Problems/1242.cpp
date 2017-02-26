// 1242. Werewolf - http://acm.timus.ru/problem.aspx?space=1&num=1242

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1234;

vector<vector<int>> up_graph(MAX_N);
vector<vector<int>> down_graph(MAX_N);
vector<bool> suspect(MAX_N, true);
int n;

unordered_set<int> victims;
vector<bool> visited(MAX_N, false);

void dfs(int vertex, vector<vector<int>> &graph) {
    visited[vertex] = true;
    suspect[vertex] = false;

    for (const auto & neighbour : graph[vertex]) {
        if (!visited[neighbour]) {
            dfs(neighbour, graph);
        }
    }
}

void traverse(vector<vector<int>> &graph) {
    for (const auto & victim : victims) {
        if (!visited[victim]) {
            dfs(victim, graph);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);

    // freopen("input.txt", "r", stdin);
    cin >> n;
    
    string line;
    getline(cin, line);
    bool has_edge = true;

    
    int child, parent;

    while(getline(cin, line)) {
        if (line == "BLOOD") {
            has_edge = false;
            continue;
        }

        if (has_edge) {
            stringstream edge;
            edge.str(line);            
            edge >> child >> parent;
            --child; --parent;
            up_graph[child].emplace_back(parent);
            down_graph[parent].emplace_back(child);

        } else {
            victims.insert(stoi(line) - 1);
        }
    }

    // Mark parents, grandparents, etc.
    traverse(up_graph);

    fill(visited.begin(), visited.end(), false);

    // Mark children, grandchildren, etc.
    traverse(down_graph);

    vector<int> werewolfs;
    for (int vertex = 0; vertex < n; ++vertex) {
        if (suspect[vertex]) {
            werewolfs.emplace_back(vertex + 1);
        }
    }

    if (werewolfs.empty()) {
        cout << "0";
    } else {
        for (const auto & werewolf : werewolfs) {
            cout << werewolf << " ";
        }
    }

    return 0;
}
