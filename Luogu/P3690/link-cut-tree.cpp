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

const int N = 300010;
int n, m;
int f[N], c[N][2], s[N], v[N];
bool r[N];

inline void upd(int x) {
  s[x] = v[x] ^ s[c[x][0]] ^ s[c[x][1]];
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

inline void mkrt(int x) {
  access(x), splay(x), r[x] ^= 1;
}

inline int frt(int x) {
  access(x), splay(x);
  while (push(x), c[x][0])
    x = c[x][0];
  return x;
}

inline void link(int x, int y) {
  mkrt(x), splay(x);
  if (frt(y) == x)
    return;
  f[x] = y;
}

inline void cut(int x, int y) {
  mkrt(x), access(y), splay(y), push(y);
  if (c[y][0] != x || c[x][1] || frt(y) != x)
    return;
  f[x] = c[y][0] = 0, upd(y);
}

int main() {
  n = gi(), m = gi();
  for (int i = 1; i <= n; ++i)
    v[i] = s[i] = gi();
  while (m--) {
    int opt = gi(), x = gi(), y = gi();
    if (opt == 0)
      mkrt(x), access(y), splay(y), putln(s[y]);
    else if (opt == 1)
      link(x, y);
    else if (opt == 2)
      cut(x, y);
    else
      splay(x), v[x] = y, upd(x);
  }
  return 0;
}
