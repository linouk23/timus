// 1208. Legendary Teams Contest - http://acm.timus.ru/problem.aspx?space=1&num=1208

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 18;

int num_of_teams;
vector<vector<string>> teams(MAX_N, vector<string> (3));

unordered_map<string, bool> is_playing;

// num_of_teams >= 1
int answer = 1;

// Answer is a maximal possible number of teams of veterans, 
// that could simultaneously participate at the contest.
void dfs(int number_of_processed_teams, int cur_answer) {

    if (number_of_processed_teams == num_of_teams) {
        answer = max(answer, cur_answer);
        return;
    }

    // This team doesn't participate at the contest.
    dfs(number_of_processed_teams + 1, cur_answer);


    // We want to take this team, but some veteran was already taken.
    if (is_playing[teams[number_of_processed_teams][0]]
        || is_playing[teams[number_of_processed_teams][1]]
        || is_playing[teams[number_of_processed_teams][2]]) {
            return;
    }

    // This team participates at the contest.
    is_playing[teams[number_of_processed_teams][0]] = 
    is_playing[teams[number_of_processed_teams][1]] = 
    is_playing[teams[number_of_processed_teams][2]] = true;

    dfs(number_of_processed_teams + 1, cur_answer + 1);

    // To restore initial values for the next recursive calls.
    is_playing[teams[number_of_processed_teams][0]] = 
    is_playing[teams[number_of_processed_teams][1]] = 
    is_playing[teams[number_of_processed_teams][2]] = false;
}

int main() {
    ios::sync_with_stdio(false);

    // freopen("input.txt", "r", stdin);
    cin >> num_of_teams;
    
    for (int team = 0; team < num_of_teams; ++team) {
        cin >> teams[team][0] >> teams[team][1] >> teams[team][2];
    }

    dfs(0, 0);

    cout << answer;

    return 0;
}
