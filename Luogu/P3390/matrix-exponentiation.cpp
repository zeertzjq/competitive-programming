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

const int N = 101, mod = 1000000007;

struct mat {
  int a, b, m[N][N];

  mat(int a, int b) : a(a), b(b) {
    for (int i = 0; i < a; ++i)
      for (int j = 0; j < b; ++j)
        m[i][j] = 0;
  }

  mat &operator*=(const mat &rhs) {
    int bb = rhs.b;
    mat ret(a, bb);
    for (int i = 0; i < a; ++i)
      for (int j = 0; j < bb; ++j)
        for (int k = 0; k < b; ++k)
          ret.m[i][j] = (ret.m[i][j] + 1LL * m[i][k] * rhs.m[k][j]) % mod;
    a = ret.a, b = ret.b;
    for (int i = 0; i < a; ++i)
      for (int j = 0; j < b; ++j)
        m[i][j] = ret.m[i][j];
    return *this;
  }
};

int main() {
  int n = gi();
  long long k = gll();
  mat a(n, n), ans(n, n);
  for (int i = 0; i < n; ++i)
    ans.m[i][i] = 1;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      a.m[i][j] = gi() % mod;
  for (; k; k >>= 1)
    k & 1 && (ans *= a), a *= a;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j)
      putsp(ans.m[i][j]);
    putchar('\n');
  }
  return 0;
}
