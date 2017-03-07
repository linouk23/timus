# 1036. Lucky Tickets - http://acm.timus.ru/problem.aspx?space=1&num=1036

from sys import stdin, stdout


def solve():
    MAXN = 51
    MAXS = 1234

    line = stdin.readline()
    input_list = list(map(int, line.split()))

    N = input_list[0]
    S = input_list[1]

    if (S % 2 == 1):
        stdout.write('0')
        return

    # Let dp[i][j] be the total number of
    # of tickets,
    # containing i digits where sum is j.
    dp = [[0 for x in range(MAXS)] for y in range(MAXN)]

    S = S // 2

    # Base cases.
    for sum_of_number in range(10):
        dp[1][sum_of_number] = 1

    # Recurrence.
    for length in range(2, N + 1):
        for sum_of_number in range(S + 1):
            for digit in range(10):
                if sum_of_number - digit < 0:
                    continue

                # Append every possible digit.
                dp[length][sum_of_number] += dp[length - 1][sum_of_number - digit]

    stdout.write(str(dp[N][S] * dp[N][S]))


if __name__ == '__main__':
    solve()
