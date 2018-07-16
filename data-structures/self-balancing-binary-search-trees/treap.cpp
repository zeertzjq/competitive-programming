// https://www.luogu.org/problemnew/show/P3369
#include <bits/stdc++.h>
using namespace std;

const int INF = 2147483647;
int seed = 19260817;

int ran() {
    return seed = (seed * 1103515245LL + 12345LL) % 2147483648;
}

struct node {
    int key, val, cnt, sz;
    node *son[2];

    node(int k) {
        key = k;
        val = ran();
        sz = cnt = 1;
        son[0] = son[1] = NULL;
    }

    void update() {
        sz = cnt;
        if (son[0]) sz += son[0]->sz;
        if (son[1]) sz += son[1]->sz;
    }

    node *stpred() {
        if (!son[0]) return NULL;
        node *ret = son[0];
        while (ret->son[1]) ret = ret->son[1];
        return ret;
    }

    node *stsucc() {
        if (!son[1]) return NULL;
        node *ret = son[1];
        while (ret->son[0]) ret = ret->son[0];
        return ret;
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

node *insitem(node *rt, int key) {
    if (!rt) return new node(key);
    if (key == rt->key) {
        ++rt->cnt;
        ++rt->sz;
        return rt;
    }
    bool dir = 0;
    if (key > rt->key) dir = 1;
    rt->son[dir] = insitem(rt->son[dir], key);
    rt->update();
    if (rt->son[dir]->val > rt->val) rt = rotate(rt, !dir);
    return rt;
}

node *delitem(node *rt, int key) {
    if (!rt) return rt;
    if (key < rt->key) {
        rt->son[0] = delitem(rt->son[0], key);
        rt->update();
        return rt;
    } else if (key > rt->key) {
        rt->son[1] = delitem(rt->son[1], key);
        rt->update();
        return rt;
    } else {
        if (rt->cnt > 1) {
            --rt->cnt;
            --rt->sz;
            return rt;
        } else if (!rt->son[0]) {
            node *tmp = rt->son[1];
            delete rt;
            return tmp;
        } else if (!rt->son[1]) {
            node *tmp = rt->son[0];
            delete rt;
            return tmp;
        } else {
            bool dir = 0;
            if (rt->son[!dir]->val > rt->son[dir]->val) dir ^= 1;
            rt = rotate(rt, !dir);
            rt->son[!dir] = delitem(rt->son[!dir], key);
            rt->update();
            return rt;
        }
    }
}

int getlesscnt(node *rt, int key) {
    if (!rt) return 0;
    int lsz = 0;
    if (rt->son[0]) lsz = rt->son[0]->sz;
    if (key < rt->key)
        return getlesscnt(rt->son[0], key);
    else if (key == rt->key)
        return lsz;
    else
        return lsz + rt->cnt + getlesscnt(rt->son[1], key);
}

int getnth(node *rt, int rank) {
    if (!rt) return -INF;
    int lsz = 0;
    if (rt->son[0]) lsz = rt->son[0]->sz;
    if (rank <= lsz)
        return getnth(rt->son[0], rank);
    else if (rank <= lsz + rt->cnt)
        return rt->key;
    else
        return getnth(rt->son[1], rank - lsz - rt->cnt);
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
        return pred(rt->son[0], key);
    else
        return max(rt->key, pred(rt->son[1], key));
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
        return succ(rt->son[1], key);
    else
        return min(rt->key, succ(rt->son[0], key));
}

int main() {
    int n;
    scanf("%d", &n);
    node *rt = NULL;
    for (int _ = 1; _ <= n; ++_) {
        char opt;
        int x;
        scanf("%hhd%d", &opt, &x);
        if (opt == 1)
            rt = insitem(rt, x);
        else if (opt == 2)
            rt = delitem(rt, x);
        else if (opt == 3)
            printf("%d\n", 1 + getlesscnt(rt, x));
        else if (opt == 4)
            printf("%d\n", getnth(rt, x));
        else if (opt == 5)
            printf("%d\n", pred(rt, x));
        else if (opt == 6)
            printf("%d\n", succ(rt, x));
    }
    destroy(rt);
    return 0;
}
