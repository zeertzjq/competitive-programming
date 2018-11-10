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

const int INF = 2147483647;

struct node {
    node *son[2];
    int key, cnt, sz;

    node(int k) {
        key = k;
        sz = cnt = 1;
        son[0] = son[1] = NULL;
    }

    void update() {
        sz = cnt;
        if (son[0]) sz += son[0]->sz;
        if (son[1]) sz += son[1]->sz;
    }
};

void destroy(node *rt) {
    if (!rt) return;
    destroy(rt->son[0]);
    destroy(rt->son[1]);
    delete rt;
}

node *rotate(node *p, bool dir) {
    node *s = p->son[!dir], *t = s->son[dir];
    s->son[dir] = p;
    p->son[!dir] = t;
    p->update();
    s->update();
    return s;
}

node *splay(node *rt, int key) {
    if (!rt || key == rt->key) return rt;
    if (key < rt->key) {
        if (!rt->son[0]) return rt;
        if (key < rt->son[0]->key) {
            rt->son[0]->son[0] = splay(rt->son[0]->son[0], key);
            rt = rotate(rt, 1);
        } else if (key > rt->son[0]->key) {
            rt->son[0]->son[1] = splay(rt->son[0]->son[1], key);
            if (rt->son[0]->son[1]) rt->son[0] = rotate(rt->son[0], 0);
        }
        if (rt->son[0]) rt = rotate(rt, 1);
    } else {
        if (!rt->son[1]) return rt;
        if (key > rt->son[1]->key) {
            rt->son[1]->son[1] = splay(rt->son[1]->son[1], key);
            rt = rotate(rt, 0);
        } else if (key < rt->son[1]->key) {
            rt->son[1]->son[0] = splay(rt->son[1]->son[0], key);
            if (rt->son[1]->son[0]) rt->son[1] = rotate(rt->son[1], 1);
        }
        if (rt->son[1]) rt = rotate(rt, 0);
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
        nrt->son[0] = rt;
        nrt->son[1] = rt->son[1];
        rt->son[1] = NULL;
        rt->update();
        nrt->update();
        return nrt;
    } else {
        node *nrt = new node(key);
        nrt->son[1] = rt;
        nrt->son[0] = rt->son[0];
        rt->son[0] = NULL;
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
        node *nrt = rt->son[0];
        if (!nrt)
            nrt = rt->son[1];
        else {
            nrt = splay(nrt, key);
            nrt->son[1] = rt->son[1];
            nrt->update();
        }
        delete rt;
        return nrt;
    }
}

int getnth(node *rt, int rank) {
    if (!rt) return INF;
    int lsz = 0;
    if (rt->son[0]) lsz = rt->son[0]->sz;
    if (rank <= lsz)
        return getnth(rt->son[0], rank);
    else if (rank <= lsz + rt->cnt)
        return rt->key;
    else
        return getnth(rt->son[1], rank - lsz - rt->cnt);
}

int main() {
    int _ = geti();
    node *rt = NULL;
    while (_--) {
        int opt = geti(), x = geti();
        if (opt == 1)
            rt = insitem(rt, x);
        else if (opt == 2)
            rt = delitem(rt, x);
        else if (opt == 3) {
            rt = splay(rt, x);
            int lsz = 0;
            if (rt->son[0]) lsz = rt->son[0]->sz;
            putln(lsz + 1);
        } else if (opt == 4) {
            putln(getnth(rt, x));
        } else if (opt == 5) {
            rt = splay(rt, x);
            node *res = rt;
            if (res->key >= x) res = rt->son[0] = splay(rt->son[0], x);
            putln(res->key);
        } else if (opt == 6) {
            rt = splay(rt, x);
            node *res = rt;
            if (res->key <= x) res = rt->son[1] = splay(rt->son[1], x);
            putln(res->key);
        }
    }
    destroy(rt);
}
