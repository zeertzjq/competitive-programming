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

const int N = 1000010;
int n, m, a[N], rt[N], lc[N * 20], rc[N * 20], val[N * 20], tot = 0;

inline int mk(int v, int l, int r) {
    val[++tot] = v;
    lc[tot] = l;
    rc[tot] = r;
    return tot;
}

int build(int l, int r) {
    if (l == r) return mk(a[l], 0, 0);
    int m = (l + r) >> 1;
    return mk(0, build(l, m), build(m + 1, r));
}

int upd(int rt, int l, int r, int x, int v) {
    if (x < l || x > r) return rt;
    if (l == r) return mk(v, 0, 0);
    int m = (l + r) >> 1;
    return mk(0, upd(lc[rt], l, m, x, v), upd(rc[rt], m + 1, r, x, v));
}

int qry(int rt, int l, int r, int x) {
    if (l == r) return val[rt];
    int m = (l + r) >> 1;
    return x <= m ? qry(lc[rt], l, m, x) : qry(rc[rt], m + 1, r, x);
}

int main() {
    n = gi();
    m = gi();
    for (int i = 1; i <= n; ++i) a[i] = gi();
    rt[0] = build(1, n);
    for (int i = 1; i <= m; ++i) {
        int v = gi(), o = gi(), x = gi();
        if (o == 1)
            rt[i] = upd(rt[v], 1, n, x, gi());
        else
            putln(qry(rt[i] = rt[v], 1, n, x));
    }
    return 0;
}
