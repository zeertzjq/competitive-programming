#include <bits/stdc++.h>
using namespace std;

//{{{
inline int gi() {
    int x, f = 0;
    char c;
    while (!isdigit(c = getchar())) c == '-' && (f = 1);
    for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0')
        ;
    return f ? -x : x;
}

inline long long gll() {
    int f = 0;
    long long x;
    char c;
    while (!isdigit(c = getchar())) c == '-' && (f = 1);
    for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0')
        ;
    return f ? -x : x;
}

template <typename T>
void puti(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) puti(x / 10);
    putchar(x % 10 + '0');
}

template <typename T>
inline void putsp(T x) {
    puti(x), putchar(' ');
}

template <typename T>
inline void putln(T x) {
    puti(x), putchar('\n');
}
//}}}

const int N = 500010, inf = ~0U >> 1;
const long long infll = ~0ULL >> 1;
int n, d, k, x[N], s[N], ming = inf, maxg = 0, q[N], head, tail;
long long tot = 0, dp[N];

bool ck(int g) {
    fill(dp, dp + n + 1, -infll), head = 1, tail = 0, dp[0] = 0;
    int j = 0;
    for (int i = 1; i <= n; ++i) {
        while (j < i && x[i] - x[j] >= d - g) {
            if (dp[j] != -infll) {
                while (head <= tail && dp[q[tail]] <= dp[j]) --tail;
                q[++tail] = j;
            }
            ++j;
        }
        while (head <= tail && x[i] - x[q[head]] > d + g) ++head;
        if (head > tail) continue;
        dp[i] = dp[q[head]] + s[i];
        if (dp[i] >= k) return true;
    }
    return false;
}

int solve(int l, int r) {
    if (l == r) return l;
    int m = (l + r) >> 1;
    if (ck(m))
        return solve(l, m);
    else
        return solve(m + 1, r);
}

int main() {
    n = gi(), d = gi(), k = gi();
    for (int i = 1; i <= n; ++i) {
        x[i] = gi(), s[i] = gi(), ming = min(abs(x[i] - d), ming),
        maxg = max(abs(x[i] - d), maxg);
        if (s[i] > 0) tot += s[i];
    }
    if (tot < k)
        puts("-1");
    else
        putln(solve(ming, maxg));
    return 0;
}
