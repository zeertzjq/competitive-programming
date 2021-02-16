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

const int B = 50;
int n;
long long lb[B + 1], ans = 0;

int main() {
  n = gi();
  while (n--) {
    long long a = gll();
    for (int j = B; j >= 0; --j)
      if (a & 1LL << j) {
        if (lb[j])
          a ^= lb[j];
        else {
          lb[j] = a;
          break;
        }
      }
  }
  for (int i = B; i >= 0; --i)
    ans = max(ans, ans ^ lb[i]);
  putln(ans);
  return 0;
}
