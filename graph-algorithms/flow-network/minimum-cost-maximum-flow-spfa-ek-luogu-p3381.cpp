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
int n, m, s, t, e0[N], e1[M], dst[M], w[M], c[M], dist[N], pre[N], q[N], head,
    tail, flow = 0, cost = 0;
bool inq[N];

inline int &qo(int &x) { return x == N ? x = 0 : x == -1 ? x = N - 1 : x; }

bool spfa() {
    head = 1;
    tail = 0;
    fill(dist + 1, dist + 1 + n, inf);
    dist[s] = 0;
    q[++tail] = s;
    inq[s] = 1;
    while (head != tail + 1) {
        int u = q[head++];
        qo(head);
        inq[u] = 0;
        for (int e = e0[u]; e; e = e1[e]) {
            int v = dst[e];
            if (!w[e]) continue;
            int ndist = dist[u] + c[e];
            if (ndist < dist[v]) {
                dist[v] = ndist;
                pre[v] = e;
                if (!inq[v]) {
                    if (ndist < dist[q[head]])
                        q[qo(--head)] = v;
                    else
                        q[qo(++tail)] = v;
                    inq[v] = 1;
                }
            }
        }
    }
    return dist[t] != inf;
}

inline void mcmf() {
    while (spfa()) {
        int f = inf;
        for (int u = t; u != s; u = dst[pre[u] ^ 1]) f = min(f, w[pre[u]]);
        for (int u = t; u != s; u = dst[pre[u] ^ 1]) {
            w[pre[u]] -= f;
            w[pre[u] ^ 1] += f;
        }
        flow += f;
        cost += f * dist[t];
    }
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
        int f = gi();
        c[i << 1] = f;
        c[i << 1 | 1] = -f;
    }
    mcmf();
    putsp(flow);
    putln(cost);
    return 0;
}
