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
int n, m, p, f[N], inv[N];

int getinv(int x) {
  return inv[x] ? inv[x] : inv[x] = (p - 1LL * p / x * getinv(p % x) % p) % p;
}

int C(int n, int m) {
  if (n < m)
    return 0;
  if (n < p)
    return 1LL * f[n] * getinv(f[m]) * getinv(f[n - m]) % p;
  return 1LL * C(n % p, m % p) * C(n / p, m / p) % p;
}

int main() {
  int _ = gi();
  while (_--) {
    n = gi(), m = gi(), p = gi(), f[0] = 1;
    for (int i = 1; i < p; ++i)
      f[i] = 1LL * f[i - 1] * i % p;
    fill(inv + 1, inv + p, 0), inv[1] = 1, putln(C(n + m, m));
  }
  return 0;
}
