// https://www.luogu.org/problemnew/show/P3391
#include <bits/stdc++.h>
using namespace std;

const int INF = 2147483647;
int n;

int geti() {
    int x, f = 0;
    char c;
    while (!isdigit(c = getchar()))
        if (c == '-') f = 1;
    for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0')
        ;
    return f ? -x : x;
}

void puti(int x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) puti(x / 10);
    putchar(x % 10 + '0');
}

struct node {
    int val, sz;
    node *son[2];
    bool tag;

    node(int v) {
        val = v;
        sz = 1;
        tag = 0;
        son[0] = son[1] = NULL;
    }

    void update() {
        sz = 1;
        if (son[0]) sz += son[0]->sz;
        if (son[1]) sz += son[1]->sz;
    }

    void rev() {
        if (!tag) return;
        tag = 0;
        if (son[0]) son[0]->tag ^= 1;
        if (son[1]) son[1]->tag ^= 1;
        swap(son[0], son[1]);
    }
};

node *rotate(node *p, bool dir) {
    p->rev();
    node *s = p->son[!dir];
    s->rev();
    node *t = s->son[dir];
    s->son[dir] = p;
    p->son[!dir] = t;
    p->update();
    s->update();
    return s;
}

node *splaykth(node *rt, int rank) {
    if (!rt) return rt;
    rt->rev();
    int lsz = rt->son[0] ? rt->son[0]->sz : 0;
    if (rank == lsz + 1)
        return rt;
    else if (rank <= lsz) {
        // IMPORTANT: DON'T use node *s = rt->son[0]
        rt->son[0]->rev();
        int llsz = rt->son[0]->son[0] ? rt->son[0]->son[0]->sz : 0;
        if (rank <= llsz) {
            rt->son[0]->son[0] = splaykth(rt->son[0]->son[0], rank);
            rt = rotate(rt, 1);
        } else if (rank > llsz + 1) {
            rt->son[0]->son[1] = splaykth(rt->son[0]->son[1], rank - llsz - 1);
            rt->son[0] = rotate(rt->son[0], 0);
        }
        if (rt->son[0]) rt = rotate(rt, 1);
    } else {
        // IMPORTANT: DON'T use node *s = rt->son[1]
        rt->son[1]->rev();
        int rlsz = rt->son[1]->son[0] ? lsz + 1 + rt->son[1]->son[0]->sz : lsz + 1;
        if (rank > rlsz + 1) {
            rt->son[1]->son[1] = splaykth(rt->son[1]->son[1], rank - rlsz - 1);
            rt = rotate(rt, 0);
        } else if (rank <= rlsz) {
            rt->son[1]->son[0] = splaykth(rt->son[1]->son[0], rank - lsz - 1);
            rt->son[1] = rotate(rt->son[1], 1);
        }
        if (rt->son[1]) rt = rotate(rt, 0);
    }
    rt->update();
    return rt;
}

node *build(int l, int r) {
    if (l > r) return NULL;
    int m = (l + r) >> 1;
    node *rt = new node(m);
    rt->son[0] = l < m ? build(l, m - 1) : NULL;
    rt->son[1] = m < r ? build(m + 1, r) : NULL;
    rt->update();
    return rt;
}

void destroy(node *rt) {
    if (!rt) return;
    destroy(rt->son[0]);
    destroy(rt->son[1]);
    delete rt;
}

void inorder(node *rt) {
    if (!rt) return;
    rt->rev();
    inorder(rt->son[0]);
    if (rt->val > 0 && rt->val <= n) {
        puti(rt->val);
        putchar(' ');
    }
    inorder(rt->son[1]);
}

int main() {
    n = geti();
    int m = geti();
    node *rt = build(0, n + 1);
    while (m--) {
        int l = geti(), r = geti();
        rt = splaykth(rt, l);
        int lsz = rt->son[0] ? rt->son[0]->sz : 0;
        rt->son[1] = splaykth(rt->son[1], r + 2 - lsz - 1);
        rt->son[1]->son[0]->tag ^= 1;
    }
    inorder(rt);
    destroy(rt);
    return 0;
}
