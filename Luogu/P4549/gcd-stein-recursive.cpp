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

int gcd(int a, int b) {
  return a && b ? a & 1   ? b & 1 ? a > b ? gcd(b, a - b) : gcd(a, b - a)
                                  : gcd(a, b >> 1)
                    : b & 1 ? gcd(b, a >> 1)
                          : gcd(a >> 1, b >> 1) << 1
                : a | b;
}

int main() {
  int _ = gi(), __ = 0;
  while (_--)
    __ = gcd(__, abs(gi()));
  putln(__);
  return 0;
}
