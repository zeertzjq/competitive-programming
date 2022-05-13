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

inline int exgcd(int a, int b, int &x, int &y) {
  int aa = 1, ab = 0, ba = 0, bb = 1;
  while (b) {
    int q = a / b, r = a % b, ra = aa - q * ba, rb = ab - q * bb;
    a = b, b = r, aa = ba, ab = bb, ba = ra, bb = rb;
  }
  x = aa, y = ab;
  return a;
}

int main() {
  int a = gi(), b = gi(), x, _;
  a %= b, exgcd(a, b, x, _), putln((x % b + b) % b);
  return 0;
}
