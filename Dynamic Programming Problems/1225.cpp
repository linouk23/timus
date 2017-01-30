// 1225. Flags - http://acm.timus.ru/problem.aspx?space=1&num=1225

#include <bits/stdc++.h>

#define MAX_LENGTH 50

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    // Let num_of_flags[i][j] be the total number of flags of length i where last color is j.
    vector<vector<long long>> num_of_flags(MAX_LENGTH, vector<long long>(3));

    int length;
    cin >> length;
    
    // Base cases.
    num_of_flags[0][1] = num_of_flags[0][2] = 0;
    // "1"; "2".
    num_of_flags[1][1] = num_of_flags[1][2] = 1;
    // "12"; "21".
    num_of_flags[2][1] = num_of_flags[2][2] = 1;

    // Recurrence.
    for (int cur_length = 3; cur_length <= length; ++cur_length) {
        // Example: num_of_flags[3][1] = |{"12" + "1", "2" + "31"}|.
        num_of_flags[cur_length][1] = num_of_flags[cur_length - 1][2] + num_of_flags[cur_length - 2][2];
        num_of_flags[cur_length][2] = num_of_flags[cur_length - 1][1] + num_of_flags[cur_length - 2][1];
    }

    cout << num_of_flags[length][1] + num_of_flags[length][2];
    
    return 0;
}
