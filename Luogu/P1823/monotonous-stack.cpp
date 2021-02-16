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

const int N = 500010;
int n, stk[N], top = 0;
long long ans = 0;

int main() {
  n = gi();
  for (int i = 1; i <= n; ++i) {
    int h = gi();
    if (top) {
      int lb = lower_bound(stk, stk + top, h, std::greater<int>()) - stk;
      if (lb)
        --lb;
      ans += top - lb,
          top = upper_bound(stk, stk + top, h, std::greater<int>()) - stk;
    }
    stk[top++] = h;
  }
  putln(ans);
  return 0;
}
