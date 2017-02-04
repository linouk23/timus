# 1012. K-based Numbers. Version 2 - http://acm.timus.ru/problem.aspx?space=1&num=1012

from sys import stdin, stdout

K = 11
N = 2000

n = int(stdin.readline())
k = int(stdin.readline())

# Let dp[i][j] be the total number of
# of valid (doesn’t contain two successive zeros) K based numbers,
# containing i digits where last digits is either 0 (j == 0)
# or non-zero (j == 1).
dp = [[0 for x in range(K)] for y in range(N)]

# Base cases.
dp[1][0] = 1
dp[1][1] = k - 1

dp[2][0] = dp[1][1]
dp[2][1] = dp[1][1] * (k - 1)

# Recurrence.
for length in range(3, n + 1):
    # Example: k = 2, length = 3
    # dp[3][0] = |{110}| = |{11}|.
    dp[length][0] = dp[length - 1][1]

    # dp[3][1] = |{111, 101}| = (|{11}| + |{10}|) * (2 - 1).
    dp[length][1] = (dp[length - 1][0] + dp[length - 1][1]) * (k - 1)

stdout.write(str(dp[n][0] + dp[n][1]))
