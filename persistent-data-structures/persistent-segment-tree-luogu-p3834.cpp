#include <bits/stdc++.h>
using namespace std;

//{{{
inline int geti() {
    int x, f = 0;
    char c;
    while (!isdigit(c = getchar()))
        if (c == '-') f = 1;
    for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0')
        ;
    return f ? -x : x;
}

inline long long getll() {
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

const int N = 200010;

int n, m, a[N], a0[N], rg, lc[N * 20], rc[N * 20], v[N * 20], rt[N], idx = 0;

inline int mk(int val, int l, int r) {
    v[++idx] = ~val ? val : v[l] + v[r];
    lc[idx] = l;
    rc[idx] = r;
    return idx;
}

int add(int rt, int l, int r, int x) {
    if (x < l || x > r) return rt;
    if (l == r) return mk(v[rt] + 1, 0, 0);
    int m = (l + r) >> 1;
    return mk(-1, add(lc[rt], l, m, x), add(rc[rt], m + 1, r, x));
}

int qry(int rt1, int rt2, int l, int r, int k) {
    if (l == r) return l;
    int cnt = v[lc[rt2]] - v[lc[rt1]];
    int m = (l + r) >> 1;
    return k <= cnt ? qry(lc[rt1], lc[rt2], l, m, k) : qry(rc[rt1], rc[rt2], m + 1, r, k - cnt);
}

int main() {
    n = geti();
    m = geti();
    for (int i = 1; i <= n; ++i) a[i] = geti();
    copy(a + 1, a + 1 + n, a0 + 1);
    sort(a + 1, a + 1 + n);
    rg = unique(a + 1, a + 1 + n) - a - 1;
    rt[0] = mk(0, 0, 0);
    for (int i = 1; i <= n; ++i) rt[i] = add(rt[i - 1], 1, rg, lower_bound(a + 1, a + 1 + rg, a0[i]) - a);
    while (m--) {
        int l = geti(), r = geti();
        putln(a[qry(rt[l - 1], rt[r], 1, rg, geti())]);
    }
    return 0;
}
