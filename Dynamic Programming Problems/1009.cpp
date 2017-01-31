// 1009. K-based Numbers - http://acm.timus.ru/problem.aspx?space=1&num=1009

#include <bits/stdc++.h>

using namespace std;

// const long long INF = (long long) 1e18;

int N, K;

int main() {
    ios::sync_with_stdio(false);

    // freopen("input.txt", "r", stdin);

    cin >> N >> K;
    
    // Let dp[i][j] be the total number of
    // of valid (doesn’t contain two successive zeros) K based numbers,
    // containing i digits where last digits is either 0 (j == 0) or non-zero (j == 1).
    vector<vector<long long>> dp(N + 1, vector<long long>(2));

    // Base cases.
    dp[0][0] = 0;
    dp[0][1] = 0;
    dp[1][0] = 0;
    dp[1][1] = K - 1;

    // Recurrence.
    for (int digits = 2; digits <= N; ++digits) {
        // Example: K = 2, digits = 3
        // dp[3][0] = |{110}| = |{11}|.
        dp[digits][0] = dp[digits - 1][1];

        // dp[3][1] = |{111, 101}| = (|{11}| + |{10}|) * (2 - 1).
        dp[digits][1] = (dp[digits - 1][1] + dp[digits - 1][0]) * (K - 1);
    }

    cout << dp[N][0] + dp[N][1];

    return 0;
}
