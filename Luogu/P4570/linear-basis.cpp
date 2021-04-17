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

const int N = 1010, B = 60;
int n, ans = 0;
long long lb[B + 1];

struct rock {
  long long a;
  int b;

  inline bool operator<(const rock & rhs) const { return b > rhs.b; }
} r[N];

inline bool ins(long long x) {
  for (int i = B; i >= 0; --i)
    if (x & 1LL << i) {
      if (!lb[i]) {
        lb[i] = x;
        return 1;
      } else
        x ^= lb[i];
    }
  return 0;
}

int main() {
  n = gi();
  for (int i = 1; i <= n; ++i)
    r[i] = {gll(), gi()};
  sort(r + 1, r + 1 + n);
  for (int i = 1; i <= n; ++i)
    ins(r[i].a) && (ans += r[i].b);
  putln(ans);
  return 0;
}
