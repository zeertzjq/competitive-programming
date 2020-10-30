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

const int N = 10010, M = 200010, inf = ~0U >> 1;
int n, m, s, t, e0[N], e1[M], to[M], w[M], dep[N], q[N], head, tail, cur[N];

inline bool bfs() {
    fill(dep + 1, dep + 1 + n, 0), dep[s] = 1, head = 1, tail = 0,
                                   q[++tail] = s;
    while (head <= tail) {
        int u = q[head++];
        for (int e = e0[u]; e; e = e1[e]) {
            int v = to[e];
            if (dep[v] || !w[e]) continue;
            dep[v] = dep[u] + 1;
            if (v == t) return 1;
            q[++tail] = v;
        }
    }
    return 0;
}

int dfs(int u, int lim) {
    if (u == t) return lim;
    int used = 0;
    for (int &e = cur[u]; e; e = e1[e]) {
        int v = to[e];
        if (!w[e] || dep[v] != dep[u] + 1) continue;
        if (int f = dfs(v, min(lim - used, w[e])))
            w[e] -= f, w[e ^ 1] += f, used += f;
    }
    if (!used) dep[u] = 0;
    return used;
}

inline int dinic() {
    int ans = 0;
    while (bfs()) {
        copy(e0 + 1, e0 + 1 + n, cur + 1);
        while (int f = dfs(s, inf)) ans += f;
    }
    return ans;
}

int main() {
    n = gi(), m = gi(), s = gi(), t = gi();
    for (int i = 1; i <= m; ++i) {
        int u = gi(), v = gi();
        e1[i << 1] = e0[u], e0[u] = i << 1, to[i << 1] = v, w[i << 1] = gi(),
                e1[i << 1 | 1] = e0[v], e0[v] = i << 1 | 1, to[i << 1 | 1] = u,
                w[i << 1 | 1] = 0;
    }
    putln(dinic());
    return 0;
}
