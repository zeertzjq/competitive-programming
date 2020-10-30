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

const int N = 5010, M = 100010, inf = ~0U >> 1;
int n, m, s, t, e0[N], e1[M], to[M], w[M], c[M], dis[N], pre[N], q[N], head,
    tail, flow = 0, cost = 0;
bool inq[N];

inline int &qo(int &x) { return x == N ? x = 0 : x == -1 ? x = N - 1 : x; }

inline bool spfa() {
    fill(dis + 1, dis + 1 + n, inf), dis[s] = 0, head = 1, tail = 0,
                                     q[++tail] = s, inq[s] = 1;
    while (head != tail + 1) {
        int u = q[head++];
        qo(head), inq[u] = 0;
        for (int e = e0[u]; e; e = e1[e]) {
            int v = to[e];
            if (!w[e]) continue;
            int ndis = dis[u] + c[e];
            if (ndis < dis[v]) {
                dis[v] = ndis, pre[v] = e;
                if (!inq[v]) {
                    if (ndis < dis[q[head]])
                        q[qo(--head)] = v;
                    else
                        q[qo(++tail)] = v;
                    inq[v] = 1;
                }
            }
        }
    }
    return dis[t] != inf;
}

inline void mcmf() {
    while (spfa()) {
        int f = inf;
        for (int u = t; u != s; u = to[pre[u] ^ 1]) f = min(f, w[pre[u]]);
        for (int u = t; u != s; u = to[pre[u] ^ 1])
            w[pre[u]] -= f, w[pre[u] ^ 1] += f;
        flow += f, cost += f * dis[t];
    }
}

int main() {
    n = gi(), m = gi(), s = gi(), t = gi();
    for (int i = 1; i <= m; ++i) {
        int u = gi(), v = gi();
        e1[i << 1] = e0[u], e0[u] = i << 1, to[i << 1] = v, w[i << 1] = gi(),
                e1[i << 1 | 1] = e0[v], e0[v] = i << 1 | 1, to[i << 1 | 1] = u,
                w[i << 1 | 1] = 0;
        int f = gi();
        c[i << 1] = f, c[i << 1 | 1] = -f;
    }
    mcmf(), putsp(flow), putln(cost);
    return 0;
}
