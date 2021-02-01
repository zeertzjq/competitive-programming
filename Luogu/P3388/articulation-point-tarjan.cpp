// vim: et sw=4 sts=4 fdm=marker
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

const int N = 100010, E = N << 1;
int n, m, e0[N], e1[E], to[E], dfn[N], low[N], disc = 0;
bool ap[N], vis[N];

void tarjan(int u, int fa) {
    low[u] = dfn[u] = ++disc, vis[u] = 1;
    int ccnt = 0;
    for (int e = e0[u]; e; e = e1[e]) {
        int v = to[e];
        if (v == fa) continue;
        if (!dfn[v]) {
            tarjan(v, u), low[u] = min(low[u], low[v]);
            if (fa && low[v] >= dfn[u])
                ap[u] = 1;
            else if (!fa)
                ++ccnt;
        } else if (vis[v])
            low[u] = min(low[u], dfn[v]);
    }
    vis[u] = 0;
    if (!fa && ccnt > 1) ap[u] = 1;
}

int main() {
    n = gi(), m = gi();
    for (int i = 1; i <= m; ++i) {
        int x = gi(), y = gi();
        e1[i << 1] = e0[x], e0[x] = i << 1, to[i << 1] = y,
                e1[i << 1 | 1] = e0[y], e0[y] = i << 1 | 1, to[i << 1 | 1] = x;
    }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i]) tarjan(i, 0);
    putln(accumulate(ap + 1, ap + 1 + n, 0));
    for (int i = 1; i <= n; ++i)
        if (ap[i]) putsp(i);
    putchar('\n');
    return 0;
}
