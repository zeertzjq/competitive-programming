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

const int N = 101, mod = 9999973;
int n, m, dp[N][N][N];

inline int c2(int x) { return x * (x - 1) >> 1; }

int main() {
  n = gi(), m = gi(), dp[0][0][0] = 1;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j <= m; ++j)
      for (int k = 0; j + k <= m; ++k)
        if (long long f0 = dp[i][j][k]) {
          dp[i + 1][j][k] = (dp[i + 1][j][k] + f0) % mod;
          if (j + k + 1 <= m)
            dp[i + 1][j + 1][k] =
                (dp[i + 1][j + 1][k] + f0 * (m - j - k)) % mod;
          if (j)
            dp[i + 1][j - 1][k + 1] = (dp[i + 1][j - 1][k + 1] + f0 * j) % mod;
          if (j + k + 2 <= m)
            dp[i + 1][j + 2][k] =
                (dp[i + 1][j + 2][k] + f0 * c2(m - j - k)) % mod;
          if (j && j + k + 1 <= m)
            dp[i + 1][j][k + 1] =
                (dp[i + 1][j][k + 1] + f0 * j * (m - j - k)) % mod;
          if (j >= 2)
            dp[i + 1][j - 2][k + 2] =
                (dp[i + 1][j - 2][k + 2] + f0 * c2(j)) % mod;
        }
  int ans = 0;
  for (int j = 0; j <= m; ++j)
    for (int k = 0; j + k <= m; ++k)
      ans = ((0LL + ans + dp[n][j][k])) % mod;
  putln(ans);
  return 0;
}
