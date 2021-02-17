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

template <typename T> inline void putsp(T x) { puti(x), putchar(' '); }

template <typename T> inline void putln(T x) { puti(x), putchar('\n'); }
//}}}

const int N = 1010, inf = ~0U >> 1;
int n, p0[N], p1[N], c0, c1, dp[N][N][2];

int main() {
  n = gi();
  for (int i = 1; i <= n; ++i) {
    int p = gi();
    if (p > 0)
      p0[++c0] = p;
    else
      p1[++c1] = -p;
  }
  sort(p0 + 1, p0 + 1 + c0), sort(p1, p1 + 1 + c1);
  for (int l = 1; l <= n; ++l)
    for (int i = 0; i <= min(l, c0); ++i) {
      int j = l - i;
      dp[i][j][0] = i ? min(dp[i - 1][j][0] + (p0[i] - p0[i - 1]) * (n - l + 1),
                            dp[i - 1][j][1] + (p0[i] + p1[j]) * (n - l + 1))
                      : inf >> 1,
      dp[i][j][1] = j ? min(dp[i][j - 1][1] + (p1[j] - p1[j - 1]) * (n - l + 1),
                            dp[i][j - 1][0] + (p1[j] + p0[i]) * (n - l + 1))
                      : inf >> 1;
    }
  putln(min(dp[c0][c1][0], dp[c0][c1][1]));
  return 0;
}
