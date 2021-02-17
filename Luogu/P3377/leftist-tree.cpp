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

const int N = 100010;

int n, m, dis[N], p[N], c[N][2], v[N];

int finds(int x) { return p[x] == x ? x : p[x] = finds(p[x]); }

int mrg(int l, int r) {
  if (!l || !r)
    return l | r;
  if (l == r)
    return l;
  if (v[l] > v[r] || (v[l] == v[r] && l > r))
    swap(l, r);
  p[r] = l, c[l][1] = mrg(c[l][1], r);
  if (dis[c[l][0]] > dis[c[l][1]])
    swap(c[l][0], c[l][1]);
  dis[l] = dis[c[l][1]] + 1;
  return l;
}

int main() {
  n = gi(), m = gi();
  for (int i = 1; i <= n; ++i)
    v[i] = gi(), p[i] = i;
  dis[0] = -1;
  while (m--) {
    int op = gi();
    if (op == 1) {
      int x = gi(), y = gi();
      if (v[x] && v[y])
        mrg(finds(x), finds(y));
    } else {
      int x = gi();
      if (!v[x]) {
        puts("-1");
        continue;
      } else {
        int rt = finds(x);
        putln(v[rt]), v[rt] = 0, p[c[rt][0]] = c[rt][0], p[c[rt][1]] = c[rt][1],
                      p[rt] = mrg(c[rt][0], c[rt][1]);
      }
    }
  }
  return 0;
}
