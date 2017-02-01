// 1203. Scientific Conference - http://acm.timus.ru/problem.aspx?space=1&num=1203

#include <bits/stdc++.h>

using namespace std;

// const int INF = (int) 1e9;

// const int MAXN = 34567;

// The number of interesting reports.
int N;

struct Interval
{
    int start, end;
    Interval(int start, int end) : start(start), end(end) {}

    bool operator <(const Interval& op) const {
        if (end != op.end)
            return end < op.end;
        return start < op.start;
    }

    bool overlaps(const Interval& op) const {
        return max(start, op.start) <= min(end, op.end);
    }
};

int main() {
    ios::sync_with_stdio(false);

    // freopen("input.txt", "r", stdin);

    cin >> N;

    vector<Interval> timetable;
    
    for (int report = 0; report < N; ++report) {
        int start, end;
        cin >> start >> end;
        timetable.emplace_back(start, end);
    }

    // Unweighted Interval Scheduling Problem.

    sort(timetable.begin(), timetable.end());
    
    // Select the interval, x, with the earliest finishing time.
    // Remove x, and all intervals intersecting x, from the set of candidate intervals.
    // Continue until the set of candidate intervals is empty.
    
    int answer = 1;
    Interval last_valid_interval = timetable[0];
    for (int interval_ind = 1; interval_ind < N; ++interval_ind) {
        bool is_overlapping = last_valid_interval.overlaps(timetable[interval_ind]);
        if (!is_overlapping) {
            ++answer;
            last_valid_interval = timetable[interval_ind];
        }
    }

    cout << answer;

    return 0;
}
