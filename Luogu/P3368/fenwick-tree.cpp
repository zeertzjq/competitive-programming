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

const int N = 500010;
int n, m, a[N], bit[N];

inline void upd(int k, int v) {
  for (; k <= n; k += k & -k)
    bit[k] += v;
}

inline int qry(int k) {
  int ans = 0;
  for (; k; k &= k - 1)
    ans += bit[k];
  return ans;
}

int main() {
  n = gi(), m = gi();
  for (int i = 1; i <= n; ++i)
    a[i] = gi();
  while (m--) {
    int o = gi(), x = gi();
    if (o == 1) {
      int y = gi(), k = gi();
      upd(x, k), upd(y + 1, -k);
    } else
      putln(a[x] + qry(x));
  }
  return 0;
}
