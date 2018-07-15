#include <bits/stdc++.h>
using namespace std;

const int INF = 2147483647;

struct node {
    int key, cnt, sz;
    bool red;
    node *son[2], *dad;

    node(int k, node *p) {
        key = k;
        cnt = sz = 1;
        son[0] = son[1] = NULL;
        red = true;
        dad = p;
    }

    bool sdir(node *s) {
        return son[0] == s ? 0 : 1;
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

void rotate(node *p, bool dir) {
    node *dad = p->dad;
    node *s = p->son[!dir], *t = s->son[dir];
    if (dad) dad->son[dad->sdir(p)] = s;
    s->son[dir] = p;
    p->son[!dir] = t;
    s->dad = dad;
    p->dad = s;
    if (t) t->dad = p;
    p->update();
    s->update();
}

void vred(node *cur) {
    if (!cur->red) return;
    node *p = cur->dad;
    if (!p) {
        cur->red = false;
        return;
    }
    if (!p->red) return;
    node *gp = p->dad;
    bool pdir = p->sdir(cur), gpdir = gp->sdir(p);
    node *u = gp->son[!gpdir];
    if (!u || !u->red) {
        if (pdir != gpdir) rotate(p, gpdir);
        rotate(gp, !gpdir);
        p->red = false;
        gp->red = true;
    } else {
        p->red = u->red = false;
        gp->red = true;
        vred(gp);
    }
}

void vblack(node *dad, bool pdir) {
    if (!dad) return;
    node *sib = dad->son[!pdir];
    if (sib->red) {
        rotate(dad, pdir);
        sib = dad->son[!pdir];
    }
    bool rot1 = sib->son[!pdir]->red;
    bool rot2 = sib->son[pdir]->red;
    if (!rot1 && !rot2) {
        sib->red = true;
        if (dad->red)
            dad->red = false;
        else if (dad->dad)
            vblack(dad->dad, dad->dad->sdir(dad));
    } else {
        if (!rot1) {
            rotate(sib, !pdir);
            sib = sib->dad;
        }
        rotate(dad, pdir);
        sib->red = dad->red;
        sib->son[!pdir]->red = dad->red = false;
    }
}

void insitem(node *&rt, node *dad, int key) {
    if (!rt) {
        rt = new node(key, dad);
        if (!dad)
            rt->red = false;
        else if (dad->red)
            vred(rt);
        return;
    }
    if (rt->key == key) {
        ++rt->cnt;
        ++rt->sz;
        return;
    }
    bool dir = 0;
    if (key > rt->key) dir = 1;
    insitem(rt->son[dir], rt, key);
    rt->update();
}

void delitem(node *&rt, node *dad, int key) {
    if (!rt) return;
    if (rt->key == key) {
        if (rt->cnt > 1) {
            --rt->cnt;
            --rt->sz;
            return;
        } else if (!rt->son[0] || !rt->son[1]) {
            bool ndir = rt->sdir(NULL);
            node *np = rt->son[!ndir];
            node *ort = rt;
            rt = np;
            if (np) np->dad = dad;
            if (np && np->red)
                np->red = false;
            else if (dad && !ort->red)
                vblack(dad, dad->sdir(np));
            delete ort;
            return;
        } else {
            node *succ = rt->stsucc();
            key = rt->key = succ->key;
            swap(rt->cnt, succ->cnt);
        }
    }
    bool dir = 1;
    if (key < rt->key) dir = 0;
    delitem(rt->son[dir], rt, key);
    rt->update();
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
            insitem(rt, NULL, x);
        else if (opt == 2)
            delitem(rt, NULL, x);
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
