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
    int key;
    int sheight;
    int cnt;
    int sz;

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

    // IMPORTANT: call update() whenever the subtree rooted at the node is modified
    inline void update() {
        sheight = max(c[0] ? c[0]->sheight : 0, c[1] ? c[1]->sheight : 0) + 1;
        sz = (c[0] ? c[0]->sz : 0) + (c[1] ? c[1]->sz : 0) + cnt;
    }

    inline int bal() {
        return (c[1] ? c[1]->sheight : 0) - (c[0] ? c[0]->sheight : 0);
    }

    node(int k) {
        key = k;
        sheight = 1;
        c[0] = c[1] = NULL;
        cnt = sz = 1;
    }
};

inline node *rotate(node *p, bool dir) {
    node *s = p->c[!dir], *t = s->c[dir];
    p->c[!dir] = t;
    s->c[dir] = p;
    p->update();
    s->update();
    return s;
}

void destroy(node *rt) {
    if (!rt) return;
    destroy(rt->c[0]);
    destroy(rt->c[1]);
    delete rt;
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
    int bal = rt->bal();
    if (bal < -1) {
        if (key > rt->c[0]->key) rt->c[0] = rotate(rt->c[0], 0);
        rt = rotate(rt, 1);
    }
    if (bal > 1) {
        if (key < rt->c[1]->key) rt->c[1] = rotate(rt->c[1], 1);
        rt = rotate(rt, 0);
    }
    return rt;
}

node *delitem(node *rt, int key) {
    if (!rt) return rt;
    if (key == rt->key) {
        if (rt->cnt > 1) {
            --rt->cnt;
            --rt->sz;
            return rt;
        } else {
            if (!rt->c[0]) {
                node *tmp = rt->c[1];
                delete rt;
                return tmp;
            } else if (!rt->c[1]) {
                node *tmp = rt->c[0];
                delete rt;
                return tmp;
            } else {
                node *p = rt->stsucc();
                key = rt->key = p->key;
                swap(rt->cnt, p->cnt);
            }
        }
    }
    bool dir = 1;
    if (key < rt->key) dir = 0;
    rt->c[dir] = delitem(rt->c[dir], key);
    rt->update();
    int bal = rt->bal();
    if (bal < -1) {
        if (rt->c[0]->bal() > 0) rt->c[0] = rotate(rt->c[0], 0);
        rt = rotate(rt, 1);
    }
    if (bal > 1) {
        if (rt->c[1]->bal() < 0) rt->c[1] = rotate(rt->c[1], 1);
        rt = rotate(rt, 0);
    }
    return rt;
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
