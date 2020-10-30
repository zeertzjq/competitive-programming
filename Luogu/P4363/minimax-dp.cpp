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

const int inf = ~0U >> 1, U = ~inf;
int n, m, a[10][10], b[10][10], f[1 << 20];

int dfs(int s, int ff) {
    if (f[s] != U) return f[s];
    f[s] = ff ? -inf : inf;
    int x = n, y = 0;
    for (int i = 0; i < m + n - 1; ++i) {
        s >> i & 1 ? --x : ++y;
        if ((s >> i & 3) != 1) continue;
        int ts = s ^ 3 << i;
        if (ff)
            f[s] = max(f[s], dfs(ts, !ff) + a[x][y]);
        else
            f[s] = min(f[s], dfs(ts, !ff) - b[x][y]);
    }
    return f[s];
}

int main() {
    n = gi(), m = gi();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) a[i][j] = gi();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) b[i][j] = gi();
    fill(f, f + (1 << (n + m)), U),
        f[((1 << n) - 1) << m] = 0, putln(dfs((1 << n) - 1, 1));
    return 0;
}
