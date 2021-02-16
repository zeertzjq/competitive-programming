// vim: et sw=2 sts=2 fdm=marker
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

const int N = 100010;
int n, m, val[N], pri[N], sz[N], c[N][2], tot = 0;
bool rev[N];

inline int mk(int v, int p) {
  val[++tot] = v, pri[tot] = p, sz[tot] = 1, c[tot][0] = c[tot][1] = 0,
  rev[tot] = 0;
  return tot;
}

inline void upd(int p) { sz[p] = 1 + sz[c[p][0]] + sz[c[p][1]]; }

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

void splt(int rt, int rk, int &l, int &r) {
  if (!rt) {
    l = r = 0;
    return;
  }
  push(rt);
  int lsz = sz[c[rt][0]];
  if (rk <= lsz)
    r = rt, splt(c[rt][0], rk, l, c[rt][0]);
  else
    l = rt, splt(c[rt][1], rk - lsz - 1, c[rt][1], r);
  upd(rt);
}

int mrg(int l, int r) {
  if (!l || !r)
    return l | r;
  if (pri[l] < pri[r]) {
    push(l), c[l][1] = mrg(c[l][1], r), upd(l);
    return l;
  } else {
    push(r), c[r][0] = mrg(l, c[r][0]), upd(r);
    return r;
  }
}

int bld(int l, int r, int d) {
  if (l > r)
    return 0;
  int m = (l + r) >> 1, rt = mk(m, d);
  c[rt][0] = bld(l, m - 1, d + 1), c[rt][1] = bld(m + 1, r, d + 1), upd(rt);
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
  int rt = bld(1, n, 1);
  while (m--) {
    int l = gi(), r = gi(), t1, t2, t3;
    splt(rt, r, t1, t3), splt(t1, l - 1, t1, t2), rev[t2] ^= 1,
        rt = mrg(mrg(t1, t2), t3);
  }
  inorder(rt), putchar('\n');
  return 0;
}
