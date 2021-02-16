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

const int N = 200010, S = N * 90, inf = ~0U >> 1;
int seed = 19260817, n, rt[N], val[S], c[S][2], pri[S], sz[S], tot = 0;
bool rev[S];
long long s[S], lastans = 0;

inline int ran() { return seed = (seed * 1103515245LL + 12345LL) & inf; }

inline int mk(int v) {
  val[++tot] = v, pri[tot] = ran(), sz[tot] = 1, s[tot] = v;
  return tot;
}

inline int cp(int o) {
  val[++tot] = val[o], pri[tot] = pri[o], c[tot][0] = c[o][0],
  c[tot][1] = c[o][1], sz[tot] = sz[o], s[tot] = s[o], rev[tot] = rev[o];
  return tot;
}

inline void upd(int p) {
  sz[p] = 1 + sz[c[p][0]] + sz[c[p][1]],
  s[p] = val[p] + s[c[p][0]] + s[c[p][1]];
}

inline void push(int p) {
  if (!rev[p])
    return;
  swap(c[p][0], c[p][1]);
  if (c[p][0])
    c[p][0] = cp(c[p][0]), rev[c[p][0]] ^= 1;
  if (c[p][1])
    c[p][1] = cp(c[p][1]), rev[c[p][1]] ^= 1;
  rev[p] = 0;
}

void splt(int rt, int rk, int& l, int& r) {
  if (!rt) {
    l = r = 0;
    return;
  }
  rt = cp(rt), push(rt);
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
  if (pri[l] > pri[r]) {
    push(l), c[l][1] = mrg(c[l][1], r), upd(l);
    return l;
  } else {
    push(r), c[r][0] = mrg(l, c[r][0]), upd(r);
    return r;
  }
}

int main() {
  n = gi();
  for (int i = 1; i <= n; ++i) {
    int v = gi(), o = gi();
    if (o == 1) {
      int p = gi() ^ lastans, x = gi() ^ lastans;
      int t1, t2;
      splt(rt[v], p, t1, t2), rt[i] = mrg(mrg(t1, mk(x)), t2);
    } else if (o == 2) {
      int p = gi() ^ lastans;
      int t1, t2, t3;
      splt(rt[v], p, t1, t3), splt(t1, p - 1, t1, t2), rt[i] = mrg(t1, t3);
    } else if (o == 3) {
      int l = gi() ^ lastans, r = gi() ^ lastans;
      int t1, t2, t3;
      splt(rt[v], r, t1, t3), splt(t1, l - 1, t1, t2), rev[t2] ^= 1,
          rt[i] = mrg(mrg(t1, t2), t3);
    } else if (o == 4) {
      int l = gi() ^ lastans, r = gi() ^ lastans;
      int t1, t2, t3;
      splt(rt[v], r, t1, t3), splt(t1, l - 1, t1, t2), putln(lastans = s[t2]),
          rt[i] = rt[v];
    }
  }
  return 0;
}
