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

template <typename T> inline void putsp(T x) {
  puti(x), putchar(' ');
}

template <typename T> inline void putln(T x) {
  puti(x), putchar('\n');
}
//}}}

const int N = 100010;
int n, m, val[N], sz[N], c[N][2], tot = 0;
bool rev[N];

inline int mk(int v) {
  val[++tot] = v, sz[tot] = 1, c[tot][0] = c[tot][1] = 0, rev[tot] = 0;
  return tot;
}

inline void upd(int p) {
  sz[p] = 1 + sz[c[p][0]] + sz[c[p][1]];
}

inline void push(int p) {
  if (!rev[p])
    return;
  rev[p] = 0;
  if (c[p][0])
    rev[c[p][0]] ^= 1;
  if (c[p][1])
    rev[c[p][1]] ^= 1;
  swap(c[p][0], c[p][1]);
}

int rot(int p, bool d) {
  push(p);
  int s = c[p][!d];
  if (!s)
    return p;
  push(s);
  int t = c[s][d];
  c[s][d] = p, c[p][!d] = t, upd(p), upd(s);
  return s;
}

int splay(int rt, int rk) {
  if (!rt)
    return rt;
  push(rt);
  int lsz = sz[c[rt][0]];
  if (rk == lsz + 1)
    return rt;
  else if (rk <= lsz) {
    push(c[rt][0]);
    int llsz = sz[c[c[rt][0]][0]];
    if (rk <= llsz)
      c[c[rt][0]][0] = splay(c[c[rt][0]][0], rk), rt = rot(rt, 1);
    else if (rk > llsz + 1)
      c[c[rt][0]][1] = splay(c[c[rt][0]][1], rk - llsz - 1),
      c[rt][0] = rot(c[rt][0], 0);
    rt = rot(rt, 1);
  } else {
    push(c[rt][1]);
    int rlsz = lsz + 1 + sz[c[c[rt][1]][0]];
    if (rk > rlsz + 1)
      c[c[rt][1]][1] = splay(c[c[rt][1]][1], rk - rlsz - 1), rt = rot(rt, 0);
    else if (rk <= rlsz)
      c[c[rt][1]][0] = splay(c[c[rt][1]][0], rk - lsz - 1),
      c[rt][1] = rot(c[rt][1], 1);
    rt = rot(rt, 0);
  }
  upd(rt);
  return rt;
}

int bld(int l, int r) {
  if (l > r)
    return 0;
  int m = (l + r) >> 1, rt = mk(m);
  c[rt][0] = bld(l, m - 1), c[rt][1] = bld(m + 1, r), upd(rt);
  return rt;
}

void inorder(int rt) {
  if (!rt)
    return;
  push(rt), inorder(c[rt][0]);
  if (val[rt] > 0 && val[rt] <= n)
    putsp(val[rt]);
  inorder(c[rt][1]);
}

int main() {
  n = gi(), m = gi();
  int rt = bld(0, n + 1);
  while (m--) {
    int l = gi(), r = gi();
    rt = splay(rt, r + 2), c[rt][0] = splay(c[rt][0], l),
    rev[c[c[rt][0]][1]] ^= 1;
  }
  inorder(rt), putchar('\n');
  return 0;
}
