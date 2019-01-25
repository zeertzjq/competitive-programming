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

struct node {
    int key, cnt, sz;
    bool red;
    node *c[2], *dad;

    node(int k, node *p) {
        key = k;
        cnt = sz = 1;
        c[0] = c[1] = NULL;
        red = 1;
        dad = p;
    }

    inline bool sdir(node *s) {
        return c[1] == s;
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

node *rt = NULL;

inline void rotate(node *p, bool dir) {
    node *dad = p->dad;
    node *s = p->c[!dir], *t = s->c[dir];
    if (dad) dad->c[dad->sdir(p)] = s;
    s->c[dir] = p;
    p->c[!dir] = t;
    s->dad = dad;
    p->dad = s;
    if (t) t->dad = p;
    p->update();
    s->update();
}

bool vired = 0, viblack = 0, vidir;
node *vicur, *vidad;

inline void svired(node *cur) {
    vired = 1;
    vicur = cur;
}

inline void sviblack(node *dad, bool pdir) {
    viblack = 1;
    vidad = dad;
    vidir = pdir;
}

void vred(node *cur) {
    vired = 0;
    if (!cur->red) return;
    node *p = cur->dad;
    if (!p) {
        cur->red = 0;
        return;
    }
    if (!p->red) return;
    node *gp = p->dad;
    bool pdir = p->sdir(cur), gpdir = gp->sdir(p);
    node *u = gp->c[!gpdir];
    if (!u || !u->red) {
        if (pdir != gpdir) {
            rotate(p, gpdir);
            swap(cur, p);
        };
        rotate(gp, !gpdir);
        if (gp == rt) rt = gp->dad;
        p->red = 0;
        gp->red = 1;
    } else {
        p->red = u->red = 0;
        gp->red = 1;
        vred(gp);
    }
}

void vblack(node *dad, bool pdir) {
    viblack = 0;
    if (!dad) return;
    node *sib = dad->c[!pdir];
    if (sib->red) {
        rotate(dad, pdir);
        if (rt == dad) rt = dad->dad;
        sib = dad->c[!pdir];
        dad->red = 1;
        dad->dad->red = 0;
    }
    bool rot1 = sib->c[!pdir] ? sib->c[!pdir]->red : 0;
    bool rot2 = sib->c[pdir] ? sib->c[pdir]->red : 0;
    if (!rot1 && !rot2) {
        sib->red = 1;
        if (dad->red)
            dad->red = 0;
        else if (dad->dad)
            vblack(dad->dad, dad->dad->sdir(dad));
    } else {
        if (!rot1) {
            rotate(sib, !pdir);
            sib = sib->dad;
        }
        rotate(dad, pdir);
        if (rt == dad) rt = dad->dad;
        sib->red = dad->red;
        sib->c[!pdir]->red = dad->red = 0;
    }
}

node *insitem(node *rt, node *dad, int key) {
    if (!rt) {
        rt = new node(key, dad);
        if (!dad)
            rt->red = 0;
        else if (dad->red)
            svired(rt);
        return rt;
    }
    if (rt->key == key) {
        ++rt->cnt;
        ++rt->sz;
        return rt;
    }
    bool dir = 0;
    if (key > rt->key) dir = 1;
    rt->c[dir] = insitem(rt->c[dir], rt, key);
    rt->update();
    return rt;
}

node *delitem(node *rt, node *dad, int key) {
    if (!rt) return rt;
    if (rt->key == key) {
        if (rt->cnt > 1) {
            --rt->cnt;
            --rt->sz;
            return rt;
        } else if (!rt->c[0] || !rt->c[1]) {
            bool ndir = rt->sdir(NULL);
            node *np = rt->c[!ndir];
            node *ort = rt;
            rt = np;
            if (np) np->dad = dad;
            if (np && np->red)
                np->red = 0;
            else if (dad && !ort->red)
                sviblack(dad, dad->sdir(ort));
            delete ort;
            return rt;
        } else {
            node *succ = rt->stsucc();
            key = rt->key = succ->key;
            swap(rt->cnt, succ->cnt);
        }
    }
    bool dir = 1;
    if (key < rt->key) dir = 0;
    rt->c[dir] = delitem(rt->c[dir], rt, key);
    rt->update();
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

void destroy(node *rt) {
    if (!rt) return;
    destroy(rt->c[0]);
    destroy(rt->c[1]);
    delete rt;
}

int main() {
    int _ = gi();
    while (_--) {
        int opt = gi(), x = gi();
        if (opt == 1) {
            rt = insitem(rt, NULL, x);
            if (vired) vred(vicur);
        } else if (opt == 2) {
            rt = delitem(rt, NULL, x);
            if (viblack) vblack(vidad, vidir);
        } else if (opt == 3)
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
