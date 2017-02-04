// 1586. Threeprime Numbers - http://acm.timus.ru/problem.aspx?space=1&num=1586

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 10001;
const int ONE_THOUSAND = 1001;
const int NUMBER_OF_DIGITS = 11;

const int mod = (int) 1000*1000*1000 + 9;

// Let dp[n][i][j] be the total number of
// n-digit numbers whose last digit is i, and second last is j,
// so that the answer for n = m:
// ans = \sum_{i = 1}^{9} \sum_{j = 1}^{9} dp[m][i][j].
vector<vector<vector<int>>> dp(MAX_N,
    vector<vector<int>> (NUMBER_OF_DIGITS,
                         vector<int> (NUMBER_OF_DIGITS)));

vector<bool> prime_numbers(MAX_N, true);

vector<bool> primes(MAX_N, false);

// Sieve of Eratosthenes.
void find_prime_numbers() {
    prime_numbers[0] = false;
    prime_numbers[1] = false;
    for (int number = 2; number * number <= ONE_THOUSAND; ++number) {
        if (prime_numbers[number]) {
            for (int m = number * number; m < ONE_THOUSAND; m += number) {
                prime_numbers[m] = false;
            }
        }
    }

    for (int i = 100; i < ONE_THOUSAND; ++i) {
        if (prime_numbers[i]) {
            primes[i] = true;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);

    // freopen("input.txt", "r", stdin);

    find_prime_numbers();

    int N;
    cin >> N;

    // Base cases.
    // N = 3.
    for (int number = 100; number < ONE_THOUSAND; ++number) {
        if (primes[number]) {
            dp[3][(number % 100) / 10][number % 10] += 1;
        }
    }

    // Recurrence.
    for (int n = 4; n <= N; ++n) {
        for (int trd_last_digit = 0; trd_last_digit < 10; ++trd_last_digit) {
            for (int snd_last_digit = 0; snd_last_digit < 10; ++snd_last_digit) {
                if (! dp[n - 1][trd_last_digit][snd_last_digit]) continue;
                for (int last_digit = 1; last_digit < 10; ++last_digit) {
                    int number = 100 * trd_last_digit + 10 * snd_last_digit + last_digit;
                    bool number_is_prime = primes[number];
                    if (! number_is_prime) continue;

                    dp[n][snd_last_digit][last_digit] += dp[n - 1][trd_last_digit][snd_last_digit];
                    dp[n][snd_last_digit][last_digit] %= mod;
                }
            }
        }
    }

    int answer = 0;
    for (int snd_last_digit = 0; snd_last_digit < 10; ++snd_last_digit) {
        for (int last_digit = 0; last_digit < 10; ++last_digit) {
            answer += dp[N][snd_last_digit][last_digit];
            answer %= mod;
        }
    }

    cout << answer;

    return 0;
}
