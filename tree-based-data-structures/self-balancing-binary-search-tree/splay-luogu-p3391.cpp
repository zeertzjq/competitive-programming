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
    int val, sz;
    node *c[2];
    bool tag;

    node(int v) { val = v, sz = 1, tag = 0, c[0] = c[1] = NULL; }

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

inline node *rotate(node *p, bool dir) {
    p->rev();
    node *s = p->c[!dir];
    s->rev();
    node *t = s->c[dir];
    s->c[dir] = p, p->c[!dir] = t, p->upd(), s->upd();
    return s;
}

node *splay(node *rt, int rk) {
    if (!rt) return rt;
    rt->rev();
    int lsz = rt->c[0] ? rt->c[0]->sz : 0;
    if (rk == lsz + 1)
        return rt;
    else if (rk <= lsz) {
        rt->c[0]->rev();
        int llsz = rt->c[0]->c[0] ? rt->c[0]->c[0]->sz : 0;
        if (rk <= llsz)
            rt->c[0]->c[0] = splay(rt->c[0]->c[0], rk), rt = rotate(rt, 1);
        else if (rk > llsz + 1)
            rt->c[0]->c[1] = splay(rt->c[0]->c[1], rk - llsz - 1),
            rt->c[0] = rotate(rt->c[0], 0);
        if (rt->c[0]) rt = rotate(rt, 1);
    } else {
        rt->c[1]->rev();
        int rlsz = rt->c[1]->c[0] ? lsz + 1 + rt->c[1]->c[0]->sz : lsz + 1;
        if (rk > rlsz + 1)
            rt->c[1]->c[1] = splay(rt->c[1]->c[1], rk - rlsz - 1),
            rt = rotate(rt, 0);
        else if (rk <= rlsz)
            rt->c[1]->c[0] = splay(rt->c[1]->c[0], rk - lsz - 1),
            rt->c[1] = rotate(rt->c[1], 1);
        if (rt->c[1]) rt = rotate(rt, 0);
    }
    rt->upd();
    return rt;
}

node *build(int l, int r) {
    if (l > r) return NULL;
    int m = (l + r) >> 1;
    node *rt = new node(m);
    rt->c[0] = build(l, m - 1), rt->c[1] = build(m + 1, r), rt->upd();
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
    node *rt = build(0, n + 1);
    while (m--) {
        int l = gi(), r = gi();
        rt = splay(rt, r + 2), rt->c[0] = splay(rt->c[0], l),
        rt->c[0]->c[1]->tag ^= 1;
    }
    inorder(rt), putchar('\n'), destroy(rt);
    return 0;
}
