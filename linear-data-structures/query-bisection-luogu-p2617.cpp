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

inline char gc() {
    char c;
    while (isspace(c = getchar()))
        ;
    return c;
}

const int N = 100010;
int n, m, a[N], aidx = 0, v[N << 1], vidx, ans[N], qidx, bit[N];

struct itm {
    bool tp;
    int l, r, k, id;
} q[N * 3], q1[N * 3], q2[N * 3];

inline void upd(int k, int v) {
    while (k <= n) {
        bit[k] += v;
        k += k & -k;
    }
}

inline int qry(int k) {
    int ans = 0;
    while (k) {
        ans += bit[k];
        k &= k - 1;
    }
    return ans;
}

void solve(int ql, int qr, int l, int r) {
    if (ql > qr || l > r) return;
    if (l == r) {
        for (int i = ql; i <= qr; ++i)
            if (q[i].tp) ans[q[i].id] = l;
        return;
    }
    int m = (l + r) >> 1;
    int p1 = 0, p2 = 0;
    for (int i = ql; i <= qr; ++i)
        if (!q[i].tp) {
            if (q[i].k <= m) {
                upd(q[i].l, q[i].r);
                q1[++p1] = q[i];
            } else
                q2[++p2] = q[i];
        } else {
            int lss = qry(q[i].r) - qry(q[i].l - 1);
            if (q[i].k > lss) {
                q[i].k -= lss;
                q2[++p2] = q[i];
            } else
                q1[++p1] = q[i];
        }
    for (int i = 1; i <= p1; ++i)
        if (!q1[i].tp) upd(q1[i].l, -q1[i].r);
    copy(q1 + 1, q1 + 1 + p1, q + ql);
    copy(q2 + 1, q2 + 1 + p2, q + ql + p1);
    solve(ql, ql + p1 - 1, l, m);
    solve(ql + p1, qr, m + 1, r);
}

int main() {
    n = gi();
    m = gi();
    for (int i = 1; i <= n; ++i) {
        q[i].tp = 0;
        q[i].l = i;
        q[i].r = 1;
        a[i] = v[i] = q[i].k = gi();
    }
    qidx = vidx = n;
    while (m--) {
        if (q[++qidx].tp = gc() == 'Q') {
            q[qidx].l = gi();
            q[qidx].r = gi();
            q[qidx].k = gi();
            q[qidx].id = ++aidx;
        } else {
            int p = gi();
            q[qidx].l = p;
            q[qidx].r = -1;
            q[qidx].k = a[p];
            q[++qidx].tp = 0;
            q[qidx].l = p;
            q[qidx].r = 1;
            a[p] = v[++vidx] = q[qidx].k = gi();
        }
    }
    sort(v + 1, v + 1 + vidx);
    vidx = unique(v + 1, v + 1 + vidx) - v - 1;
    for (int i = 1; i <= qidx; ++i)
        if (!q[i].tp) q[i].k = lower_bound(v + 1, v + 1 + vidx, q[i].k) - v;
    solve(1, qidx, 1, vidx);
    for (int i = 1; i <= aidx; ++i) putln(v[ans[i]]);
    return 0;
}
