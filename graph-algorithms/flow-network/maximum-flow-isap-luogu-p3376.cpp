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

const int N = 10010, M = 200010, INF = 2147483647;
int n, m, s, t, e0[N], e1[M], dst[M], w[M], dep[N], q[N], head, tail, cur[N], cnt[N], pre[N];

void bfs() {
    head = 1;
    tail = 0;
    dep[t] = 1;
    q[++tail] = t;
    while (head <= tail) {
        int u = q[head++];
        ++cnt[dep[u]];
        for (int e = e0[u]; e; e = e1[e]) {
            int v = dst[e];
            if (dep[v] || !w[e ^ 1]) continue;
            dep[v] = dep[u] + 1;
            q[++tail] = v;
        }
    }
}

inline int flow() {
    int ans = INF, u = t;
    while (u != s) {
        ans = min(ans, w[pre[u]]);
        u = dst[pre[u] ^ 1];
    }
    u = t;
    while (u != s) {
        w[pre[u]] -= ans;
        w[pre[u] ^ 1] += ans;
        u = dst[pre[u] ^ 1];
    }
    return ans;
}

int isap() {
    bfs();
    copy(e0 + 1, e0 + 1 + n, cur + 1);
    int ans = 0, u = s;
    while (dep[s] <= n) {
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
            int mins = n;
            for (int e = e0[u]; e; e = e1[e])
                if (w[e]) mins = min(mins, dep[dst[e]]);
            if (!--cnt[dep[u]]) return ans;
            ++cnt[dep[u] = mins + 1];
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
