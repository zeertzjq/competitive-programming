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

struct node {
    int val;
    node *c[2];

    node(int v, node *c0, node *c1) {
        val = v;
        c[0] = c0;
        c[1] = c1;
        if (!v && c0 && c1) upd();
    }

    void upd() {
        val = c[0]->val + c[1]->val;
    }
};

int n, m, a[N], a0[N], rg;
node *rt[N], *nil = new node(0, NULL, NULL);

node *add(node *rt, int l, int r, int x) {
    if (x < l || x > r) return rt;
    if (l == r) return new node(rt->val + 1, nil, nil);
    int m = (l + r) >> 1;
    return new node(0, add(rt->c[0], l, m, x), add(rt->c[1], m + 1, r, x));
}

int qry(node *rt1, node *rt2, int l, int r, int k) {
    if (l == r) return l;
    int cnt = rt2->c[0]->val - rt1->c[0]->val;
    int m = (l + r) >> 1;
    return k <= cnt ? qry(rt1->c[0], rt2->c[0], l, m, k) : qry(rt1->c[1], rt2->c[1], m + 1, r, k - cnt);
}

int main() {
    nil->c[0] = nil->c[1] = nil;
    n = geti();
    m = geti();
    for (int i = 1; i <= n; ++i) a[i] = geti();
    copy(a + 1, a + 1 + n, a0 + 1);
    sort(a + 1, a + 1 + n);
    rg = unique(a + 1, a + 1 + n) - a - 1;
    rt[0] = nil;
    for (int i = 1; i <= n; ++i) rt[i] = add(rt[i - 1], 1, rg, lower_bound(a + 1, a + 1 + rg, a0[i]) - a);
    while (m--) {
        int l = geti(), r = geti();
        putln(a[qry(rt[l - 1], rt[r], 1, rg, geti())]);
    }
    return 0;
}
