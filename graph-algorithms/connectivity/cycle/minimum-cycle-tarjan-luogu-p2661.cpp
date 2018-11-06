#include <bits/stdc++.h>
using namespace std;

inline int geti() {
    int x, f = 0;
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

const int N = 200010, INF = 2147483647;
int n, t[N], disc = 0, dfn[N], low[N], stk[N], top = 0, ans = INF;
bool vis[N];

void tarjan(int u) {
    dfn[u] = low[u] = ++disc;
    stk[++top] = u;
    vis[u] = true;
    int v = t[u];
    if (!dfn[v]) {
        tarjan(v);
        low[u] = min(low[u], low[v]);
    } else if (vis[v])
        low[u] = min(low[u], dfn[v]);
    if (dfn[u] == low[u]) {
        int cnt = 0;
        while (int p = stk[top--]) {
            vis[p] = false;
            ++cnt;
            if (p == u) break;
        }
        if (cnt > 1) ans = min(cnt, ans);
    }
}

int main() {
    n = geti();
    for (int i = 1; i <= n; ++i) t[i] = geti();
    for (int i = 1; i <= n; ++i)
        if (!dfn[i]) tarjan(i);
    putln(ans);
    return 0;
}
