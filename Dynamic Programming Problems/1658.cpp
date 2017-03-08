// 1658. Sum of Digits - http://acm.timus.ru/problem.aspx?space=1&num=1658

#include <bits/stdc++.h>

using namespace std;

const int MAX_SUM = 999;
const int MAX_SQ_SUM = 8199;

// Let dp[i][j] be the minimum number of
// digits whose sum is i and 'squared' sum is j.
vector<vector<int>> dp(MAX_SUM, vector<int>(MAX_SQ_SUM, 0));
vector<vector<int>> parent(MAX_SUM, vector<int>(MAX_SQ_SUM, 0));

int rec(int sum, int sq_sum) {
    if (sum < 0 || sq_sum < 0) return 1e6;
    if (sum == 0 && sq_sum == 0) return 0;
    if (dp[sum][sq_sum]) return dp[sum][sq_sum];

    int ans = 1e6;
    for (int digit = 1; digit <= 9; ++digit) {
        int possible_ans = rec(sum - digit, sq_sum - digit * digit) + 1;

        if (possible_ans < ans) {
            ans = possible_ans;
            parent[sum][sq_sum] = digit;
        }
    }

    dp[sum][sq_sum] = ans;
    return dp[sum][sq_sum];
}

int main() {
    ios::sync_with_stdio(false);

    // freopen("input.txt", "r", stdin);

    // Number of test cases.
    int T;
    cin >> T;
    int sum_of_digits, sum_of_squared_digits;

    for (int test_case = 0; test_case < T; ++test_case) {
        cin >> sum_of_digits >> sum_of_squared_digits;

        if (sum_of_digits > 900 || sum_of_squared_digits > 8100 ||
            sum_of_digits > sum_of_squared_digits) {
            cout << "No solution" << endl;
            continue;
        }

        int num_of_digits = rec(sum_of_digits, sum_of_squared_digits);
        
        if (num_of_digits > 100) {
            cout << "No solution" << endl;
            continue;
        }

        string ans;
        while(parent[sum_of_digits][sum_of_squared_digits]) {
            int last_digit = parent[sum_of_digits][sum_of_squared_digits];
            ans += to_string(last_digit);
            sum_of_digits -= last_digit;
            sum_of_squared_digits -= last_digit * last_digit;
        }

        sort(ans.begin(), ans.end());
        cout << ans << endl;
    }
    return 0;
}
