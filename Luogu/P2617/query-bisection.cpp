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

inline char gc() {
  char c;
  while (isspace(c = getchar()))
    ;
  return c;
}

const int N = 100010;
int n, m, a[N], aidx = 0, v[N << 1], ans[N], tot, bit[N];

struct itm {
  bool tp;
  int l, r, k, id;
} q[N * 3], q1[N * 3], q2[N * 3];

inline void mk(bool tp, int l, int r, int k, int id) {
  q[++tot].tp = tp, q[tot].l = l, q[tot].r = r, q[tot].k = k, q[tot].id = id;
}

inline void upd(int k, int v) {
  for (; k <= n; k += k & -k)
    bit[k] += v;
}

inline int qry(int k) {
  int ans = 0;
  for (; k; k &= k - 1)
    ans += bit[k];
  return ans;
}

void solve(int ql, int qr, int l, int r) {
  if (ql > qr || l > r)
    return;
  if (l == r) {
    for (int i = ql; i <= qr; ++i)
      if (q[i].tp)
        ans[q[i].id] = l;
    return;
  }
  int m = (l + r) >> 1;
  int p1 = 0, p2 = 0;
  for (int i = ql; i <= qr; ++i)
    if (!q[i].tp) {
      if (q[i].k <= m)
        upd(q[i].l, q[i].r), q1[++p1] = q[i];
      else
        q2[++p2] = q[i];
    } else {
      int lss = qry(q[i].r) - qry(q[i].l - 1);
      if (q[i].k > lss)
        q[i].k -= lss, q2[++p2] = q[i];
      else
        q1[++p1] = q[i];
    }
  for (int i = 1; i <= p1; ++i)
    if (!q1[i].tp)
      upd(q1[i].l, -q1[i].r);
  copy(q1 + 1, q1 + 1 + p1, q + ql), copy(q2 + 1, q2 + 1 + p2, q + ql + p1),
      solve(ql, ql + p1 - 1, l, m), solve(ql + p1, qr, m + 1, r);
}

int main() {
  n = gi(), m = gi();
  for (int i = 1; i <= n; ++i)
    q[i].tp = 0, q[i].l = i, q[i].r = 1, a[i] = v[i] = q[i].k = gi();
  tot = v[0] = n;
  while (m--) {
    if (gc() == 'Q') {
      int l = gi(), r = gi(), k = gi();
      mk(1, l, r, k, ++aidx);
    } else {
      int p = gi(), t = gi();
      mk(0, p, -1, a[p], 0), mk(0, p, 1, t, 0), a[p] = v[++v[0]] = t;
    }
  }
  sort(v + 1, v + 1 + v[0]), v[0] = unique(v + 1, v + 1 + v[0]) - v - 1;
  for (int i = 1; i <= tot; ++i)
    if (!q[i].tp)
      q[i].k = lower_bound(v + 1, v + 1 + v[0], q[i].k) - v;
  solve(1, tot, 1, v[0]);
  for (int i = 1; i <= aidx; ++i)
    putln(v[ans[i]]);
  return 0;
}
