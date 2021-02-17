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

const int N = 200010, inf = ~0U >> 1;
int n, dad[N], dis[N], ans = inf;

int finds(int x) {
  if (dad[x] == x)
    return x;
  else {
    int fa = dad[x];
    dad[x] = finds(dad[x]), dis[x] += dis[fa];
  }
  return dad[x];
}

inline void unions(int x, int y) {
  int x0 = finds(x), y0 = finds(y);
  if (x0 == y0)
    ans = min(ans, dis[x] + dis[y] + 1);
  else
    dad[x0] = y0, dis[x] = dis[y] + 1;
}

int main() {
  n = gi();
  for (int i = 1; i <= n; ++i)
    dad[i] = i;
  for (int i = 1; i <= n; ++i)
    unions(i, gi());
  putln(ans);
  return 0;
}
