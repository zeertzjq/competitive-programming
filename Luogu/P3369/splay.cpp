// vim: et sw=2 fdm=marker
#include <bits/stdc++.h>
using namespace std;

//{{{
inline int gi() {
  int x, f = 0;
  char c;
  while (!isdigit(c = getchar()))
    if (c == '-')
      f = 1;
  for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0')
    ;
  return f ? -x : x;
}

inline long long gll() {
  int f = 0;
  long long x;
  char c;
  while (!isdigit(c = getchar()))
    if (c == '-')
      f = 1;
  for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0')
    ;
  return f ? -x : x;
}

template <typename T> void puti(T x) {
  if (x < 0)
    putchar('-'), x = -x;
  if (x > 9)
    puti(x / 10);
  putchar(x % 10 + '0');
}

template <typename T> inline void putsp(T x) { puti(x), putchar(' '); }

template <typename T> inline void putln(T x) { puti(x), putchar('\n'); }
//}}}

const int N = 100010, inf = ~0U >> 1;
int key[N], cnt[N], sz[N], c[N][2], tot = 0;

inline int mk(int k) {
  key[++tot] = k, sz[tot] = cnt[tot] = 1, c[tot][0] = c[tot][1] = 0;
  return tot;
}

inline void upd(int p) { sz[p] = cnt[p] + sz[c[p][0]] + sz[c[p][1]]; }

inline int rot(int p, bool d) {
  int s = c[p][!d];
  if (!s)
    return p;
  int t = c[s][d];
  c[s][d] = p, c[p][!d] = t, upd(p), upd(s);
  return s;
}

int splay(int rt, int k) {
  if (!rt || k == key[rt])
    return rt;
  if (k < key[rt]) {
    if (!c[rt][0])
      return rt;
    if (k < key[c[rt][0]])
      c[c[rt][0]][0] = splay(c[c[rt][0]][0], k), rt = rot(rt, 1);
    else if (k > key[c[rt][0]])
      c[c[rt][0]][1] = splay(c[c[rt][0]][1], k), c[rt][0] = rot(c[rt][0], 0);
    rt = rot(rt, 1);
  } else {
    if (!c[rt][1])
      return rt;
    if (k > key[c[rt][1]])
      c[c[rt][1]][1] = splay(c[c[rt][1]][1], k), rt = rot(rt, 0);
    else if (k < key[c[rt][1]])
      c[c[rt][1]][0] = splay(c[c[rt][1]][0], k), c[rt][1] = rot(c[rt][1], 1);
    rt = rot(rt, 0);
  }
  return rt;
}

int insitem(int rt, int k) {
  if (!rt)
    return mk(k);
  rt = splay(rt, k);
  if (k == key[rt]) {
    ++cnt[rt], ++sz[rt];
    return rt;
  } else if (key[rt] < k) {
    int nrt = mk(k);
    c[nrt][0] = rt, c[nrt][1] = c[rt][1], c[rt][1] = 0, upd(rt), upd(nrt);
    return nrt;
  } else {
    int nrt = mk(k);
    c[nrt][1] = rt, c[nrt][0] = c[rt][0], c[rt][0] = 0, upd(rt), upd(nrt);
    return nrt;
  }
}

int delitem(int rt, int k) {
  if (!rt)
    return rt;
  rt = splay(rt, k);
  if (k != key[rt])
    return rt;
  if (cnt[rt] > 1) {
    --cnt[rt], --sz[rt];
    return rt;
  } else {
    int nrt = c[rt][0];
    if (!nrt)
      nrt = c[rt][1];
    else
      nrt = splay(nrt, k), c[nrt][1] = c[rt][1], upd(nrt);
    return nrt;
  }
}

int getkth(int rt, int rk) {
  if (!rt)
    return inf;
  int lsz = sz[c[rt][0]];
  if (rk <= lsz)
    return getkth(c[rt][0], rk);
  else if (rk <= lsz + cnt[rt])
    return key[rt];
  else
    return getkth(c[rt][1], rk - lsz - cnt[rt]);
}

int main() {
  int _ = gi(), rt = 0;
  while (_--) {
    int opt = gi(), x = gi();
    if (opt == 1)
      rt = insitem(rt, x);
    else if (opt == 2)
      rt = delitem(rt, x);
    else if (opt == 3) {
      rt = splay(rt, x);
      int lsz = sz[c[rt][0]];
      putln(lsz + 1);
    } else if (opt == 4)
      putln(getkth(rt, x));
    else if (opt == 5) {
      rt = splay(rt, x);
      int res = rt;
      if (key[res] >= x)
        res = c[rt][0] = splay(c[rt][0], x);
      putln(key[res]);
    } else if (opt == 6) {
      rt = splay(rt, x);
      int res = rt;
      if (key[res] <= x)
        res = c[rt][1] = splay(c[rt][1], x);
      putln(key[res]);
    }
  }
}
