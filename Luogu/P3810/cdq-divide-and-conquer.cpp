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

const int N = 100010, K = 200010;

struct itm {
    int a, b, c, id, cnt;

    inline bool operator<(const itm &rhs) const {
        return a == rhs.a ? b == rhs.b ? c < rhs.c : b < rhs.b : a < rhs.a;
    }

    inline bool operator==(const itm &rhs) const {
        return a == rhs.a && b == rhs.b && c == rhs.c;
    }
} q[N], tmp[N];

int bit[K], f[N], ans[N], k;

inline void upd(int p, int v) {
    for (; p <= k; p += p & -p) bit[p] += v;
}

inline int qry(int p) {
    int ans = 0;
    for (; p; p &= p - 1) ans += bit[p];
    return ans;
}

inline void clr(int p) {
    for (; p <= k && bit[p]; p += p & -p) bit[p] = 0;
}

void cdq(int l, int r) {
    if (l >= r) return;
    int m = (l + r) >> 1;
    cdq(l, m), cdq(m + 1, r);
    int p1 = l, p2 = m + 1, p = l;
    while (p1 <= m && p2 <= r) {
        if (q[p1].b <= q[p2].b)
            upd(q[p1].c, q[p1].cnt), tmp[p++] = q[p1++];
        else
            f[q[p2].id] += qry(q[p2].c), tmp[p++] = q[p2++];
    }
    while (p1 <= m) tmp[p++] = q[p1++];
    while (p2 <= r) f[q[p2].id] += qry(q[p2].c), tmp[p++] = q[p2++];
    for (int i = l; i <= r; ++i) clr(tmp[i].c), q[i] = tmp[i];
}

int main() {
    int n0 = gi();
    k = gi();
    for (int i = 1; i <= n0; ++i) q[i].a = gi(), q[i].b = gi(), q[i].c = gi();
    sort(q + 1, q + n0 + 1);
    int n = 0;
    int ccnt = 0;
    for (int i = 1; i <= n0; ++i) {
        ++ccnt;
        if (i == n0 || !(q[i] == q[i + 1]))
            q[++n] = q[i], q[n].id = n, q[n].cnt = ccnt, ccnt = 0;
    }
    cdq(1, n);
    for (int i = 1; i <= n; ++i) ans[f[q[i].id] + q[i].cnt - 1] += q[i].cnt;
    for (int i = 0; i < n0; ++i) putln(ans[i]);
    return 0;
}
