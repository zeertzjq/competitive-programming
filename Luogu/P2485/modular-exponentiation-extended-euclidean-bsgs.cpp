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

inline int pow(int n, int k, int p) {
  int ans = 1;
  for (; k; k >>= 1)
    k & 1 && (ans = 1LL * ans * n % p), n = 1LL * n * n % p;
  return ans;
}

inline int exgcd(int a, int b, int &x, int &y) {
  int aa = 1, ab = 0, ba = 0, bb = 1;
  while (b) {
    int q = a / b, r = a % b, ra = aa - q * ba, rb = ab - q * bb;
    a = b, b = r, aa = ba, ab = bb, ba = ra, bb = rb;
  }
  x = aa, y = ab;
  return a;
}

inline int bsgs(int a, int b, int p) {
  if (!a && !b)
    return 1;
  if ((!a && b) || (!b && a))
    return -1;
  int n = sqrt(p) + 1, an = pow(a, n, p);
  unordered_map<int, int> mp;
  for (int i = 0, r = b; i <= n; ++i, r = 1LL * r * a % p)
    mp[r] = i;
  for (int i = 1, l = an; i <= n; ++i, l = 1LL * l * an % p)
    if (mp.count(l))
      return i * n - mp[l];
  return -1;
}

int main() {
  int _ = gi(), k = gi();
  while (_--) {
    int y = gi(), z = gi(), p = gi();
    if (k == 1)
      y %= p, putln(pow(y, z, p));
    else if (k == 2) {
      y %= p, z %= p;
      if (!y && z) {
        puts("Orz, I cannot find x!");
        continue;
      }
      int x, _;
      exgcd(y, p, x, _), putln((1LL * x * z % p + p) % p);
    } else {
      y %= p, z %= p;
      int x = bsgs(y, z, p);
      if (~x)
        putln(x);
      else
        puts("Orz, I cannot find x!");
    }
  }
  return 0;
}
