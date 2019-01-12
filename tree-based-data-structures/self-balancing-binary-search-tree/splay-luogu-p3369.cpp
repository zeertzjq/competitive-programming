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

const int INF = 2147483647;

struct node {
    node *c[2];
    int key, cnt, sz;

    node(int k) {
        key = k;
        sz = cnt = 1;
        c[0] = c[1] = NULL;
    }

    inline void update() {
        sz = (c[0] ? c[0]->sz : 0) + (c[1] ? c[1]->sz : 0) + cnt;
    }
};

inline node *rotate(node *p, bool dir) {
    node *s = p->c[!dir], *t = s->c[dir];
    s->c[dir] = p;
    p->c[!dir] = t;
    p->update();
    s->update();
    return s;
}

node *splay(node *rt, int key) {
    if (!rt || key == rt->key) return rt;
    if (key < rt->key) {
        if (!rt->c[0]) return rt;
        if (key < rt->c[0]->key) {
            rt->c[0]->c[0] = splay(rt->c[0]->c[0], key);
            rt = rotate(rt, 1);
        } else if (key > rt->c[0]->key) {
            rt->c[0]->c[1] = splay(rt->c[0]->c[1], key);
            if (rt->c[0]->c[1]) rt->c[0] = rotate(rt->c[0], 0);
        }
        if (rt->c[0]) rt = rotate(rt, 1);
    } else {
        if (!rt->c[1]) return rt;
        if (key > rt->c[1]->key) {
            rt->c[1]->c[1] = splay(rt->c[1]->c[1], key);
            rt = rotate(rt, 0);
        } else if (key < rt->c[1]->key) {
            rt->c[1]->c[0] = splay(rt->c[1]->c[0], key);
            if (rt->c[1]->c[0]) rt->c[1] = rotate(rt->c[1], 1);
        }
        if (rt->c[1]) rt = rotate(rt, 0);
    }
    return rt;
}

node *insitem(node *rt, int key) {
    if (!rt) return new node(key);
    rt = splay(rt, key);
    if (key == rt->key) {
        ++rt->cnt;
        ++rt->sz;
        return rt;
    } else if (rt->key < key) {
        node *nrt = new node(key);
        nrt->c[0] = rt;
        nrt->c[1] = rt->c[1];
        rt->c[1] = NULL;
        rt->update();
        nrt->update();
        return nrt;
    } else {
        node *nrt = new node(key);
        nrt->c[1] = rt;
        nrt->c[0] = rt->c[0];
        rt->c[0] = NULL;
        rt->update();
        nrt->update();
        return nrt;
    }
}

node *delitem(node *rt, int key) {
    if (!rt) return rt;
    rt = splay(rt, key);
    if (key != rt->key) return rt;
    if (rt->cnt > 1) {
        --rt->cnt;
        --rt->sz;
        return rt;
    } else {
        node *nrt = rt->c[0];
        if (!nrt)
            nrt = rt->c[1];
        else {
            nrt = splay(nrt, key);
            nrt->c[1] = rt->c[1];
            nrt->update();
        }
        delete rt;
        return nrt;
    }
}

int getnth(node *rt, int rk) {
    if (!rt) return INF;
    int lsz = 0;
    if (rt->c[0]) lsz = rt->c[0]->sz;
    if (rk <= lsz)
        return getnth(rt->c[0], rk);
    else if (rk <= lsz + rt->cnt)
        return rt->key;
    else
        return getnth(rt->c[1], rk - lsz - rt->cnt);
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
        if (opt == 1)
            rt = insitem(rt, x);
        else if (opt == 2)
            rt = delitem(rt, x);
        else if (opt == 3) {
            rt = splay(rt, x);
            int lsz = 0;
            if (rt->c[0]) lsz = rt->c[0]->sz;
            putln(lsz + 1);
        } else if (opt == 4) {
            putln(getnth(rt, x));
        } else if (opt == 5) {
            rt = splay(rt, x);
            node *res = rt;
            if (res->key >= x) res = rt->c[0] = splay(rt->c[0], x);
            putln(res->key);
        } else if (opt == 6) {
            rt = splay(rt, x);
            node *res = rt;
            if (res->key <= x) res = rt->c[1] = splay(rt->c[1], x);
            putln(res->key);
        }
    }
    destroy(rt);
}
