#include <bits/stdc++.h>
using namespace std;

//{{{
inline int gi() {
    int x, f = 0;
    char c;
    while (!isdigit(c = getchar()))
        if (c == '-') f = 1;
    for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0')
        ;
    return f ? -x : x;
}

inline long long gll() {
    int f = 0;
    long long x;
    char c;
    while (!isdigit(c = getchar()))
        if (c == '-') f = 1;
    for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0')
        ;
    return f ? -x : x;
}

template <typename T>
void puti(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) puti(x / 10);
    putchar(x % 10 + '0');
}

template <typename T>
inline void putsp(T x) {
    puti(x);
    putchar(' ');
}

template <typename T>
inline void putln(T x) {
    puti(x);
    putchar('\n');
}
//}}}

int n, k;
long long dp[10][82][1 << 9];

inline int bs(int s) {
    int ret = 0;
    do
        ret += s & 1;
    while (s >>= 1);
    return ret;
}

inline bool ck(int s) { return !(s & s << 1); }

int main() {
    n = gi();
    k = gi();
    for (int j = 0; j <= min((n + 1) >> 1, k); ++j)
        for (int s = 0; s < 1 << n; ++s)
            if (ck(s) && bs(s) == j) dp[1][j][s] = 1;
    for (int i = 2; i <= n; ++i)
        for (int j = 0; j <= k; ++j)
            for (int s = 0; s < 1 << n; ++s) {
                int d = bs(s);
                if (!ck(s) || d > j) continue;
                for (int ps = 0; ps < 1 << n; ++ps)
                    if (!(s & ps) && ck(s | ps))
                        dp[i][j][s] += dp[i - 1][j - d][ps];
            }
    putln(accumulate(dp[n][k], dp[n][k] + (1 << n),
                     0LL));  // IMPORTANT: use long long
    return 0;
}
