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

const int N = 1000010, P = 998244353;
int n, f[N], bit[N];

inline void upd(int k) {
  for (; k <= n; k += k & -k)
    ++bit[k];
}

inline int qry(int k) {
  int ans = 0;
  for (; k; k &= k - 1)
    ans += bit[k];
  return ans;
}

int main() {
  n = gi();
  f[0] = 1;
  for (int i = 1; i <= n; ++i)
    f[i] = 1LL * f[i - 1] * i % P;
  int ans = 1;
  for (int i = n - 1; i >= 0; --i) {
    int a = gi();
    ans = (ans + 1LL * (a - 1 - qry(a - 1)) * f[i]) % P;
    upd(a);
  }
  putln(ans);
  return 0;
}
