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

const int N = 100010;
int n, m;
long long s[N], bit1[N], bit2[N];

inline void upd(long long *bit, int k, long long v) {
  for (; k <= n; k += k & -k)
    bit[k] += v;
}

inline long long qry(long long *bit, int k) {
  long long ans = 0;
  for (; k; k &= k - 1)
    ans += bit[k];
  return ans;
}

int main() {
  n = gi(), m = gi();
  for (int i = 1; i <= n; ++i)
    s[i] = s[i - 1] + gll();
  while (m--) {
    int o = gi(), x = gi(), y = gi();
    if (o == 1) {
      long long k = gll();
      upd(bit1, x, k), upd(bit1, y + 1, -k), upd(bit2, x, k * x),
          upd(bit2, y + 1, -k * (y + 1));
    } else
      putln(s[y] + (y + 1) * qry(bit1, y) - qry(bit2, y) - s[x - 1] -
            x * qry(bit1, x - 1) + qry(bit2, x - 1));
  }
  return 0;
}
