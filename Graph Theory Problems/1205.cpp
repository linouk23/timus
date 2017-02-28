// 1205. By the Underground or by Foot? - http://acm.timus.ru/problem.aspx?space=1&num=1205

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 234;
const double INF = 1000*1000*1000;

struct Point {
    double x, y;

    Point() {}
    Point(double x, double y) : x(x), y(y) {}

    double dist(const Point& op) const {
        return sqrt(pow(x - op.x, 2) + pow(y - op.y, 2));
    }
};

vector<vector<pair<int, double>>> graph(MAX_N);
int n;
double foot_speed, undgrnd_speed;
vector<Point> stations;


int main() {
    ios::sync_with_stdio(false);

    // freopen("input.txt", "r", stdin);

    cin >> foot_speed >> undgrnd_speed;
    cin >> n;
    
    double x, y;
    for (int station = 0; station < n; ++station) {
        cin >> x >> y;
        stations.emplace_back(x, y);
    }

    // Add edges between undeground stations (travelling by undgrnd).
    int fst_station, snd_station;
    while (cin >> fst_station >> snd_station) {
        if (fst_station == 0 && snd_station == 0) {
            break;
        }
        --fst_station; --snd_station;
        double distance = stations[fst_station].dist(stations[snd_station]);
        double travel_time = distance / undgrnd_speed;
        graph[fst_station].emplace_back(snd_station, travel_time);
        graph[snd_station].emplace_back(fst_station, travel_time);
    }

    int start_vertex = n;
    int finish_vertex = n + 1;
    Point start;
    cin >> start.x >> start.y;
    
    Point finish;
    cin >> finish.x >> finish.y;
    
    // Add edges between undeground stations and the start point (travelling on foot).
    for (int station = 0; station < n; ++station) {
        double distance = start.dist(stations[station]);
        double travel_time = distance / foot_speed;
        graph[start_vertex].emplace_back(station, travel_time);
    }

    // Add edges between undeground stations and the finish point (travelling on foot).
    for (int station = 0; station < n; ++station) {
        double distance = finish.dist(stations[station]);
        double travel_time = distance / foot_speed;
        graph[station].emplace_back(finish_vertex, travel_time);
    }

    // Add edges between undeground stations (travelling on foot).
    for (int fst_station = 0; fst_station < n; ++fst_station) {
        for (int snd_station = fst_station + 1; snd_station < n; ++snd_station) {
            double distance = stations[fst_station].dist(stations[snd_station]);
            double travel_time = distance / foot_speed;
            graph[fst_station].emplace_back(snd_station, travel_time);
            graph[snd_station].emplace_back(fst_station, travel_time);
        }
    }

    // Add edge between start and finish points (travelling on foot).
    double distance = start.dist(finish);
    double travel_time = distance / foot_speed;
    graph[start_vertex].emplace_back(finish_vertex, travel_time);


    // Start vertex = n,
    // finish vertex = n + 1.
    vector<double> dist(n + 2, INF);
    vector<int> parents(n + 2);
    
    dist[start_vertex] = 0;
    parents[start_vertex] = start_vertex;

    set<pair<double, int>> q;
    q.insert({dist[start_vertex], start_vertex});

    while(!q.empty()) {
        // Get the min-dist vertex.
        int cur_vertex = q.begin()->second;
        q.erase(q.begin());

        // Relax its adjacent vertices.
        for (const pair<int, double> & edge : graph[cur_vertex]) {
            double len = edge.second;
            int adj_vertex = edge.first;

            if (dist[adj_vertex] > dist[cur_vertex] + len) {
                q.erase({dist[adj_vertex], adj_vertex});
                dist[adj_vertex] = dist[cur_vertex] + len;
                parents[adj_vertex] = cur_vertex;
                q.insert({dist[adj_vertex], adj_vertex});
            }
        }
    }

    vector<int> path;
    
    int vertex = finish_vertex;
    while(vertex != start_vertex) {
        path.emplace_back(vertex);
        vertex = parents[vertex];
    }
    path.emplace_back(start_vertex);

    cout.precision(15);
    cout << dist[finish_vertex] << endl;
    cout << path.size() - 2 << " ";
    reverse(path.begin(), path.end());
    for (int vertex = 1; vertex < path.size() - 1; ++vertex) {
        cout << path[vertex] + 1 << " ";
    }

    return 0;
}
