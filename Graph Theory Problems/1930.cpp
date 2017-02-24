// 1930. Ivan's Car - http://acm.timus.ru/problem.aspx?space=1&num=1930

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 30001;
const int INF = 123456789;
int n, m;

struct Edge {
    int finish;
    int weight;

    Edge(int finish, int weight) : 
        finish(finish), weight(weight) {}
};

vector<vector<Edge>> graph(MAX_N);
vector<int> dist(MAX_N, INF);

int md(int vertex) {
    return 2 * vertex;
}

int mu(int vertex) {
    return 2 * vertex + 1;
}

int main() {
    ios::sync_with_stdio(false);

    // freopen("input.txt", "r", stdin);
    cin >> n >> m;
    int fake_start = 0;
    int start, finish;
    for (int edge = 0; edge < m; ++edge) {
        cin >> start >> finish;

        // Start vertex is lower than finish vertex.
        // Build a graph with 2 * N vertices: two vertices
        // for each city (encoding which gear-mode is 
        // currently selected: for moving up (2 * i + 1) or moving down: (2 * i)).

        // So for start->finish edge we'll add 4 edges:
        // 1) start (MD selected) -> (weight = 1) -> finish (MU selected)
        // 2) start (MU selected) -> (weight = 0) -> finish (MU selected)
        // 3) finish (MD selected) -> (weight = 0) -> start (MD selected)
        // 4) finish (MU selected) -> (weight = 1) -> start (MD selected)


        graph[md(start)].emplace_back(mu(finish), 1);
        graph[mu(start)].emplace_back(mu(finish), 0);
        graph[md(finish)].emplace_back(md(start), 0);
        graph[mu(finish)].emplace_back(md(start), 1);
    }

    cin >> start >> finish;

    graph[fake_start].emplace_back(mu(start), 0);
    graph[fake_start].emplace_back(md(start), 0);


    // O-1 BFS
    deque<int> q;
    dist[fake_start] = 0;
    q.push_front(fake_start);
    while(!q.empty()) {
        int vertex = q.front();
        q.pop_front();
        for (const auto & neighbour : graph[vertex]) {
            // If relaxes distance to neighbour.finish
            if (dist[vertex] + neighbour.weight < dist[neighbour.finish]) {
                dist[neighbour.finish] = dist[vertex] + neighbour.weight;

                if (neighbour.weight == 1) {
                    q.push_back(neighbour.finish);
                } else {
                    q.push_front(neighbour.finish);
                }
            }
        }
    }

    cout << min(dist[md(finish)], dist[mu(finish)]);

    return 0;
}
