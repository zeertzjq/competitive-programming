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

const int N = 20010, E = N << 1;
int n, e0[N], e1[E], to[E], w[E], rt, rtmsz = N, tot, sz[N], dis[N], dcnt,
                                      vdis[N], vdcnt, ans[3];
bool vis[N];

inline int gcd(int a, int b) {
  int r;
  while (b)
    r = a % b, a = b, b = r;
  return a;
}

void grt(int u, int fa) {
  int msz = 0;
  sz[u] = 1;
  for (int e = e0[u]; e; e = e1[e]) {
    int v = to[e];
    if (v == fa || vis[v])
      continue;
    grt(v, u), msz = max(msz, sz[v]), sz[u] += sz[v];
  }
  msz = max(msz, tot - sz[u]);
  if (msz < rtmsz)
    rtmsz = msz, rt = u;
}

void gdis(int u, int fa, int d) {
  dis[++dcnt] = d;
  for (int e = e0[u]; e; e = e1[e]) {
    int v = to[e];
    if (v == fa || vis[v])
      continue;
    gdis(v, u, d + w[e]);
  }
}

inline void gans(int d) {
  for (int i = 1; i <= vdcnt; ++i)
    ans[(d + vdis[i]) % 3] += 2;
}

void solve(int u) {
  vis[u] = 1, vdis[vdcnt = 1] = 0, ++ans[0];
  for (int e = e0[u]; e; e = e1[e]) {
    int v = to[e];
    if (vis[v])
      continue;
    dcnt = 0, gdis(v, u, w[e]);
    for (int i = 1; i <= dcnt; ++i)
      gans(dis[i]);
    vdcnt = copy(dis + 1, dis + 1 + dcnt, vdis + 1 + vdcnt) - vdis - 1;
  }
  for (int e = e0[u]; e; e = e1[e]) {
    int v = to[e];
    if (vis[v])
      continue;
    rt = 0, rtmsz = N, tot = sz[v] < sz[u] ? sz[v] : sz[v] - sz[u], grt(v, 0),
    solve(rt);
  }
}

int main() {
  tot = n = gi();
  for (int i = 1; i < n; ++i) {
    int x = gi(), y = gi();
    w[i << 1] = w[i << 1 | 1] = gi(), e1[i << 1] = e0[x], e0[x] = i << 1,
           to[i << 1] = y, e1[i << 1 | 1] = e0[y], e0[y] = i << 1 | 1,
           to[i << 1 | 1] = x;
  }
  grt(1, 0), solve(rt);
  int a = ans[0], b = ans[0] + ans[1] + ans[2], d = gcd(a, b);
  puti(a / d), putchar('/'), putln(b / d);
  return 0;
}
