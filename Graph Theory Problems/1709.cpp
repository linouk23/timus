// 1709. Penguin-Avia - http://acm.timus.ru/problem.aspx?space=1&num=1709

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 101;

vector<vector<bool>> adj_matrix(MAX_N, vector<bool> (MAX_N, false));
vector<vector<bool>> mst(MAX_N, vector<bool> (MAX_N, false));
vector<vector<char>> res(MAX_N, vector<char> (MAX_N, '0'));
int n;
int cost_to_add, cost_to_delete;

vector<int> parent(MAX_N, 0);
vector<int> size(MAX_N, 1);

void make_set(int vertex) {
    parent[vertex] = vertex;
    size[vertex] = 1;
}

int find_set(int vertex) {
    if (parent[vertex] == vertex) {
        return vertex;
    }
    
    return parent[vertex] = find_set(parent[vertex]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    
    if (a != b) {
        if (size[b] > size[a]) {
            swap(a, b);
        }
        
        parent[b] = a;
        size[a] += size[b];
    }
}

struct Edge {
    int weight;
    int start_vertex;
    int finish_vertex;
    
    Edge(int weight, int start_vertex, int finish_vertex) :
    weight(weight), start_vertex(start_vertex),
    finish_vertex(finish_vertex) {}
    
    bool operator <(const Edge& op) const {
        return weight < op.weight;
    }
};

int main() {
    ios::sync_with_stdio(false);
    
    // freopen("input.txt", "r", stdin);
    
    cin >> n >> cost_to_delete >> cost_to_add;
    
    string edges_for_airport;
    getline(cin, edges_for_airport);
    
    for (int start_airport = 0; start_airport < n; ++start_airport) {
        getline(cin, edges_for_airport);
        for (int edge_index = 0; edge_index < edges_for_airport.length(); ++edge_index) {
            if (edges_for_airport[edge_index] == '1') {
                adj_matrix[start_airport][edge_index] = true;
            }
        }
    }
    
    vector<Edge> edges;
    for (int start = 0; start < n; ++start) {
        for (int finish = 0; finish < n; ++finish) {
            if (start == finish) {
                continue;
            }
            
            if (adj_matrix[start][finish]) {
                edges.emplace_back(0, start, finish);
            } else {
                edges.emplace_back(cost_to_add, start, finish);
            }
        }
    }
    
    sort(edges.begin(), edges.end());
    
    for (int airport = 0; airport < n; ++airport) {
        make_set(airport);
    }
    
    for (const auto &edge : edges) {
        int start = edge.start_vertex;
        int finish = edge.finish_vertex;
        
        int start_vertex_root = find_set(start);
        int finish_vertex_root = find_set(finish);
        
        if (start_vertex_root != finish_vertex_root) {
            union_sets(start_vertex_root, finish_vertex_root);
            mst[start][finish] = true;
            mst[finish][start] = true;
        }
    }
    
    long long cost = 0;
    for (int start = 0; start < n; ++start) {
        for (int finish = 0; finish < n; ++finish) {
            if (mst[start][finish]) {
                if (!adj_matrix[start][finish]) {
                    res[start][finish] = 'a';
                    cost += cost_to_add;
                }
            } else {
                if (adj_matrix[start][finish]) {
                    res[start][finish] = 'd';
                    cost += cost_to_delete;
                }
            }
        }
    }
    
    
    cout << cost / 2 << endl;
    for (int start = 0; start < n; ++start) {
        for (int finish = 0; finish < n; ++finish) {
            cout << res[start][finish];
        }
        cout << endl;
    }
    
    return 0;
}
