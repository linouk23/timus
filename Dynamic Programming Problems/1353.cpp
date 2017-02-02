// 1353. Milliard Vasya's Function - http://acm.timus.ru/problem.aspx?space=1&num=1353

#include <bits/stdc++.h>

using namespace std;

int MAX_N = 9;
int MAX_SUM = 81;
int required_sum;

int main() {
    ios::sync_with_stdio(false);

    // freopen("input.txt", "r", stdin);

    cin >> required_sum;

    // Let dp[n][s] be the amout of numbers of length n and whose sum of digits is s
    vector<vector<long long>> dp(MAX_N + 1, vector<long long>(MAX_SUM + 1, 0));

    // Base cases.
    for (int digit = 1; digit <= 9; ++digit) {
        dp[1][digit] = 1;
    }

    // Recurrence.
    for (int n = 2; n <= MAX_N; ++n) {
        for (int sum = 1; sum <= MAX_SUM; ++sum) {
            for (int digit = 0; digit <= min(9, sum); ++digit) {
                dp[n][sum] += dp[n - 1][sum - digit];
            }
        }
    }

    // Add 10^9 (10 digits) to the answer
    // cause our DP works for numbers of 9 digits at max.
    long long answer = (required_sum == 1) ? 1 : 0;

    // Sum up the numbers of 1-9 digits to get the answer
    for (int num_of_digits = 1; num_of_digits <= 9; ++num_of_digits) {
        answer += dp[num_of_digits][required_sum];
    }

    cout << answer;

    return 0;
}
