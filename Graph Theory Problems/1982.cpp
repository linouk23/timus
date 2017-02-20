// 1982. Electrification Plan - http://acm.timus.ru/problem.aspx?space=1&num=1982

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 102;

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

int num_of_cities;
vector<int> parent(MAX_N);
vector<int> size(MAX_N);

vector<Edge> edges;

void make_set(int v) {
    parent[v] = v;
    size[v] = 1;
}
 
int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}
 
void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (size[a] < size[b]) {
            swap(a, b);
        }
        parent[b] = a;
        size[a] += size[b];
    }
}

int main() {
    ios::sync_with_stdio(false);

    // freopen("input.txt", "r", stdin);
    
    cin >> num_of_cities;

    int fake_station = num_of_cities;
    ++num_of_cities;

    int num_of_power_stations;
    cin >> num_of_power_stations;

    int station;
    for (int index = 0; index < num_of_power_stations; ++index) {
        cin >> station;
        --station;
        edges.emplace_back(0, station, fake_station);
    }

    int weight;
    for (int start = 0; start < num_of_cities - 1; ++start) {
        for (int finish = 0; finish < num_of_cities - 1; ++finish) {
            cin >> weight;
            if (start == finish) {
                continue;
            }
            edges.emplace_back(weight, start, finish);
        }
    }
    
    sort(edges.begin(), edges.end());

    for (int city = 0; city < num_of_cities; ++city) {
        make_set(city);
    }

    long long cost = 0;

    for (Edge edge : edges) {
        int start_vertex_root = find_set(edge.start_vertex);
        int finish_vertex_root = find_set(edge.finish_vertex);
        if (start_vertex_root != finish_vertex_root) {
            cost += edge.weight;
            union_sets(start_vertex_root, finish_vertex_root);
        }
    }

    cout << cost;

    return 0;
}
