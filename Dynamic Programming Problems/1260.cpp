// 1260. Nudnik Photographer - http://acm.timus.ru/problem.aspx?space=1&num=1260

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 56;

int main() {
    ios::sync_with_stdio(false);

    // freopen("input.txt", "r", stdin);

    int n;
    cin >> n;
    
    // Let dp[i] be the number of all the possible arranges of length i.
    vector<long long> dp(MAX_N, 0);

    // Base cases.
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 1;
    dp[3] = 2;

    // Recurrence.
    for (int length = 4; length <= n; ++length) {
        dp[length] += dp[length - 1] + dp[length - 3] + 1;
    }

    cout << dp[n];

    return 0;
}
