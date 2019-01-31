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

const int INF = 2147483647;
int seed = 19260817;

int ran() {
    return seed = (seed * 1103515245LL + 12345LL) & 2147483647;
}

struct node {
    int key, pri, cnt, sz;
    node *c[2];

    node(int k) {
        key = k;
        pri = ran();
        sz = cnt = 1;
        c[0] = c[1] = NULL;
    }

    inline void update() {
        sz = (c[0] ? c[0]->sz : 0) + (c[1] ? c[1]->sz : 0) + cnt;
    }

    inline node *stpred() {
        if (!c[0]) return NULL;
        node *ret = c[0];
        while (ret->c[1]) ret = ret->c[1];
        return ret;
    }

    inline node *stsucc() {
        if (!c[1]) return NULL;
        node *ret = c[1];
        while (ret->c[0]) ret = ret->c[0];
        return ret;
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

node *insitem(node *rt, int key) {
    if (!rt) return new node(key);
    if (key == rt->key) {
        ++rt->cnt;
        ++rt->sz;
        return rt;
    }
    bool dir = 0;
    if (key > rt->key) dir = 1;
    rt->c[dir] = insitem(rt->c[dir], key);
    rt->update();
    if (rt->c[dir]->pri > rt->pri) rt = rotate(rt, !dir);
    return rt;
}

node *delitem(node *rt, int key) {
    if (!rt) return rt;
    if (key < rt->key) {
        rt->c[0] = delitem(rt->c[0], key);
        rt->update();
        return rt;
    } else if (key > rt->key) {
        rt->c[1] = delitem(rt->c[1], key);
        rt->update();
        return rt;
    } else {
        if (rt->cnt > 1) {
            --rt->cnt;
            --rt->sz;
            return rt;
        } else if (!rt->c[0]) {
            node *tmp = rt->c[1];
            delete rt;
            return tmp;
        } else if (!rt->c[1]) {
            node *tmp = rt->c[0];
            delete rt;
            return tmp;
        } else {
            bool dir = 0;
            if (rt->c[!dir]->pri > rt->c[dir]->pri) dir ^= 1;
            rt = rotate(rt, !dir);
            rt->c[!dir] = delitem(rt->c[!dir], key);
            rt->update();
            return rt;
        }
    }
}

int getlesscnt(node *rt, int key) {
    if (!rt) return 0;
    int lsz = 0;
    if (rt->c[0]) lsz = rt->c[0]->sz;
    if (key < rt->key)
        return getlesscnt(rt->c[0], key);
    else if (key == rt->key)
        return lsz;
    else
        return lsz + rt->cnt + getlesscnt(rt->c[1], key);
}

int getnth(node *rt, int rk) {
    if (!rt) return -INF;
    int lsz = 0;
    if (rt->c[0]) lsz = rt->c[0]->sz;
    if (rk <= lsz)
        return getnth(rt->c[0], rk);
    else if (rk <= lsz + rt->cnt)
        return rt->key;
    else
        return getnth(rt->c[1], rk - lsz - rt->cnt);
}

int pred(node *rt, int key) {
    if (!rt) return -INF;
    if (key == rt->key) {
        node *p = rt->stpred();
        if (!p)
            return -INF;
        else
            return p->key;
    } else if (key < rt->key)
        return pred(rt->c[0], key);
    else
        return max(rt->key, pred(rt->c[1], key));
}

int succ(node *rt, int key) {
    if (!rt) return INF;
    if (key == rt->key) {
        node *p = rt->stsucc();
        if (!p)
            return INF;
        else
            return p->key;
    } else if (key > rt->key)
        return succ(rt->c[1], key);
    else
        return min(rt->key, succ(rt->c[0], key));
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
        else if (opt == 3)
            putln(1 + getlesscnt(rt, x));
        else if (opt == 4)
            putln(getnth(rt, x));
        else if (opt == 5)
            putln(pred(rt, x));
        else if (opt == 6)
            putln(succ(rt, x));
    }
    destroy(rt);
    return 0;
}
