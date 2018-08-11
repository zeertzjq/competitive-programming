#include <bits/stdc++.h>
using namespace std;

inline int geti() {
    int x, f = 0;
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

const int N = 100010, K = 200010;

struct item {
    int a, b, c, idx, cnt;

    inline bool operator<(const item &rhs) const {
        return a == rhs.a ? b == rhs.b ? c < rhs.c : b < rhs.b : a < rhs.a;
    }

    inline bool operator==(const item &rhs) const {
        return a == rhs.a && b == rhs.b && c == rhs.c;
    }
} o[N], tmp[N];

int bit[K];
int f[N];
int ans[N];
int k;

inline void add(int p, int v) {
    while (p <= k) {
        bit[p] += v;
        p += p & -p;
    }
}

inline int query(int p) {
    int ret = 0;
    while (p) {
        ret += bit[p];
        p &= p - 1;
    }
    return ret;
}

inline void clear(int p) {
    while (p <= k && bit[p]) {
        bit[p] = 0;
        p += p & -p;
    }
}

void cdq(int l, int r) {
    if (l >= r) return;
    int m = (l + r) >> 1;
    cdq(l, m);
    cdq(m + 1, r);
    int p = l, q = m + 1, s = l;
    while (p <= m && q <= r) {
        if (o[p].b <= o[q].b) {
            add(o[p].c, o[p].cnt);
            tmp[s++] = o[p++];
        } else {
            f[o[q].idx] += query(o[q].c);
            tmp[s++] = o[q++];
        }
    }
    while (p <= m) tmp[s++] = o[p++];
    while (q <= r) {
        f[o[q].idx] += query(o[q].c);
        tmp[s++] = o[q++];
    }
    for (int i = l; i <= r; ++i) {
        clear(tmp[i].c);
        o[i] = tmp[i];
    }
}

int main() {
    int n0 = geti();
    k = geti();
    for (int i = 1; i <= n0; ++i) {
        o[i].a = geti();
        o[i].b = geti();
        o[i].c = geti();
    }
    sort(o + 1, o + n0 + 1);
    int n = 0;
    int ccnt = 0;
    for (int i = 1; i <= n0; ++i) {
        ++ccnt;
        if (i == n0 || !(o[i] == o[i + 1])) {
            o[++n] = o[i];
            o[n].idx = n;
            o[n].cnt = ccnt;
            ccnt = 0;
        }
    }
    cdq(1, n);
    for (int i = 1; i <= n; ++i)
        ans[f[o[i].idx] + o[i].cnt - 1] += o[i].cnt;
    for (int i = 0; i < n0; ++i) putln(ans[i]);
    return 0;
}
