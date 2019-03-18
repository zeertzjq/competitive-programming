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

const int N = 500010, inf = ~0U >> 1;
int seed = 19260817, n, rt[N], key[N * 38], c[N * 38][2], pri[N * 38],
    sz[N * 38], tot = 0;

inline int ran() { return seed = (seed * 1103515245LL + 12345LL) & inf; }

inline int mk(int k) {
    key[++tot] = k, pri[tot] = ran(), sz[tot] = 1;
    return tot;
}

inline int cp(int o) {
    key[++tot] = key[o], pri[tot] = pri[o], sz[tot] = sz[o],
    c[tot][0] = c[o][0], c[tot][1] = c[o][1];
    return tot;
}

inline void upd(int p) { sz[p] = 1 + sz[c[p][0]] + sz[c[p][1]]; }

void split(int rt, int k, int &l, int &r) {
    if (!rt) {
        l = r = 0;
        return;
    }
    rt = cp(rt);
    if (key[rt] <= k)
        l = rt, split(c[rt][1], k, c[rt][1], r);
    else
        r = rt, split(c[rt][0], k, l, c[rt][0]);
    upd(rt);
}

int merge(int l, int r) {
    if (!l || !r) return l | r;
    if (pri[l] > pri[r]) {
        c[l][1] = merge(c[l][1], r), upd(l);
        return l;
    } else {
        c[r][0] = merge(l, c[r][0]), upd(r);
        return r;
    }
}

inline int maxn(int rt) {
    while (c[rt][1]) rt = c[rt][1];
    return key[rt];
}

inline int minn(int rt) {
    while (c[rt][0]) rt = c[rt][0];
    return key[rt];
}

int kth(int rt, int rk) {
    int lsz = sz[c[rt][0]];
    if (rk <= lsz)
        return kth(c[rt][0], rk);
    else if (rk == lsz + 1)
        return key[rt];
    else
        return kth(c[rt][1], rk - lsz - 1);
}

int main() {
    n = gi();
    for (int i = 1; i <= n; ++i) {
        int v = gi(), o = gi(), x = gi();
        if (o == 1) {
            int t1, t2;
            split(rt[v], x, t1, t2), rt[i] = merge(merge(t1, mk(x)), t2);
        } else if (o == 2) {
            int t1, t2, t3;
            split(rt[v], x, t1, t3), split(t1, x - 1, t1, t2);
            if (t2)
                rt[i] = merge(merge(t1, merge(c[t2][0], c[t2][1])), t3);
            else
                rt[i] = rt[v];
        } else if (o == 3) {
            int t1, t2;
            split(rt[v], x - 1, t1, t2), putln(sz[t1] + 1), rt[i] = rt[v];
        } else if (o == 4) {
            putln(kth(rt[v], x)), rt[i] = rt[v];
        } else if (o == 5) {
            int t1, t2;
            split(rt[v], x - 1, t1, t2), putln(t1 ? maxn(t1) : -inf),
                rt[i] = rt[v];
        } else {
            int t1, t2;
            split(rt[v], x, t1, t2), putln(t2 ? minn(t2) : inf), rt[i] = rt[v];
        }
    }
    return 0;
}
