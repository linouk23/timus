// 1635. Mnemonics and Palindromes - http://acm.timus.ru/problem.aspx?space=1&num=1635

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4001;
const int INF = (int)1e9;

// Let dp[i][j] be the the minimal number
// of palindromes to which the str[0:i] (such that str[j:i] is
// the last palindrome) can be broken into.
vector<int> dp(MAX_N, INF);

// Keep the indexes of start letters for
// the optimal decompositions dp[i].
vector<int> start(MAX_N);

string str;
int N;

// Whether str[i:j] is a palindrome:
// -1 - doesn't make sense,
// 0 - no,
// 1 - yes.
vector<vector<int>> is_palindrome(MAX_N, vector<int> (MAX_N, -1));

int rec(int left, int right) {
    if (left > right || left >= N || right < 0) {
        return 1;
    }

    if (is_palindrome[left][right] != -1) {
        return is_palindrome[left][right];
    }


    int result = 0;
    if (str[left] == str[right] && rec(left + 1, right - 1) == 1) {
        result = 1;
    }

    is_palindrome[left][right] = result;
    return result;
}

int main() {
    ios::sync_with_stdio(false);

    // freopen("input.txt", "r", stdin);

    cin >> str;

    N = str.length();

    // Check the empty string.
    if (!str.length()) {
        cout << 0;
        return 0;
    }

    for (int start = 0; start < N; ++start) {
        for (int finish = 0; finish < N; ++finish) {
            if (start > finish) {
                is_palindrome[start][finish] = 0;
            } else if (is_palindrome[start][finish] == -1) {
                rec(start, finish);
            }
        }
    }

    for (int finish = 0; finish < N; ++finish) {
        for (int length = 1; length < finish + 2; ++length) {
            // The whole substring (from the beginning) is a palindrome.
            if (is_palindrome[0][finish]) {
                dp[finish] = 1;
                start[finish] = 0;
            // Continue & improve non-empty sequence of palindromes.
            } else if (is_palindrome[finish - length + 1][finish]) {
                // dp[finish] = min(dp[finish], dp[finish - length] + 1);
                if (dp[finish - length] + 1 < dp[finish]) {
                    dp[finish] = dp[finish - length] + 1;
                    start[finish] = finish - length + 1;
                }
            }   
        }
    }

    vector<string> palindromes;
    int last_letter_ind = N - 1;
    while(last_letter_ind >= 0) {
        int start_letter_ind = start[last_letter_ind];
        int length = last_letter_ind - start_letter_ind + 1;
        palindromes.push_back(str.substr(start_letter_ind, length));
        last_letter_ind = last_letter_ind - length;
    }

    reverse(palindromes.begin(), palindromes.end());

    cout << palindromes.size() << endl;
    for (const string &palindrome : palindromes) {
        cout << palindrome << " ";
    }

    return 0;
}
