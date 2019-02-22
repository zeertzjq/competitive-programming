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

const int N = 1210, M = 240010, inf = ~0U >> 1;
int n, m, s, t, e0[N], e1[M], dst[M], w[M], h[N], q[N], head, tail, fe[N], pq[N], pqsz = 0, cnt[N << 1];
bool inq[N], inpq[N];

inline bool bfs() {
    head = 1;
    tail = 0;
    fill(h + 1, h + 1 + n, inf);
    h[t] = 0;
    q[++tail] = t;
    inq[t] = 1;
    while (head <= tail) {
        int u = q[head++];
        for (int e = e0[u]; e; e = e1[e]) {
            int v = dst[e];
            if (w[e ^ 1] && h[u] + 1 < h[v]) {
                h[v] = h[u] + 1;
                if (!inq[v]) {
                    q[++tail] = v;
                    inq[v] = 1;
                }
            }
        }
    }
    return h[s] != inf;
}

inline void push(int u) {
    for (int e = e0[u]; e; e = e1[e]) {
        int v = dst[e];
        if (w[e] && h[u] == h[v] + 1) {
            int f = min(fe[u], w[e]);
            w[e] -= f;
            w[e ^ 1] += f;
            fe[u] -= f;
            fe[v] += f;
            if (!inpq[v]) {
                pq[pqsz++] = v;
                push_heap(pq, pq + pqsz);
                inpq[v] = 1;
            }
            if (!fe[u]) break;
        }
    }
}

inline void relabel(int u) {
    h[u] = inf;
    for (int e = e0[u]; e; e = e1[e]) {
        int v = dst[e];
        if (w[e]) h[u] = min(h[u], h[v] + 1);
    }
}

int hlpp() {
    if (!bfs()) return 0;
    h[s] = n;
    for (int v = 1; v <= n; ++v)
        if (h[v] != inf) ++cnt[h[v]];
    inpq[s] = inpq[t] = 1;
    for (int e = e0[s]; e; e = e1[e]) {
        int v = dst[e];
        if (int f = w[e]) {
            w[e] -= f;
            w[e ^ 1] += f;
            fe[s] -= f;
            fe[v] += f;
            if (!inpq[v]) {
                pq[pqsz++] = v;
                push_heap(pq, pq + pqsz);
                inpq[v] = 1;
            }
        }
    }
    while (pqsz) {
        pop_heap(pq, pq + pqsz--);
        int u = pq[pqsz];
        inpq[u] = 0;
        push(u);
        if (fe[u]) {
            if (!--cnt[h[u]])
                for (int v = 1; v <= n; ++v)
                    if (v != s && v != t && h[v] > h[u] && h[v] < n + 1) h[v] = n + 1;
            relabel(u);
            ++cnt[h[u]];
            pq[pqsz++] = u;
            push_heap(pq, pq + pqsz);
            inpq[u] = 1;
        }
    }
    return fe[t];
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
    putln(hlpp());
    return 0;
}
