// 1167. Bicolored Horses - http://acm.timus.ru/problem.aspx?space=1&num=1167

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 501;

const long long INF = 1e18;

// Let dp[i][j] be the minimum possible value
// for the total coefficient of unhappiness
// for the first i horses where the first j 
// stables are taken.
vector<vector<long long>> dp(MAX_N, vector<long long> (MAX_N, 0));

// Let black[i] be the number of black 
// horses among the first i ones.
vector<long long> black(MAX_N, 0);
vector<long long> white(MAX_N, 0);

long long coef_for_last_stable(long long horses, long long k) {
    return (black[horses] - black[horses - k]) *
           (white[horses] - white[horses - k]);
}

int main() {
    ios::sync_with_stdio(false);

    // freopen("input.txt", "r", stdin);

    long long N, K;
    cin >> N >> K;
    

    for (long long horses = 1; horses <= N; ++horses) {
        int number;
        cin >> number;
        // 1 means that the horse is black
        if (number) {
            black[horses] = black[horses - 1] + 1;
            white[horses] = white[horses - 1];
        } else {
            white[horses] = white[horses - 1] + 1;
            black[horses] = black[horses - 1];
        }
    }

    // Base cases.
    // K = 1.
    for (long long horses = 1; horses <= N; ++horses) {
        dp[horses][1] = black[horses] * white[horses];
    }

    // Recurrence.
    for (long long stables = 2; stables <= K; ++stables) {
        for (long long horses = 1; horses <= N; ++horses) {
            // Let k be the number of horses (from the end)
            // that we try to place in the last stable, where the
            // unhappiness for i - k horses (from the beginning)
            // that placed in all stables (but the last one) is known.
            long long cur_minimum = INF;
            long long new_coef;
            for (int k = 1; k <= min(horses, N); ++k) {
                new_coef = dp[horses - k][stables - 1] + coef_for_last_stable(horses, k);
                cur_minimum = min(cur_minimum, new_coef);
            }
            dp[horses][stables] = cur_minimum;
        }
    }

    // Place the N horses into the K stables,
    // so that the total coefficient of unhappiness is minimized.
    cout << dp[N][K];

    return 0;
}
