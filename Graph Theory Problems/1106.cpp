// 1106. Two Teams - http://acm.timus.ru/problem.aspx?space=1&num=1106

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 101;

vector<int> graph[MAX_N];

int main() {
    ios::sync_with_stdio(false);

    // freopen("input.txt", "r", stdin);

    int num_of_friends;
    cin >> num_of_friends;

    for (int member = 0; member < num_of_friends; ++member) {
        int frnd;
        cin >> frnd;
        while(frnd != 0) {
            graph[frnd - 1].emplace_back(member);
            graph[member].emplace_back(frnd - 1);
            cin >> frnd;
        }
    }

    vector<bool> used(num_of_friends, false);
    vector<int> color(num_of_friends, -1);

    for (int frnd = 0; frnd < num_of_friends; ++frnd) {
        if (used[frnd]) {
            continue;
        }
        queue<int> q;
        used[frnd] = true;
        q.push(frnd);
        color[frnd] = 1;
        while(!q.empty()) {
            int vertex = q.front();
            q.pop();
            for (auto neighbour : graph[vertex]) {
                if (used[neighbour]) {
                    continue;
                }
                q.push(neighbour);
                used[neighbour] = true;
                color[neighbour] = 1 - color[vertex];
            }
        }
    }

    int size_of_fst_group = 0;
    vector<int> group;
    for (int frnd = 0; frnd < num_of_friends; ++frnd) {
        if (color[frnd] == 0) {
            ++size_of_fst_group;
            group.emplace_back(frnd + 1);
        }
    }
    
    cout << size_of_fst_group << endl;
    for (auto member : group) {
        cout << member << " ";
    }
    return 0;
}
