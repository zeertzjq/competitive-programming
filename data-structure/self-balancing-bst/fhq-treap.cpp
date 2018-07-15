#include <bits/stdc++.h>
using namespace std;

const int INF = 2147483647;
int seed = 19260817;

int ran() {
    return seed = (seed * 1103515245LL + 12345LL) % 2147483648;
}

struct node {
    int key, val, sz;
    node *son[2];

    node(int k) {
        key = k;
        val = ran();
        sz = 1;
        son[0] = son[1] = NULL;
    }

    void update() {
        sz = 1;
        if (son[0]) sz += son[0]->sz;
        if (son[1]) sz += son[1]->sz;
    }

    int min() {
        node *cur = this;
        while (cur->son[0]) cur = cur->son[0];
        return cur->key;
    }

    int max() {
        node *cur = this;
        while (cur->son[1]) cur = cur->son[1];
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
        split(rt->son[1], key, rt->son[1], r);
    } else {
        r = rt;
        split(rt->son[0], key, l, rt->son[0]);
    }
    rt->update();
}

node *merge(node *l, node *r) {
    if (!l) return r;
    if (!r) return l;
    if (l->val > r->val) {
        l->son[1] = merge(l->son[1], r);
        l->update();
        return l;
    } else {
        r->son[0] = merge(l, r->son[0]);
        r->update();
        return r;
    }
}

void destroy(node *rt) {
    if (!rt) return;
    destroy(rt->son[0]);
    destroy(rt->son[1]);
    delete rt;
}

int getkth(node *rt, int rank) {
    int lsz = 0;
    if (rt->son[0]) lsz = rt->son[0]->sz;
    if (rank <= lsz)
        return getkth(rt->son[0], rank);
    else if (rank == lsz + 1)
        return rt->key;
    else
        return getkth(rt->son[1], rank - lsz - 1);
}

int main() {
    int n;
    scanf("%d", &n);
    node *rt = NULL;
    for (int _ = 1; _ <= n; ++_) {
        char opt;
        int x;
        scanf("%hhd%d", &opt, &x);
        if (opt == 1) {
            node *t1, *t2;
            split(rt, x, t1, t2);
            rt = merge(merge(t1, new node(x)), t2);
        } else if (opt == 2) {
            node *t1, *t2, *t3;
            split(rt, x, t1, t3);
            split(t1, x - 1, t1, t2);
            rt = merge(merge(t1, merge(t2->son[0], t2->son[1])), t3);
        } else if (opt == 3) {
            node *t1, *t2;
            split(rt, x - 1, t1, t2);
            printf("%d\n", t1 ? t1->sz + 1 : 1);
            rt = merge(t1, t2);
        } else if (opt == 4) {
            printf("%d\n", getkth(rt, x));
        } else if (opt == 5) {
            node *t1, *t2;
            split(rt, x - 1, t1, t2);
            printf("%d\n", t1->max());
            rt = merge(t1, t2);
        } else if (opt == 6) {
            node *t1, *t2;
            split(rt, x, t1, t2);
            printf("%d\n", t2->min());
            rt = merge(t1, t2);
        }
    }
    destroy(rt);
    return 0;
}
