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
int seed = 19260817, key[N], pri[N], sz[N], c[N][2], tot = 0;

inline int ran() { return seed = (seed * 1103515245LL + 12345LL) & inf; }

inline int mk(int k) {
  key[++tot] = k, pri[tot] = ran(), sz[tot] = 1, c[tot][0] = c[tot][1] = 0;
  return tot;
}

inline void upd(int p) { sz[p] = 1 + sz[c[p][0]] + sz[c[p][1]]; }

inline int tmin(int rt) {
  while (c[rt][0])
    rt = c[rt][0];
  return key[rt];
}

inline int tmax(int rt) {
  while (c[rt][1])
    rt = c[rt][1];
  return key[rt];
}

void splt(int rt, int k, int & l, int & r) {
  if (!rt) {
    l = r = 0;
    return;
  }
  if (key[rt] <= k)
    l = rt, splt(c[rt][1], k, c[rt][1], r);
  else
    r = rt, splt(c[rt][0], k, l, c[rt][0]);
  upd(rt);
}

int mrg(int l, int r) {
  if (!l || !r)
    return l | r;
  if (pri[l] > pri[r]) {
    c[l][1] = mrg(c[l][1], r), upd(l);
    return l;
  } else {
    c[r][0] = mrg(l, c[r][0]), upd(r);
    return r;
  }
}

int getkth(int rt, int rk) {
  int lsz = sz[c[rt][0]];
  if (rk <= lsz)
    return getkth(c[rt][0], rk);
  else if (rk == lsz + 1)
    return key[rt];
  else
    return getkth(c[rt][1], rk - lsz - 1);
}

int main() {
  int _ = gi(), rt = 0;
  while (_--) {
    int opt = gi(), x = gi();
    if (opt == 1) {
      int t1, t2;
      splt(rt, x, t1, t2), rt = mrg(mrg(t1, mk(x)), t2);
    } else if (opt == 2) {
      int t1, t2, t3;
      splt(rt, x, t1, t3), splt(t1, x - 1, t1, t2),
          rt = mrg(mrg(t1, mrg(c[t2][0], c[t2][1])), t3);
    } else if (opt == 3) {
      int t1, t2;
      splt(rt, x - 1, t1, t2), putln(t1 ? sz[t1] + 1 : 1), rt = mrg(t1, t2);
    } else if (opt == 4) {
      putln(getkth(rt, x));
    } else if (opt == 5) {
      int t1, t2;
      splt(rt, x - 1, t1, t2), putln(tmax(t1)), rt = mrg(t1, t2);
    } else if (opt == 6) {
      int t1, t2;
      splt(rt, x, t1, t2), putln(tmin(t2)), rt = mrg(t1, t2);
    }
  }
  return 0;
}
