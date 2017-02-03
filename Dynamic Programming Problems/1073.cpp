// 1073. Square Country - http://acm.timus.ru/problem.aspx?space=1&num=1073

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 61234;

const int INF = 1e9;

// Let dp[n] be the answer for n.
vector<int> dp(MAX_N, -1);

int rec(int n) {
    // Base cases.
    if (n <= 0) return INF;

    // rec(n) was already computed.
    if (dp[n] != -1) return dp[n];

    // Check if the number is a perfect square
    int root = round(sqrt(n));
    bool is_perfect_square = (n == root * root);

    // Recurrence.
    int ans = 0;
    if (is_perfect_square) {
        ans = 1;
    } else {
        int minimum = INF;
        for (int summand = 1; summand <= round(sqrt(n)); ++summand) {
            minimum = min(minimum, rec(n - summand * summand) + 1);
        }
        ans = minimum;
    }

    dp[n] = ans;
    return dp[n];
}

int main() {
    ios::sync_with_stdio(false);

    // freopen("input.txt", "r", stdin);

    int n;
    cin >> n;

    int ans = rec(n);

    cout << ans;

    return 0;
}
