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

const int N = 100010, M = 50010;

struct itm {
  int t, p, v;
} q[N], tmp[N];

inline bool cmp0(const itm &lhs, const itm &rhs) { return lhs.t > rhs.t; }
inline bool cmp1(const itm &lhs, const itm &rhs) { return lhs.t < rhs.t; }

int n, m, pos[N], f[N], bit[N];
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

inline void clr(int k) {
  for (; k <= n && bit[k]; k += k & -k)
    bit[k] = 0;
}

void cdq1(int l, int r) {
  if (l >= r)
    return;
  int m = (l + r) >> 1;
  cdq1(l, m), cdq1(m + 1, r);
  int p1 = l, p2 = m + 1, p = l;
  while (p1 <= m && p2 <= r) {
    if (q[p1].p > q[p2].p)
      upd(q[p1].v), tmp[p++] = q[p1++];
    else
      f[q[p2].p] += qry(q[p2].v), tmp[p++] = q[p2++];
  }
  while (p1 <= m)
    tmp[p++] = q[p1++];
  while (p2 <= r)
    f[q[p2].p] += qry(q[p2].v), tmp[p++] = q[p2++];
  for (int i = l; i <= r; ++i)
    clr(tmp[i].v), q[i] = tmp[i];
}

void cdq2(int l, int r) {
  if (l >= r)
    return;
  int m = (l + r) >> 1;
  cdq2(l, m), cdq2(m + 1, r);
  int p1 = l, p2 = m + 1, p = l;
  while (p1 <= m && p2 <= r) {
    if (q[p1].v > q[p2].v)
      upd(q[p1].p), tmp[p++] = q[p1++];
    else
      f[q[p2].p] += qry(q[p2].p), tmp[p++] = q[p2++];
  }
  while (p1 <= m)
    tmp[p++] = q[p1++];
  while (p2 <= r)
    f[q[p2].p] += qry(q[p2].p), tmp[p++] = q[p2++];
  for (int i = l; i <= r; ++i)
    clr(tmp[i].p), q[i] = tmp[i];
}

int main() {
  n = gi(), m = gi();
  for (int i = 1; i <= n; ++i) {
    int v = gi();
    q[i].p = i, q[i].v = v, pos[v] = i, ans += i - 1 - qry(v), upd(v);
  }
  fill(bit + 1, bit + 1 + n, 0);
  for (int i = 1; i <= m; ++i)
    q[pos[gi()]].t = i;
  for (int i = 1; i <= n; ++i)
    if (!q[i].t)
      q[i].t = m + 1;
  sort(q + 1, q + 1 + n, cmp0), cdq1(1, n), sort(q + 1, q + 1 + n, cmp0),
      cdq2(1, n), sort(q + 1, q + 1 + n, cmp1);
  for (int i = 1; i <= m; ++i)
    putln(ans), ans -= f[q[i].p];
  return 0;
}
