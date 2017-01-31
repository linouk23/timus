// 1119. Metro - http://acm.timus.ru/problem.aspx?space=1&num=1119

#include <bits/stdc++.h>

using namespace std;

// const int INF = (int) 1e9;

// // West-east and south-north sizes of the grid.
// const int N = 1234;
// const int M = 1234;

// A number of quarters that can be crossed diagonally.
const int K = 123;

// The length of the side.
const double SIDE = 100.0;

// The length of diagonal.
const double DIAGONAL = sqrt(2 * SIDE * SIDE);

// The coordinates of quarters that can be crossed diagonally.
vector<pair<int, int>> crossed_quarters;

bool has_same_x_coordinate(int op1, int op2) {
    return crossed_quarters[op1].first == crossed_quarters[op2].first;
}

int main() {
    ios::sync_with_stdio(false);

    // freopen("input.txt", "r", stdin);

    int n, m, k;
    cin >> n >> m >> k;
    
    for (int index = 0; index < k; ++index) {
        int row, column;
        cin >> row >> column;
        crossed_quarters.emplace_back(row, column);
    }

    sort(crossed_quarters.begin(), crossed_quarters.end());

    // Longest Increasing Subsequence (LIS).
    // Let dp[i] be the length of the LIS which is ending at element with index i.
    vector<int> dp(K);
    vector<int> parents(K);

    // Base cases.
    for (int last_elem = 0; last_elem < k; ++last_elem) {
        dp[last_elem] = 1;
        parents[last_elem] = last_elem;

        for (int second_last_elem = 0; second_last_elem < last_elem; ++second_last_elem) {
            if (crossed_quarters[second_last_elem].second >= crossed_quarters[last_elem].second)
                continue;
            if (has_same_x_coordinate(second_last_elem, last_elem))
                continue;
            if (dp[second_last_elem] + 1 > dp[last_elem]) {
                dp[last_elem] = dp[second_last_elem] + 1;
                parents[last_elem] = second_last_elem;
            }
        }
    }

    auto max_index = minmax_element(dp.begin(), dp.begin() + k).second - dp.begin();
    int number_of_used_diagonals = dp[max_index];
    cout << llround(1.0 * number_of_used_diagonals * DIAGONAL + 
                    1.0 * (n + m - 2 * number_of_used_diagonals) * SIDE);

    return 0;
}
