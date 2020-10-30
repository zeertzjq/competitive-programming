// vim: sw=4 ts=4 sts=4 et fdm=marker
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

const int N = 6010;
int n, r[N], c0[N], c1[N], p[N], dp[N][2], rt = 1;

void dfs(int u) {
    dp[u][1] = r[u];
    for (int v = c0[u]; v; v = c1[v])
        dfs(v), dp[u][0] += max(dp[v][0], dp[v][1]), dp[u][1] += dp[v][0];
}

int main() {
    n = gi();
    for (int i = 1; i <= n; ++i) r[i] = gi();
    for (int i = 1; i < n; ++i) {
        int l = gi(), k = gi();
        c1[l] = c0[k], c0[k] = l, p[l] = k;
    }
    gi(), gi();
    while (p[rt]) rt = p[rt];
    dfs(rt), putln(max(dp[rt][0], dp[rt][1]));
    return 0;
}
