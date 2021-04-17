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
int n, m, bs, a[N], cnt[N], ans[N];

struct _ {
  int v, *p;

  inline bool operator<(const _ &rhs) const { return v < rhs.v; }
} a_[N];

struct query {
  int b, l, r, id;

  inline bool operator<(const query &rhs) const {
    return b == rhs.b ? r < rhs.r : b < rhs.b;
  }
} q[N];

inline int mv(int p, int tp) {
  cnt[a[p]] += tp ? 1 : -1;
  return cnt[a[p]] == tp ? tp ? 1 : -1 : 0;
}

int main() {
  n = gi(), bs = sqrt(n);
  for (int i = 1; i <= n; ++i)
    a[i] = a_[i].v = gi(), a_[i].p = a + i;
  sort(a_ + 1, a_ + 1 + n);
  for (int i = 1, j = 1; i <= n; ++i)
    a_[j].v != a_[i].v && (j = i), *a_[i].p = j;
  m = gi();
  for (int i = 1; i <= m; ++i)
    q[i].l = gi(), q[i].r = gi(), q[i].b = q[i].l / bs, q[i].id = i;
  sort(q + 1, q + 1 + m);
  int lp = q[1].l, rp = lp, cur = mv(lp, 1);
  for (int i = 1; i <= m; ++i) {
    while (lp > q[i].l)
      cur += mv(--lp, 1);
    while (rp < q[i].r)
      cur += mv(++rp, 1);
    while (lp < q[i].l)
      cur += mv(lp++, 0);
    while (rp > q[i].r)
      cur += mv(rp--, 0);
    ans[q[i].id] = cur;
  }
  for (int i = 1; i <= m; ++i)
    putln(ans[i]);
  return 0;
}
