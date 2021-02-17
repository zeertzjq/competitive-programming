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

const int N = 200010, S = N * 36;
int n, m, rt[N], lc[S], rc[S], fa[S], rk[S], tot = 0;

inline int mk(int f, int k, int l, int r) {
  fa[++tot] = f, rk[tot] = k, lc[tot] = l, rc[tot] = r;
  return tot;
}

int bld(int l, int r) {
  if (l == r)
    return mk(l, 0, 0, 0);
  int m = (l + r) >> 1;
  return mk(0, 0, bld(l, m), bld(m + 1, r));
}

int upd(int rt, int l, int r, int x, int f) {
  if (x < l || x > r)
    return rt;
  if (l == r)
    return mk(f, rk[rt], 0, 0);
  int m = (l + r) >> 1;
  return mk(0, 0, upd(lc[rt], l, m, x, f), upd(rc[rt], m + 1, r, x, f));
}

int add(int rt, int l, int r, int x) {
  if (x < l || x > r)
    return rt;
  if (l == r)
    return mk(fa[rt], rk[rt] + 1, 0, 0);
  int m = (l + r) >> 1;
  return mk(0, 0, add(lc[rt], l, m, x), add(rc[rt], m + 1, r, x));
}

int nqry(int rt, int l, int r, int x) {
  if (l == r)
    return rt;
  int m = (l + r) >> 1;
  return x <= m ? nqry(lc[rt], l, m, x) : nqry(rc[rt], m + 1, r, x);
}

int finds(int rt, int x) {
  int nf = nqry(rt, 1, n, x);
  return fa[nf] == x ? nf : finds(rt, fa[nf]);
}

int main() {
  n = gi(), m = gi(), rt[0] = bld(1, n);
  for (int i = 1; i <= m; ++i) {
    int o = gi();
    if (o == 1) {
      int na = finds(rt[i - 1], gi()), nb = finds(rt[i - 1], gi());
      if (fa[na] == fa[nb]) {
        rt[i] = rt[i - 1];
        continue;
      }
      if (rk[na] < rk[nb])
        swap(na, nb);
      rt[i] = upd(rt[i - 1], 1, n, fa[nb], fa[na]);
      if (rk[na] == rk[nb])
        rt[i] = add(rt[i], 1, n, fa[na]);
    } else if (o == 3)
      rt[i] = rt[i - 1],
      puts(fa[finds(rt[i], gi())] == fa[finds(rt[i], gi())] ? "1" : "0");
    else
      rt[i] = rt[gi()];
  }
  return 0;
}
