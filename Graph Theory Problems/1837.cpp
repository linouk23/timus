// 1837. Isenbaev's Number - http://acm.timus.ru/problem.aspx?space=1&num=1837

#include <bits/stdc++.h>

using namespace std;

unordered_map<string, unordered_set<string>> graph;
map<string, int> ans;

const int INF = 123456789;
const string captain = "Isenbaev";

int main() {
    ios::sync_with_stdio(false);

    // freopen("input.txt", "r", stdin);

    int num_of_teams;
    cin >> num_of_teams;

    string fst, snd, trd;

    for (int team = 0; team < num_of_teams; ++team) {
        cin >> fst >> snd >> trd;
        graph[fst].insert(snd);
        graph[fst].insert(trd);
        graph[snd].insert(fst);
        graph[snd].insert(trd);
        graph[trd].insert(fst);
        graph[trd].insert(snd);
        ans[fst] = INF;
        ans[snd] = INF;
        ans[trd] = INF;
    }

    if (graph.find(captain) != graph.end()) {
        unordered_set<string> used;
        used.insert(captain);
        queue<string> q;
        q.push(captain);
        ans[captain] = 0;

        while(!q.empty()) {
            string lastname = q.front();
            q.pop();
            for (const auto &neighbour : graph[lastname]) {
                if (used.find(neighbour) == used.end()) {
                    q.push(neighbour);
                    used.insert(neighbour);
                    ans[neighbour] = ans[lastname] + 1;
                }
            }
        }
    }
    
    for (const auto &it : ans) {
        if (it.second != INF) {
            cout << it.first << " " << it.second << endl;
        } else {
            cout << it.first << " " << "undefined" << endl;
        }
    }

    return 0;
}