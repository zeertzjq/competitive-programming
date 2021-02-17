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

const int N = 5010, M = 200010, inf = ~0U >> 1;
int n, m, e0[N], e1[M << 1], to[M << 1], z[M << 1], dis[N], len = 0, vcnt = 0,
                                                            hsz = 0;
struct hitm {
  int d, u;

  inline bool operator<(const hitm& rhs) const { return d > rhs.d; }
} h[M];
bool vis[N];

void prim() {
  fill(dis + 1, dis + 1 + n, inf), dis[1] = 0, h[hsz++] = {0, 1},
                                   push_heap(h, h + hsz);
  while (hsz) {
    pop_heap(h, h + hsz--);
    int u = h[hsz].u;
    if (vis[u])
      continue;
    vis[u] = 1, len += dis[u], ++vcnt;
    if (vcnt == n)
      return;
    for (int e = e0[u]; e; e = e1[e]) {
      int v = to[e];
      if (z[e] < dis[v])
        dis[v] = z[e], h[hsz++] = {dis[v], v}, push_heap(h, h + hsz);
    }
  }
}

int main() {
  n = gi(), m = gi();
  for (int i = 1; i <= m; ++i) {
    int x = gi(), y = gi();
    z[i << 1] = z[i << 1 | 1] = gi(), e1[i << 1] = e0[x], e0[x] = i << 1,
           to[i << 1] = y, e1[i << 1 | 1] = e0[y], e0[y] = i << 1 | 1,
           to[i << 1 | 1] = x;
  }
  prim();
  if (vcnt == n)
    putln(len);
  else
    puts("orz");
  return 0;
}
