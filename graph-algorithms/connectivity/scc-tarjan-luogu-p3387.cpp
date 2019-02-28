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

const int N = 10010, M = 100010;
int n, m, val[N], e0[N], e1[M], ee[N], dst[M], dfn[N], low[N], rep[N], stk[N],
    top = 0, disc = 0, f[N], ans = 0;
bool vis[N];

void tarjan(int u) {
    if (dfn[u]) return;
    dfn[u] = low[u] = ++disc;
    stk[++top] = u;
    vis[u] = 1;
    for (int e = e0[u]; e; e = e1[e]) {
        int v = dst[e];
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (vis[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u])
        while (int v = stk[top--]) {
            rep[v] = u;
            vis[v] = 0;
            if (v == u) break;
            val[u] += val[v];
            if (e0[v]) {
                if (ee[u]) {
                    e1[ee[u]] = e0[v];
                    ee[u] = ee[v];
                } else {
                    e0[u] = e0[v];
                    ee[u] = ee[v];
                }
            }
        }
}

int dfs(int u) {
    u = rep[u];
    if (f[u]) return f[u];
    for (int e = e0[u]; e; e = e1[e]) {
        int v = rep[dst[e]];
        if (v != u) f[u] = max(f[u], dfs(v));
    }
    return f[u] += val[u];
}

int main() {
    n = gi();
    m = gi();
    for (int i = 1; i <= n; ++i) val[i] = gi();
    for (int i = 1; i <= m; ++i) {
        int u = gi(), v = gi();
        e1[i] = e0[u];
        e0[u] = i;
        if (!ee[u]) ee[u] = i;
        dst[i] = v;
    }
    for (int i = 1; i <= n; ++i) tarjan(i);  // IMPORTANT: the graph has NO root
    for (int i = 1; i <= m; ++i) dst[i] = rep[dst[i]];
    for (int i = 1; i <= n; ++i) ans = max(ans, dfs(i));
    putln(ans);
    return 0;
}
