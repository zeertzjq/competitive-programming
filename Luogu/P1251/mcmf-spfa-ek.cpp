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

const int N = 4010, E = N * 12, inf = ~0U >> 1;
int n, s, t, e0[N], e1[E], to[E], w[E], c[E], ei = 0, dis[N], pre[N], q[N],
                                              head, tail;
bool inq[N];

inline int &qo(int &x) { return x == N ? x = 0 : x == -1 ? x = N - 1 : x; }

inline void mk(int u, int v, int w0, int c0) {
  ++ei;
  int i0 = ei << 1, i1 = ei << 1 | 1;
  e1[i0] = e0[u], e0[u] = i0, to[i0] = v, e1[i1] = e0[v], e0[v] = i1,
  to[i1] = u, w[i0] = w0, w[i1] = 0, c[i0] = c0, c[i1] = -c0;
}

inline bool spfa() {
  fill(dis + 1, dis + 1 + t, inf), dis[s] = 0, head = 1, tail = 0,
                                   q[++tail] = s, inq[s] = 1;
  while (head != tail + 1) {
    int u = q[head++];
    qo(head), inq[u] = 0;
    for (int e = e0[u]; e; e = e1[e]) {
      int v = to[e];
      if (!w[e])
        continue;
      int ndis = dis[u] + c[e];
      if (ndis < dis[v]) {
        dis[v] = ndis, pre[v] = e;
        if (!inq[v]) {
          if (ndis < dis[q[head]])
            q[qo(--head)] = v;
          else
            q[qo(++tail)] = v;
        }
      }
    }
  }
  return dis[t] != inf;
}

inline long long mcmf() {
  long long cost = 0;
  while (spfa()) {
    int f = inf;
    for (int u = t; u != s; u = to[pre[u] ^ 1])
      f = min(f, w[pre[u]]);
    for (int u = t; u != s; u = to[pre[u] ^ 1])
      w[pre[u]] -= f, w[pre[u] ^ 1] += f;
    cost += f * dis[t];
  }
  return cost;
}

int main() {
  n = gi(), s = 1, t = (n + 1) << 1;
  for (int i = 1; i < n; ++i)
    mk(i << 1 | 1, (i + 1) << 1 | 1, inf, 0);
  for (int i = 1; i <= n; ++i) {
    int r = gi();
    mk(i << 1, t, r, 0), mk(s, i << 1 | 1, r, 0);
  }
  int p0 = gi(), m0 = gi(), f0 = gi(), n0 = gi(), s0 = gi();
  for (int i = 1; i <= n; ++i) {
    mk(s, i << 1, inf, p0);
    if (i + m0 <= n)
      mk(i << 1 | 1, (i + m0) << 1, inf, f0);
    if (i + n0 <= n)
      mk(i << 1 | 1, (i + n0) << 1, inf, s0);
  }
  putln(mcmf());
  return 0;
}
