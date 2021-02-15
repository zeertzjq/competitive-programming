// vim: et sw=2 sts=2 fdm=marker
#include <bits/stdc++.h>
using namespace std;

//{{{
inline int gi() {
  int x, f = 0;
  char c;
  while (!isdigit(c = getchar()))
    c == '-' && (f = 1);
  for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0')
    ;
  return f ? -x : x;
}

inline long long gll() {
  int f = 0;
  long long x;
  char c;
  while (!isdigit(c = getchar()))
    c == '-' && (f = 1);
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

inline int pow(int n, int k, int p) {
  int ans = 1;
  for (; k; k >>= 1)
    k & 1 && (ans = 1LL * ans * n % p), n = 1LL * n * n % p;
  return ans;
}

inline int bsgs(int a, int b, int p) {
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
  int g = gi(), p = gi(), _ = gi();
  while (_--) {
    int A = gi(), b = bsgs(g, gi(), p);
    putln(pow(A, b, p));
  }
  return 0;
}
