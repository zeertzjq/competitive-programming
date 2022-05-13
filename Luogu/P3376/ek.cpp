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

const int N = 10010, M = 200010, inf = ~0U >> 1;
int n, m, s, t, e0[N], e1[M], to[M], w[M], flow[N], pre[N], q[N], head, tail;

inline int bfs() {
  fill(pre + 1, pre + 1 + n, 0), head = 1, tail = 0, flow[s] = inf,
                                 q[++tail] = s;
  while (head <= tail) {
    int u = q[head++];
    for (int e = e0[u]; e; e = e1[e]) {
      int v = to[e];
      if (pre[v] || !w[e])
        continue;
      pre[v] = e, flow[v] = min(flow[u], w[e]);
      if (v == t)
        return flow[t];
      q[++tail] = v;
    }
  }
  return 0;
}

inline int ek() {
  int ans = 0;
  while (int f = bfs()) {
    for (int u = t; u != s; u = to[pre[u] ^ 1])
      w[pre[u]] -= f, w[pre[u] ^ 1] += f;
    ans += f;
  }
  return ans;
}

int main() {
  n = gi(), m = gi(), s = gi(), t = gi();
  for (int i = 1; i <= m; ++i) {
    int u = gi(), v = gi();
    e1[i << 1] = e0[u], e0[u] = i << 1, to[i << 1] = v, w[i << 1] = gi(),
            e1[i << 1 | 1] = e0[v], e0[v] = i << 1 | 1, to[i << 1 | 1] = u,
            w[i << 1 | 1] = 0;
  }
  putln(ek());
  return 0;
}
