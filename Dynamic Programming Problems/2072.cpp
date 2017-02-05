// 2072. Kirill the Gardener 3 - http://acm.timus.ru/problem.aspx?space=1&num=2072

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1234567;
long long INF = (long long)1e18;

// Let dp[pos] be the minimum time for the gardener
// that can be achieved after getting into this position
// to water the other flowers that has greater dryness.
vector<long long> dp(MAX_N, INF);

long long N;
vector<long long> flowerbed(MAX_N);
unordered_map<long long, long long> left_pos;
unordered_map<long long, long long> right_pos;

set<long long> set_of_dryness;

long long get_greater_number(long long num) {
    auto iterator = set_of_dryness.lower_bound(num + 1);
    return (iterator != set_of_dryness.end()) ? *iterator : -1;
}

// Returns the minimum time for the gardener
// to water all the flowerbeds that has the dryness > cur_dryness
// starting from the position = 'start_pos', where 'start_pos' is 
// the finish position of completed watering of the flowerbeds 
// of dryness = 'cur_dryness'.
long long rec(long long start_pos, long long cur_dryness) {
    long long next_dryness = get_greater_number(cur_dryness);

    // The young gardener completed his job.
    if (next_dryness == -1) return 0;

    // Check whether minimum time has been computed previously.
    // Without this memoizing, this solutions gets TL on test #10.
    if (dp[start_pos] != INF) {
        return dp[start_pos];
    }

    long long ans = INF;
    long long r_pos = right_pos[next_dryness];
    long long l_pos = left_pos[next_dryness];
    
    // There're 3 major cases:
    // 1. right_pos[next_dryness] < start_pos,
    // 2. left_pos[next_dryness] > start_pos,
    // 3. left_pos[next_dryness] < start_pos < right_pos[next_dryness].

    if (r_pos < start_pos) {
        ans = start_pos - l_pos + rec(l_pos, next_dryness);
    } else if (l_pos > start_pos) {
        ans = r_pos - start_pos + rec(r_pos, next_dryness);
    } else {
        long long distance = r_pos - l_pos;
        ans = min({ans, 
                   start_pos - l_pos + distance + rec(r_pos, next_dryness),
                   r_pos - start_pos + distance + rec(l_pos, next_dryness)});
    }

    dp[start_pos] = ans;
    return dp[start_pos];
}

int main() {
    ios::sync_with_stdio(false);

    // freopen("input.txt", "r", stdin);

    cin >> N;
    for (long long index = 0; index < N; ++index) {
        cin >> flowerbed[index];
        long long dryness = flowerbed[index];

        // Save index of the first and last occurance of the number.
        if (left_pos.find(dryness) == left_pos.end()) {
            left_pos[dryness] = index + 1;
        }
        right_pos[dryness] = index + 1;

        set_of_dryness.insert(dryness);
    }

    long long lowest_dryness = *set_of_dryness.begin();
    long long r_pos = right_pos[lowest_dryness];
    long long l_pos = left_pos[lowest_dryness];
    long long distance = r_pos - l_pos;

    // Initially Kirill stands near the leftmost flower.
    long long ans = min(r_pos - 1 + distance + rec(l_pos, lowest_dryness),
                        r_pos - 1 + rec(r_pos, lowest_dryness));

    // Watering of one flower takes Kirill one minute.
    ans += N;
    cout << ans;

    return 0;
}
