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

const int N = 3, mod = 1000000007;

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
  int _ = gi();
  while (_--) {
    int n = gi();
    if (n <= 3) {
      puts("1");
      continue;
    }
    n -= 3;
    mat b(3, 3), p(3, 3), a(3, 1);
    b.m[0][0] = b.m[0][2] = b.m[1][0] = b.m[2][1] = 1;
    for (int i = 0; i < 3; ++i)
      p.m[i][i] = 1;
    for (; n; n >>= 1)
      n & 1 && (p *= b), b *= b;
    for (int i = 0; i < 3; ++i)
      a.m[i][0] = 1;
    p *= a, putln(p.m[0][0]);
  }
  return 0;
}
