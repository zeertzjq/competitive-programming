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

const int N = 100010, E = N << 1, S = N * 68;
int n, m, e0[N], e1[E], to[E], rt[N], mx[S], c[S][2], q0[N], q1[E], qi[E], p[N],
    fa[N], z[N], ans[N], tot = 0;
bool ck[N];

int finds(int x) { return p[x] == x ? x : p[x] = finds(p[x]); }

void upd(int &rt, int l, int r, int x, int w) {
    if (!rt) rt = ++tot;
    if (l == r) {
        mx[rt] += w;
        return;
    }
    int m = (l + r) >> 1;
    x <= m ? upd(c[rt][0], l, m, x, w) : upd(c[rt][1], m + 1, r, x, w),
        mx[rt] = max(mx[c[rt][0]], mx[c[rt][1]]);
}

inline int qmx(int rt) {
    if (!mx[rt]) return 0;
    int l = 1, r = N;
    while (l != r) {
        int m = (l + r) >> 1;
        if (mx[c[rt][0]] >= mx[c[rt][1]])
            r = m, rt = c[rt][0];
        else
            l = m + 1, rt = c[rt][1];
    }
    return l;
}

void mrg(int &a, int b, int l, int r) {
    if (!a || !b) {
        a |= b;
        return;
    }
    if (l == r) {
        mx[a] += mx[b];
        return;
    }
    int m = (l + r) >> 1;
    mrg(c[a][0], c[b][0], l, m), mrg(c[a][1], c[b][1], m + 1, r),
        mx[a] = max(mx[c[a][0]], mx[c[a][1]]);
}

void dfs(int u) {
    for (int e = e0[u]; e; e = e1[e]) {
        int v = to[e];
        if (v == fa[u]) continue;
        fa[v] = u, dfs(v), p[v] = u, mrg(rt[u], rt[v], 1, N);
    }
    for (int q = q0[u]; q; q = q1[q]) {
        int a = q >> 1, v = qi[q];
        if (!ck[a])
            ck[a] = 1;
        else {
            int lca = finds(v);
            upd(rt[lca], 1, N, z[a], -1);
            if (fa[lca]) upd(rt[fa[lca]], 1, N, z[a], -1);
        }
    }
    ans[u] = qmx(rt[u]);
}

int main() {
    n = gi(), m = gi();
    for (int i = 1; i < n; ++i) {
        int a = gi(), b = gi();
        e1[i << 1] = e0[a], e0[a] = i << 1, to[i << 1] = b,
                e1[i << 1 | 1] = e0[b], e0[b] = i << 1 | 1, to[i << 1 | 1] = a;
    }
    for (int i = 1; i <= m; ++i) {
        int x = gi(), y = gi();
        z[i] = gi(), upd(rt[x], 1, N, z[i], 1), upd(rt[y], 1, N, z[i], 1),
        q1[i << 1] = q0[x], q0[x] = i << 1, qi[i << 1] = y,
        q1[i << 1 | 1] = q0[y], q0[y] = i << 1 | 1, qi[i << 1 | 1] = x;
    }
    for (int i = 1; i <= n; ++i) p[i] = i;
    dfs(1);
    for (int i = 1; i <= n; ++i) putln(ans[i]);
    return 0;
}
