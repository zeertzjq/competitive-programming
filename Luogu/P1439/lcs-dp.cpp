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

const int N = 100010;
int n, mp[N], f[N], ans = 0;

int main() {
  n = gi();
  for (int i = 1; i <= n; ++i)
    mp[gi()] = i;
  for (int i = 1; i <= n; ++i) {
    int b = mp[gi()];
    if (b > f[ans])
      f[++ans] = b;
    else {
      int p = lower_bound(f + 1, f + 1 + ans, b) - f;
      f[p] = min(f[p], b);
    }
  }
  putln(ans);
  return 0;
}
