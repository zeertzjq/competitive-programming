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

const int N = 1010;
const unsigned B = 1000000000;
int n, a, b;

struct itm {
  int a, b, p;

  inline bool operator<(const itm &rhs) const {
    return p < rhs.p;
  }
} m[N];

struct bi {
  unsigned d[N];
  int sz;

  bi(unsigned n = 0) {
    d[sz = 0] = n;
  }

  bi(const bi &rhs) {
    sz = rhs.sz;
    for (int i = 0; i <= sz; ++i)
      d[i] = rhs.d[i];
  }

  inline bool operator<(const bi &rhs) const {
    if (sz != rhs.sz)
      return sz < rhs.sz;
    for (int i = sz; i >= 0; --i)
      if (d[i] != rhs.d[i])
        return d[i] < rhs.d[i];
    return 0;
  }

  inline bi &operator*=(const unsigned &rhs) {
    unsigned r = 0;
    for (int i = 0; i <= sz; ++i) {
      unsigned long long tmp = 1ULL * d[i] * rhs + r;
      d[i] = tmp % B, r = tmp / B;
    }
    if (r)
      d[++sz] = r;
    return *this;
  }

  inline bi &operator/=(const unsigned &rhs) {
    unsigned long long r = 0;
    for (int i = sz; i >= 0; --i)
      r = r * B + d[i], d[i] = r / rhs, r %= rhs;
    while (sz && !d[sz])
      --sz;
    return *this;
  }
};

int main() {
  n = gi(), a = gi(), b = gi();
  for (int i = 1; i <= n; ++i)
    m[i].a = gi(), m[i].b = gi(), m[i].p = m[i].a * m[i].b;
  sort(m + 1, m + 1 + n);
  bi ans = 0, p = a;
  for (int i = 1; i <= n; ++i) {
    bi tmp = p;
    tmp /= m[i].b, p *= m[i].a;
    if (ans < tmp)
      ans = tmp;
  }
  puti(ans.d[ans.sz]);
  for (int i = ans.sz - 1; i >= 0; --i)
    printf("%09d", ans.d[i]);
  putchar('\n');
  return 0;
}
