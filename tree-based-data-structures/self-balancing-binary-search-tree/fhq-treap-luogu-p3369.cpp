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

const int inf = ~0U >> 1;
int seed = 19260817;

inline int ran() { return seed = (seed * 1103515245LL + 12345LL) & inf; }

struct node {
    int key, pri, sz;
    node *c[2];

    node(int k) {
        key = k;
        pri = ran();
        sz = 1;
        c[0] = c[1] = NULL;
    }

    inline void update() {
        sz = (c[0] ? c[0]->sz : 0) + (c[1] ? c[1]->sz : 0) + 1;
    }

    inline int min() {
        node *cur = this;
        while (cur->c[0]) cur = cur->c[0];
        return cur->key;
    }

    inline int max() {
        node *cur = this;
        while (cur->c[1]) cur = cur->c[1];
        return cur->key;
    }
};

void split(node *rt, int key, node *&l, node *&r) {
    if (!rt) {
        l = r = NULL;
        return;
    }
    if (rt->key <= key) {
        l = rt;
        split(rt->c[1], key, rt->c[1], r);
    } else {
        r = rt;
        split(rt->c[0], key, l, rt->c[0]);
    }
    rt->update();
}

node *merge(node *l, node *r) {
    if (!l) return r;
    if (!r) return l;
    if (l->pri > r->pri) {
        l->c[1] = merge(l->c[1], r);
        l->update();
        return l;
    } else {
        r->c[0] = merge(l, r->c[0]);
        r->update();
        return r;
    }
}

int getkth(node *rt, int rk) {
    int lsz = 0;
    if (rt->c[0]) lsz = rt->c[0]->sz;
    if (rk <= lsz)
        return getkth(rt->c[0], rk);
    else if (rk == lsz + 1)
        return rt->key;
    else
        return getkth(rt->c[1], rk - lsz - 1);
}

void destroy(node *rt) {
    if (!rt) return;
    destroy(rt->c[0]);
    destroy(rt->c[1]);
    delete rt;
}

int main() {
    int _ = gi();
    node *rt = NULL;
    while (_--) {
        int opt = gi(), x = gi();
        if (opt == 1) {
            node *t1, *t2;
            split(rt, x, t1, t2);
            rt = merge(merge(t1, new node(x)), t2);
        } else if (opt == 2) {
            node *t1, *t2, *t3;
            split(rt, x, t1, t3);
            split(t1, x - 1, t1, t2);
            rt = merge(merge(t1, merge(t2->c[0], t2->c[1])), t3);
        } else if (opt == 3) {
            node *t1, *t2;
            split(rt, x - 1, t1, t2);
            putln(t1 ? t1->sz + 1 : 1);
            rt = merge(t1, t2);
        } else if (opt == 4) {
            putln(getkth(rt, x));
        } else if (opt == 5) {
            node *t1, *t2;
            split(rt, x - 1, t1, t2);
            putln(t1->max());
            rt = merge(t1, t2);
        } else if (opt == 6) {
            node *t1, *t2;
            split(rt, x, t1, t2);
            putln(t2->min());
            rt = merge(t1, t2);
        }
    }
    destroy(rt);
    return 0;
}
