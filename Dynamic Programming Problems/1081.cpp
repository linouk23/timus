// 1081. Binary Lexicographic Sequence - http://acm.timus.ru/problem.aspx?space=1&num=1081

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 45;

int N, K;

// Let dp[i][j] be the total number of
// of valid (doesn’t contain two successive ones) numbers,
// containing i digits where last digit is j.
vector<vector<long long>> dp(MAXN, vector<long long>(2));

void rec(int N, int K) {
    if (N == 0) return;

    if (K < dp[N][0]){
        cout << 0;
        rec(N - 1, K);
    } else {
        cout << 1;
        rec(N - 1, K - dp[N][0]);
    }
}

int main() {
    ios::sync_with_stdio(false);

    // freopen("input.txt", "r", stdin);

    cin >> N >> K;

    // Base cases.
    dp[0][0] = 0;
    dp[0][1] = 0;
    dp[1][0] = 1;
    dp[1][1] = 1;

    // Recurrence.
    for (int digits = 2; digits <= N; ++digits) {
        dp[digits][1] = dp[digits - 1][0];

        dp[digits][0] = dp[digits - 1][0] + dp[digits - 1][1];
    }

    int number_of_valid_sequences = dp[N][0] + dp[N][1];
    if (number_of_valid_sequences < K) {
        cout << -1;
    } else {
        rec(N, K - 1);
    }

    return 0;
}
