// 1152. False Mirrors - http://acm.timus.ru/problem.aspx?space=1&num=1152

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 21;
long long INF = (long long)1e14;

// Let dp[X] be the minimum amount of damage that can be achieved for set X.
// |X| = n where n is the number of balconies.
// X[i] = 0 || 1 (0 when the ith balcony was destroyed, 1 otherwise).
// so that the answer is dp[Y] where Y = 11...1, |Y| = n (everything was destroyed).
vector<long long> dp(pow(2, MAX_N), INF);

long long N;
vector<long long> damage(MAX_N);

long long delete_bit(long long X, long long position_of_bit) {
    return X ^ (1 << position_of_bit);
}

long long rec(long long X, long long sum_of_damages) {
    // Check whether minimum amount of damage for set X
    // has been computed previously.
    if (dp[X] != INF) {
        return dp[X];
    }

    long long ans = INF;

    // Check every balcony in set X.
    for (long long balcony_ind = 1; balcony_ind <= N; ++balcony_ind) {
        long long sum_of_damages_left = sum_of_damages;
        long long position_of_balcony_bit = balcony_ind - 1;

        // If there's ith balcony in X. 
        if (X & (1 << position_of_balcony_bit)) {
            long long mask_after_hit = delete_bit(X, position_of_balcony_bit);

            sum_of_damages_left -= damage[position_of_balcony_bit];

            // Cause it destroys three adjacent balconies per one shoot.
            long long left_balcony_ind = (balcony_ind - 2 + N) % N + 1;
            long long right_balcony_ind = balcony_ind % N + 1;


            long long position_of_left_balcony_bit = left_balcony_ind - 1;
            long long position_of_right_balcony_bit = right_balcony_ind - 1;

            if (mask_after_hit & (1 << position_of_left_balcony_bit)) {
                mask_after_hit = delete_bit(mask_after_hit, position_of_left_balcony_bit);
                sum_of_damages_left -= damage[position_of_left_balcony_bit];
            }

            if (mask_after_hit & (1 << position_of_right_balcony_bit)) {
                mask_after_hit = delete_bit(mask_after_hit, position_of_right_balcony_bit);
                sum_of_damages_left -= damage[position_of_right_balcony_bit];
            }

            // Recurrence: try to guess the first right shoot from X position.
            ans = min(ans, rec(mask_after_hit, sum_of_damages_left) + sum_of_damages_left);
        }
    }
    dp[X] = ans;
    return dp[X];
}

int main() {
    ios::sync_with_stdio(false);

    // freopen("input.txt", "r", stdin);

    cin >> N;
    long long sum_of_damages = 0;
    for (int balcony = 0; balcony < N; ++balcony) {
        cin >> damage[balcony];
        sum_of_damages += damage[balcony];
    }

    // Base cases.
    // For empty set (everything was destroyed): 00...0
    dp[0] = 0;

    // Y = 11...1, |Y| = n (nothing was destroyed).
    // (1 << N) = pow(2, N).
    long long Y = pow(2, N) - 1;
    long long ans = rec(Y, sum_of_damages);

    cout << ans;
    
    return 0;
}
