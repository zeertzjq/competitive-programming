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
void putsp(T x) {
    puti(x);
    putchar(' ');
}

template <typename T>
void putln(T x) {
    puti(x);
    putchar('\n');
}
//}}}

const int N = 10010, M = 50010;
int n, m, e0[N], e1[M], dst[M], dfn[N], low[N], disc = 0, stk[N], top = 0, cnt[N], scc = 0, id[N], deg[N], ans = 0;
bool vis[N];

void tarjan(int u) {
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
    if (dfn[u] == low[u]) {
        ++scc;
        while (int v = stk[top--]) {
            id[v] = scc;
            ++cnt[scc];
            vis[v] = 0;
            if (v == u) break;
        }
    }
}

int main() {
    n = gi();
    m = gi();
    for (int i = 1; i <= m; ++i) {
        int a = gi(), b = gi();
        e1[i] = e0[a];
        e0[a] = i;
        dst[i] = b;
    }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i]) tarjan(i);
    for (int u = 1; u <= n; ++u)
        for (int e = e0[u]; e; e = e1[e]) {
            int v = dst[e];
            if (id[v] != id[u]) ++deg[id[u]];
        }
    for (int i = 1; i <= scc; ++i)
        if (!deg[i]) {
            if (ans) {
                puts("0");
                return 0;
            } else
                ans = i;
        }
    putln(cnt[ans]);
    return 0;
}
