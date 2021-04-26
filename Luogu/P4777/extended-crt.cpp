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

int n;
long long m, ans;

inline long long mul(long long a, long long b, long long p) {
  long long ans = 0;
  for (; b; b >>= 1)
    b & 1 && (ans = (ans + a) % p), a = (a << 1) % p;
  return ans;
}

inline long long exgcd(long long a, long long b, long long &x, long long &y) {
  long long aa = 1, ab = 0, ba = 0, bb = 1;
  while (b) {
    long long q = a / b, r = a % b, ra = aa - q * ba, rb = ab - q * bb;
    a = b, b = r, aa = ba, ab = bb, ba = ra, bb = rb;
  }
  x = aa, y = ab;
  return a;
}

int main() {
  n = gi(), m = gll(), ans = gll();
  for (int i = 2; i <= n; ++i) {
    long long p = gll(), b = gll(), c = (b - ans % p + p) % p, x, t,
              d = exgcd(m, p, x, t), r = p / d;
    if (c % d)
      return -1;
    x = mul(x, c / d, r), ans += x * m, m *= r, ans = (ans % m + m) % m;
  }
  putln(ans);
  return 0;
}
