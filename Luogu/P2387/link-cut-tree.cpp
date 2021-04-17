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

const int N = 50010, M = 100010, inf = ~0U >> 1;
int n, m, ans = inf, f[N + M], c[N + M][2], b[N + M], mx[N + M], uf[N + M];
bool r[N + M];

struct edge {
  int x, y, a, b;

  inline bool operator<(const edge & rhs) const { return a < rhs.a; }
} e[M];

int finds(int x) { return uf[x] == x ? x : uf[x] = finds(uf[x]); }

inline void upd(int x) {
  mx[x] = x;
  if (b[mx[c[x][0]]] > b[mx[x]])
    mx[x] = mx[c[x][0]];
  if (b[mx[c[x][1]]] > b[mx[x]])
    mx[x] = mx[c[x][1]];
}

inline void push(int x) {
  if (!x || !r[x])
    return;
  r[x] = 0;
  if (c[x][0])
    r[c[x][0]] ^= 1;
  if (c[x][1])
    r[c[x][1]] ^= 1;
  swap(c[x][0], c[x][1]);
}

inline bool isrt(int x) {
  return !f[x] || (c[f[x]][0] != x && c[f[x]][1] != x);
}

inline int rot(int p, bool d) {
  push(p);
  int s = c[p][!d];
  if (!s)
    return p;
  push(s);
  int t = c[s][d];
  c[s][d] = p, c[p][!d] = t, f[s] = f[p], f[p] = s, f[t] = p, upd(p), upd(s);
  return s;
}

inline void splay(int x) {
  while (!isrt(x)) {
    int p = f[x], gp = f[p];
    push(gp), push(p);
    bool pd = c[p][1] == x;
    if (isrt(p))
      rot(p, !pd);
    else {
      int ggp = f[gp];
      bool gpd = c[gp][1] == p, gprt = isrt(gp), ggpd = gprt || c[ggp][1] == gp;
      if (pd != gpd)
        c[gp][gpd] = rot(p, !pd);
      else
        gp = rot(gp, !gpd);
      gp = rot(gp, !gpd);
      if (!gprt)
        c[ggp][ggpd] = gp;
    }
  }
}

inline void access(int x) {
  for (int s = 0; x; s = x, x = f[x])
    splay(x), push(x), c[x][1] = s, upd(x);
}

inline void mkrt(int x) { access(x), splay(x), r[x] ^= 1; }

inline void link(int x, int y) { mkrt(x), splay(x), f[x] = y; }

inline void cut(int x, int y) {
  mkrt(x), access(y), splay(y), push(y), f[x] = c[y][0] = 0, upd(y);
}

inline int pmx(int x, int y) {
  mkrt(x), access(y), splay(y);
  return mx[y];
}

int main() {
  n = gi(), m = gi();
  for (int i = 1; i <= m; ++i)
    e[i].x = gi(), e[i].y = gi(), e[i].a = gi(), e[i].b = gi();
  sort(e + 1, e + 1 + m);
  for (int i = 1; i <= n + m; ++i)
    uf[i] = mx[i] = i;
  for (int i = 1; i <= m; ++i)
    b[n + i] = e[i].b;
  for (int i = 1; i <= m; ++i) {
    int u = e[i].x, v = e[i].y, ur = finds(u), vr = finds(v);
    bool f = 1;
    if (ur == vr) {
      int mxe = pmx(u, v);
      if (b[mxe] > e[i].b)
        cut(e[mxe - n].x, mxe), cut(mxe, e[mxe - n].y);
      else
        f = 0;
    } else
      uf[vr] = ur;
    if (f)
      link(u, i + n), link(i + n, v);
    if (finds(1) == finds(n))
      ans = min(ans, e[i].a + b[pmx(1, n)]);
  }
  putln(ans == inf ? -1 : ans);
  return 0;
}
