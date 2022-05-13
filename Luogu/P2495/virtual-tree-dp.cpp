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

const int N = 250010, E = N << 1, inf = ~0U >> 1;
int n, e0[N], e1[E], to[E], w[E], anc[N][20], amc[N][20], dep[N], dfn[N],
    disc = 0, h[N], s[N], top, pmc, ecnt;
bool ih[N];

inline void mk(int u, int v, int w0) {
  e1[++ecnt] = e0[u], e0[u] = ecnt, to[ecnt] = v, w[ecnt] = w0;
}

inline int log2(int x) {
  int ans = 0;
  while (x >>= 1)
    ++ans;
  return ans;
}

void init(int u) {
  dfn[u] = ++disc;
  int log2d = log2(dep[u]);
  for (int i = 1; i <= log2d; ++i)
    anc[u][i] = anc[anc[u][i - 1]][i - 1],
    amc[u][i] = min(amc[u][i - 1], amc[anc[u][i - 1]][i - 1]);
  for (int e = e0[u]; e; e = e1[e]) {
    int v = to[e];
    if (v == anc[u][0])
      continue;
    anc[v][0] = u, amc[v][0] = w[e], dep[v] = dep[u] + 1, init(v);
  }
}

inline int lca(int x, int y) {
  pmc = inf;
  if (dep[x] < dep[y])
    swap(x, y);
  while (dep[x] > dep[y]) {
    int d = log2(dep[x] - dep[y]);
    pmc = min(pmc, amc[x][d]);
    x = anc[x][d];
  }
  if (x == y)
    return x;
  for (int d = log2(dep[x]); d >= 0; --d)
    if (anc[x][d] != anc[y][d])
      pmc = min(pmc, min(amc[x][d], amc[y][d])), x = anc[x][d], y = anc[y][d];
  return anc[x][0];
}

inline bool cmp(int a, int b) {
  return dfn[a] < dfn[b];
}

long long dfs(int u) {
  long long ans = 0;
  for (int e = e0[u]; e; e = e1[e]) {
    int v = to[e];
    ans += ih[v] ? w[e] : min(dfs(v), 1LL * w[e]);
  }
  return ans;
}

int main() {
  n = gi();
  for (int i = 1; i < n; ++i) {
    int u = gi(), v = gi(), i0 = i << 1, i1 = i << 1 | 1;
    w[i0] = w[i1] = gi(), e1[i0] = e0[u], e0[u] = i0, to[i0] = v,
    e1[i1] = e0[v], e0[v] = i1, to[i1] = u;
  }
  init(1);
  int m = gi();
  while (m--) {
    int k = gi();
    fill(ih + 1, ih + 1 + n, 0);
    for (int i = 1; i <= k; ++i)
      h[i] = gi(), ih[h[i]] = 1;
    sort(h + 1, h + 1 + k, cmp), e0[1] = 0, s[top = 1] = 1, ecnt = 0;
    for (int i = 1; i <= k; ++i)
      if (h[i] != 1) {
        int a = lca(s[top], h[i]);
        if (a != s[top]) {
          while (dfn[s[top - 1]] > dfn[a])
            lca(s[top - 1], s[top]), mk(s[top - 1], s[top], pmc), --top;
          if (dfn[s[top - 1]] < dfn[a])
            e0[a] = 0, lca(a, s[top]), mk(a, s[top], pmc), s[top] = a;
          else
            lca(a, s[top]), mk(a, s[top], pmc), --top;
        }
        e0[h[i]] = 0, s[++top] = h[i];
      }
    for (; top > 1; top--)
      lca(s[top - 1], s[top]), mk(s[top - 1], s[top], pmc);
    putln(dfs(1));
  }
  return 0;
}
