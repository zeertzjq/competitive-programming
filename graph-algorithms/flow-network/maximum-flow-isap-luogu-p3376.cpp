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

const int N = 10010, M = 200010, inf = ~0U >> 1;
int n, m, s, t, e0[N], e1[M], dst[M], w[M], dep[N], q[N], head, tail, cur[N],
    cnt[N], pre[N];

inline void bfs() {
    head = 1;
    tail = 0;
    fill(dep + 1, dep + 1 + n, -1);
    dep[t] = 0;
    q[++tail] = t;
    while (head <= tail) {
        int u = q[head++];
        ++cnt[dep[u]];
        for (int e = e0[u]; e; e = e1[e]) {
            int v = dst[e];
            if (~dep[v] || !w[e ^ 1]) continue;
            dep[v] = dep[u] + 1;
            q[++tail] = v;
        }
    }
}

inline int flow() {
    int f = inf;
    for (int u = t; u != s; u = dst[pre[u] ^ 1]) f = min(f, w[pre[u]]);
    for (int u = t; u != s; u = dst[pre[u] ^ 1]) {
        w[pre[u]] -= f;
        w[pre[u] ^ 1] += f;
    }
    return f;
}

inline void relabel(int u) {
    dep[u] = n;
    for (int e = e0[u]; e; e = e1[e]) {
        int v = dst[e];
        if (w[e]) dep[u] = min(dep[u], dep[v] + 1);
    }
}

int isap() {
    bfs();
    copy(e0 + 1, e0 + 1 + n, cur + 1);
    int ans = 0, u = s;
    while (dep[s] < n) {
        if (u == t) {
            ans += flow();
            u = s;
        }
        bool f = 0;
        for (int &e = cur[u]; e; e = e1[e]) {
            int v = dst[e];
            if (dep[u] == dep[v] + 1 && w[e]) {
                f = 1;
                u = v;
                pre[v] = e;
                break;
            }
        }
        if (!f) {
            if (!--cnt[dep[u]]) return ans;
            relabel(u);
            ++cnt[dep[u]];
            cur[u] = e0[u];
            if (u != s) u = dst[pre[u] ^ 1];
        }
    }
    return ans;
}

int main() {
    n = gi();
    m = gi();
    s = gi();
    t = gi();
    for (int i = 1; i <= m; ++i) {
        int u = gi(), v = gi();
        e1[i << 1] = e0[u];
        e0[u] = i << 1;
        dst[i << 1] = v;
        w[i << 1] = gi();
        e1[i << 1 | 1] = e0[v];
        e0[v] = i << 1 | 1;
        dst[i << 1 | 1] = u;
        w[i << 1 | 1] = 0;
    }
    putln(isap());
    return 0;
}
