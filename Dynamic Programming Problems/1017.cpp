// 1017. Staircases - http://acm.timus.ru/problem.aspx?space=1&num=1017

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 501;

// const int INF = 1e9;

// Let dp[i][j] be the number of staircases with
// i cubes and the height of last block is j,
// so that the answer = \sum_{j = 1}^{n} dp[n][j].
vector<vector<long long>> dp(MAX_N, vector<long long> (MAX_N));

int main() {
    ios::sync_with_stdio(false);

    // freopen("input.txt", "r", stdin);

    int n;
    cin >> n;

    // Base cases.
    dp[0][0] = 1;

    // Recurrence.
    for (int cubes = 1; cubes <= n; ++cubes) {
        for (int last_block = 1; last_block <= min(cubes, n); ++last_block) {
            long long sum = 0;
            for (int second_last_block = 0; second_last_block < last_block; ++second_last_block) {
                sum += dp[cubes - last_block][second_last_block];
            }
            dp[cubes][last_block] = sum;
        }
    }

    long long ans = 0;
    for (int last_block = 1; last_block < n; ++last_block) {
        ans += dp[n][last_block];
    }

    cout << ans;

    return 0;
}
