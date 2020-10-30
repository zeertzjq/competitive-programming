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

const int N = 50010;
int n, m, ans[N], aidx = 0;

struct itm {
    bool tp;
    int l, r, id;
    long long c;
} q[N], q1[N], q2[N];

long long sum[N << 2], tag[N << 2];
bool dirty[N << 2];

#define L (x << 1)
#define R (x << 1 | 1)

inline void push(int x, int l, int r) {
    if (dirty[x])
        dirty[L] = dirty[R] = 1,
        dirty[x] = sum[L] = sum[R] = tag[L] = tag[R] = 0;

    if (tag[x]) {
        int m = (l + r) >> 1;
        sum[L] += tag[x] * (m - l + 1), sum[R] += tag[x] * (r - m),
            tag[L] += tag[x], tag[R] += tag[x], tag[x] = 0;
    }
}

void upd(int x, int l, int r, int ml, int mr) {
    if (l > r) return;
    if (mr < l || ml > r) return;
    if (ml <= l && mr >= r) {
        sum[x] += r - l + 1, ++tag[x];
        return;
    }
    push(x, l, r);
    int m = (l + r) >> 1;
    upd(L, l, m, ml, mr), upd(R, m + 1, r, ml, mr), sum[x] = sum[L] + sum[R];
}

long long qry(int x, int l, int r, int ql, int qr) {
    if (l > r) return 0;
    if (qr < l || ql > r) return 0;
    if (ql <= l && qr >= r) return sum[x];
    push(x, l, r);
    int m = (l + r) >> 1;
    return qry(L, l, m, ql, qr) + qry(R, m + 1, r, ql, qr);
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
    tag[1] = sum[1] = 0, dirty[1] = 1;
    for (int i = ql; i <= qr; ++i)
        if (!q[i].tp) {
            if (q[i].c > m)
                upd(1, 1, n, q[i].l, q[i].r), q2[++p2] = q[i];
            else
                q1[++p1] = q[i];
        } else {
            long long gtr = qry(1, 1, n, q[i].l, q[i].r);
            if (q[i].c > gtr)
                q[i].c -= gtr, q1[++p1] = q[i];
            else
                q2[++p2] = q[i];
        }
    copy(q1 + 1, q1 + 1 + p1, q + ql), copy(q2 + 1, q2 + 1 + p2, q + ql + p1),
        solve(ql, ql + p1 - 1, l, m), solve(ql + p1, qr, m + 1, r);
}

int main() {
    n = gi(), m = gi();
    for (int i = 1; i <= m; ++i)
        q[i].tp = gi() - 1, q[i].l = gi(), q[i].r = gi(),
        q[i].c = q[i].tp ? gll() : gi(), q[i].id = q[i].tp ? ++aidx : 0;
    solve(1, m, -n, n);
    for (int i = 1; i <= aidx; ++i) putln(ans[i]);
    return 0;
}
