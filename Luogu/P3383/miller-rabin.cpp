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

inline int gll() {
  int f = 0;
  int x;
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

const int base[8] = {2, 3, 5, 7, 11, 13, 17, 19};
int n, m;

inline int pow(int n, int k, int p) {
  int ans = 1;
  for (; k; k >>= 1)
    k & 1 && (ans = 1LL * ans * n % p), n = 1LL * n * n % p;
  return ans;
}

inline bool miller_test(int a, int d, int n) {
  if (n == a)
    return 1;
  if (!(n % a))
    return 0;
  int x = pow(a, d, n);
  if (x == 1 || x == n - 1)
    return 1;
  while (d != n - 1) {
    x = 1LL * x * x % n, d <<= 1;
    if (x == 1)
      return 0;
    if (x == n - 1)
      return 1;
  }
  return 0;
}

inline bool miller_rabin(int n) {
  if (n < 2)
    return 0;
  int d = n - 1;
  while (!(d & 1))
    d >>= 1;
  for (int i = 0; i < 8; ++i)
    if (!miller_test(base[i], d, n))
      return 0;
  return 1;
}

int main() {
  n = gi(), m = gi();
  while (m--)
    puts(miller_rabin(gi()) ? "Yes" : "No");
  return 0;
}
