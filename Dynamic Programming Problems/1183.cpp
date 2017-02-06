// 1183. Brackets Sequence - http://acm.timus.ru/problem.aspx?space=1&num=1183

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 101;
const long long INF = (long long)1e18;

// Interval DP:
// Let dp[i][j] be the minimum number of
// parentheses to make str[i:j] balanced.
vector<vector<long long>> dp(MAX_N, vector<long long> (MAX_N, 0));

vector<vector<string>> res(MAX_N, vector<string> (MAX_N, ""));

unordered_map<char, char> match = {
    {'(', ')'},
    {'[', ']'},
};

string round_brackets = "()";
string square_brackets = "[]";

string str;

int main() {
    ios::sync_with_stdio(false);

    // freopen("input.txt", "r", stdin);

    cin >> str;

    // Check the empty string.
    if (!str.length()) {
        cout << "";
        return 0;
    }

    int N = str.length();

    for (int index = 0; index < N; ++index) {
        // We can balance any expression of length 1 
        // using only 1 matching parenthesis:
        // Example: '(' -> '()', ']' -> '[]'.
        dp[index][index] = 1;

        if (round_brackets.find(str[index]) != string::npos) {
            res[index][index] = round_brackets;
        } else {
            res[index][index] = square_brackets;
        }
    }

    for (int start = 0; start < N; ++start) {
        for (int finish = start + 1; finish < N; ++finish) {
            dp[start][finish] = INF;
        }
    }

    // finish > start.
    for (int start = N - 1; start >= 0; --start) {
        for (int finish = start + 1; finish < N; ++finish) {

            // Just throw matching parentheses away and make
            // the remaining subsequence balanced.
            if (str[finish] == match[str[start]]) {

                // dp[start][finish] = min(dp[start][finish], dp[start + 1][finish - 1])
                // dp[start][finish] = 0 where start > finish => dp[0][1] for "()" = 0
                if (dp[start + 1][finish - 1] < dp[start][finish]) {
                    dp[start][finish] = dp[start + 1][finish - 1];
                    res[start][finish] = str[start] + res[start + 1][finish - 1] + str[finish];
                }
            }
            // Split the sequence into two non-zero sized parts
            // and make both balanced:
            // Examples:
            // ()() -> () + (), )() -> ) + (), ()( -> () + (
                
            // dp[start][finish] = min(dp[start][finish],
            //                         dp[start][finish_of_first_part] + 
            //                         dp[finish_of_first_part + 1][finish]);
            for (int finish_of_first_part = start; finish_of_first_part < finish; ++finish_of_first_part) {
                if (dp[start][finish_of_first_part] + dp[finish_of_first_part + 1][finish] <
                    dp[start][finish]) {
                    dp[start][finish] = dp[start][finish_of_first_part] +
                                        dp[finish_of_first_part + 1][finish];
                    res[start][finish] = res[start][finish_of_first_part] +
                                         res[finish_of_first_part + 1][finish];
                }
            }
        }
    }

    // cout << dp[0][N - 1];
    cout << res[0][N - 1];
    return 0;
}
