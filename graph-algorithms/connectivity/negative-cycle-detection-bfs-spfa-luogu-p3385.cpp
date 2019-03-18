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

const int N = 2010, M = 3010, inf = ~0U >> 1;
int n, m;
int e0[N], e1[M << 1], dst[M << 1], w[M << 1], dis[N], cnt[N], inq[N];

queue<int> q;

inline void clear() {
    for (int i = 1; i <= n; ++i) cnt[i] = 0, dis[i] = inf;
    while (!q.empty()) inq[q.front()] = 0, q.pop();
}

inline void push(int v) { ++cnt[v], inq[v] = 1, q.push(v); }

inline int pop() {
    int v = q.front(), inq[v] = 0, q.pop();
    return v;
}

int detect() {
    clear(), dis[1] = 0, push(1);
    while (!q.empty()) {
        int u = pop();
        for (int e = e0[u]; e; e = e1[e]) {
            int v = dst[e];
            int ndis = dis[u] + w[e];
            if (ndis < dis[v]) {
                dis[v] = ndis;
                if (inq[v]) continue;
                if (cnt[v] >= n) return 1;
                push(v);
            }
        }
    }
    return 0;
}

int main() {
    int T = gi();
    while (T--) {
        n = gi(), m = gi();
        int ecnt = 0;
        for (int i = 1; i <= n; ++i) e0[i] = 0;
        while (m--) {
            int a = gi(), b = gi(), w0 = gi();
            e1[++ecnt] = e0[a], e0[a] = ecnt, dst[ecnt] = b, w[ecnt] = w0;
            if (w0 >= 0)
                e1[++ecnt] = e0[b], e0[b] = ecnt, dst[ecnt] = a, w[ecnt] = w0;
        }
        puts(detect() ? "YE5" : "N0");
    }
    return 0;
}
