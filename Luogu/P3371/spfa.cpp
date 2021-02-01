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

const int N = 10010, M = 500010, inf = ~0U >> 1;
int n, m, s, e0[N], e1[M], to[M], w[M], dis[N], q[N], head = 1, tail = 0;
bool inq[N];

inline int &qo(int &x) { return x == N ? x = 0 : x; }

void spfa() {
    fill(dis + 1, dis + 1 + n, inf), dis[s] = 0, q[++tail] = s, inq[s] = 1;
    while (head != tail + 1) {
        int u = q[head++];
        qo(head), inq[u] = 0;
        for (int e = e0[u]; e; e = e1[e]) {
            int v = to[e], ndis = dis[u] + w[e];
            if (ndis < dis[v]) {
                dis[v] = ndis;
                if (!inq[v]) q[qo(++tail)] = v, inq[v] = 1;
            }
        }
    }
}

int main() {
    n = gi(), m = gi(), s = gi();
    for (int i = 1; i <= m; ++i) {
        int f = gi();
        e1[i] = e0[f], e0[f] = i, to[i] = gi(), w[i] = gi();
    }
    spfa();
    for (int i = 1; i <= n; ++i) putsp(dis[i]);
    putchar('\n');
    return 0;
}
