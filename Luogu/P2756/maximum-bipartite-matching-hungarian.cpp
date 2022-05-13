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

const int N = 1010;
int m, n, xm[N], ym[N], ans = 0, vis[N];
bool g[N][N];

bool dfs(int x) {
  for (int y = 1; y <= n; ++y)
    if (g[x][y] && !vis[y]) {
      vis[y] = 1;
      if (!ym[y] || dfs(ym[y])) {
        xm[x] = y, ym[y] = x;
        return 1;
      }
    }
  return 0;
}

int main() {
  m = gi(), n = gi();
  for (int i = gi(), j = gi(); ~i && ~j; i = gi(), j = gi())
    g[i][j - m] = 1;
  for (int i = 1; i <= m; ++i)
    fill(vis + 1, vis + 1 + n, 0), ans += dfs(i);
  putln(ans);
  for (int i = 1; i <= m; ++i)
    if (xm[i])
      putsp(i), putln(xm[i] + m);
  return 0;
}
