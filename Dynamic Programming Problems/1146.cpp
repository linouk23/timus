// 1146. Maximum Sum - http://acm.timus.ru/problem.aspx?space=1&num=1146

#include <bits/stdc++.h>

using namespace std;

const long long INF = (long long) 1e18;

int N;

// Kadane's Algorithm for 1D array.
long long max_sum_subarray(vector<long long>& arr) {
    if (arr.empty())
        return 0;

    long long ans = -INF;
    vector<long long> dp((int)arr.size(), 0ll);

    dp[0] = arr[0];

    for (int index = 1; index < (int) arr.size(); ++index) {
        dp[index] = max(dp[index - 1], 0ll) + arr[index];
        ans = max(ans, dp[index]);
    }

    return max(ans, dp[0]);
}

int main() {
    ios::sync_with_stdio(false);

    // freopen("input.txt", "r", stdin);

    cin >> N;
    
    vector<vector<long long>> arr(N, vector<long long>(N));

    for (int row = 0; row < N; ++row) {
        for (int column = 0; column < N; ++column) {
            cin >> arr[row][column];
        }
    }

    // Kadane's Algorithm for 2D array.
    long long ans = -INF;

    // Use 2 pointers and 'merge' [L, R] columns into one column,
    // and then run Kadane's Algorithm for 1D array for that 'merged' column.
    for (int left_col = 0; left_col < N; ++left_col) {
        vector<long long> tmp_col(N, 0ll);
        for (int right_col = left_col; right_col < N; ++right_col) {
            for (int row = 0; row < N; ++row) {
                tmp_col[row] += arr[row][right_col];
            }

            ans = max(ans, max_sum_subarray(tmp_col));
        }
    }

    cout << ans;

    return 0;
}
