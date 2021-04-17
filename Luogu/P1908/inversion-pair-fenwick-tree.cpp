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

const int N = 500010;
int n, a[N], bit[N];

struct _ {
  int v, *p;

  inline bool operator<(const _ & rhs) const { return v < rhs.v; }
} a_[N];

long long ans = 0;

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
  for (int i = 1; i <= n; ++i)
    a[i] = a_[i].v = gi(), a_[i].p = a + i;
  sort(a_ + 1, a_ + 1 + n);
  for (int i = 1, j = 1; i <= n; ++i)
    a_[j].v != a_[i].v && (j = i), *a_[i].p = j;
  for (int i = 1; i <= n; ++i)
    ans += i - 1 - qry(a[i]), upd(a[i]);
  putln(ans);
  return 0;
}
