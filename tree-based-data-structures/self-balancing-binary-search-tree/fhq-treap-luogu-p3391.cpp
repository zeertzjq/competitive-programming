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

const int inf = ~0U >> 1;
int n, m;

struct node {
    int val, pri, sz;
    node *c[2];
    bool tag;

    node(int v, int p) {
        val = v, pri = p, sz = 1, c[0] = c[1] = NULL, tag = 0;
    }

    inline void upd() {
        sz = (c[0] ? c[0]->sz : 0) + (c[1] ? c[1]->sz : 0) + 1;
    }

    inline void rev() {
        if (!tag) return;
        tag = 0;
        if (c[0]) c[0]->tag ^= 1;
        if (c[1]) c[1]->tag ^= 1;
        swap(c[0], c[1]);
    }
};

void splt(node *rt, int rk, node *&l, node *&r) {
    if (!rt) {
        l = r = NULL;
        return;
    }
    rt->rev();
    int lsz = rt->c[0] ? rt->c[0]->sz : 0;
    if (rk <= lsz)
        r = rt, splt(rt->c[0], rk, l, rt->c[0]);
    else
        l = rt, splt(rt->c[1], rk - lsz - 1, rt->c[1], r);
    rt->upd();
}

node *mrg(node *l, node *r) {
    if (!l) return r;
    if (!r) return l;
    if (l->pri < r->pri) {
        l->rev(), l->c[1] = mrg(l->c[1], r), l->upd();
        return l;
    } else {
        r->rev(), r->c[0] = mrg(l, r->c[0]), r->upd();
        return r;
    }
}

node *bld(int l, int r, int d) {
    if (l > r) return NULL;
    int m = (l + r) >> 1;
    node *rt = new node(m, d);
    rt->c[0] = bld(l, m - 1, d + 1), rt->c[1] = bld(m + 1, r, d + 1), rt->upd();
    return rt;
}

void inorder(node *rt) {
    if (!rt) return;
    rt->rev(), inorder(rt->c[0]);
    if (rt->val > 0 && rt->val <= n) putsp(rt->val);
    inorder(rt->c[1]);
}

void destroy(node *rt) {
    if (!rt) return;
    destroy(rt->c[0]), destroy(rt->c[1]);
    delete rt;
}

int main() {
    n = gi(), m = gi();
    node *rt = bld(1, n, 1);
    while (m--) {
        int l = gi(), r = gi();
        node *t1, *t2, *t3;
        splt(rt, r, t1, t3), splt(t1, l - 1, t1, t2), t2->tag ^= 1,
            rt = mrg(mrg(t1, t2), t3);
    }
    inorder(rt), putchar('\n'), destroy(rt);
    return 0;
}
