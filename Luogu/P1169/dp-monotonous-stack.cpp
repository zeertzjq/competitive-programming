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

const int N = 2010;
int n, m, w[N][N], stk[N], top, ub[N], a1 = 0, a2 = 0;
bool mp[N][N];

inline int sq(int x) {
  return x * x;
}

void solve() {
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      w[i][j] = mp[i][j] ? w[i][j - 1] + 1 : 0;
  for (int j = 1; j <= m; ++j) {
    top = 0;
    for (int i = 1; i <= n + 1; ++i) {
      int ubm = i;
      while (top && w[i][j] < stk[top])
        a1 = max(a1, sq(min(i - ub[top], stk[top]))),
        a2 = max(a2, (i - ub[top]) * stk[top]), ubm = min(ubm, ub[top--]);
      stk[++top] = w[i][j], ub[top] = ubm;
    }
  }
}

int main() {
  n = gi(), m = gi();
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      mp[i][j] = gi() ^ (i & 1) ^ (j & 1);
  solve();
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      mp[i][j] ^= 1;
  solve(), putln(a1), putln(a2);
  return 0;
}
