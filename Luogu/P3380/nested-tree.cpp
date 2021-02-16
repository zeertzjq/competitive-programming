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

const int N = 50010, B = 20, S = N << 7, inf = ~0U >> 1;
int n, m, a[N], v[N << 1], bit[N], ql[B], qr[B], s[S], c[S][2], tot = 0;

struct opt {
  char tp;
  int l, r, k;
} o[N];

void update(int &rt, int l, int r, int x, int w) {
  if (!rt)
    rt = ++tot;
  if (l == r) {
    s[rt] += w;
    return;
  }
  int m = (l + r) >> 1;
  x <= m ? update(c[rt][0], l, m, x, w) : update(c[rt][1], m + 1, r, x, w),
      s[rt] = s[c[rt][0]] + s[c[rt][1]];
}

inline void upd(int p, int x, int w) {
  for (; p <= n; p += p & -p)
    update(bit[p], 1, v[0], x, w);
}

inline void qinit(int *q, int p) {
  for (q[0] = 0; p; p &= p - 1)
    q[++q[0]] = bit[p];
}

inline void down(bool d) {
  for (int i = 1; i <= ql[0]; ++i)
    ql[i] = c[ql[i]][d];
  for (int i = 1; i <= qr[0]; ++i)
    qr[i] = c[qr[i]][d];
}

inline int lsz() {
  int ans = 0;
  for (int i = 1; i <= qr[0]; ++i)
    ans += s[c[qr[i]][0]];
  for (int i = 1; i <= ql[0]; ++i)
    ans -= s[c[ql[i]][0]];
  return ans;
}

inline int sz() {
  int ans = 0;
  for (int i = 1; i <= qr[0]; ++i)
    ans += s[qr[i]];
  for (int i = 1; i <= ql[0]; ++i)
    ans -= s[ql[i]];
  return ans;
}

inline int grk(int l0, int r0, int x, bool mx) {
  qinit(ql, l0 - 1), qinit(qr, r0);
  int l = 1, r = v[0], ans = 1;
  while (l != r) {
    int m = (l + r) >> 1;
    if (x <= m)
      down(0), r = m;
    else
      ans += lsz(), down(1), l = m + 1;
  }
  return mx ? ans + sz() - 1 : ans;
}

inline int kth(int l0, int r0, int k) {
  qinit(ql, l0 - 1), qinit(qr, r0);
  int l = 1, r = v[0];
  while (l != r) {
    int m = (l + r) >> 1, ls = lsz();
    if (k > ls)
      k -= ls, down(1), l = m + 1;
    else
      down(0), r = m;
  }
  return l;
}

int main() {
  n = gi(), m = gi();
  for (int i = 1; i <= n; ++i)
    a[i] = v[i] = gi();
  v[0] = n;
  for (int i = 1; i <= m; ++i)
    if ((o[i].tp = gi()) == 3)
      o[i].l = gi(), o[i].k = v[++v[0]] = gi();
    else {
      o[i].l = gi(), o[i].r = gi(), o[i].k = gi();
      if (o[i].tp != 2)
        v[++v[0]] = o[i].k;
    }
  sort(v + 1, v + 1 + v[0]), v[0] = unique(v + 1, v + 1 + v[0]) - v - 1;
  for (int i = 1; i <= n; ++i)
    upd(i, a[i] = lower_bound(v + 1, v + 1 + v[0], a[i]) - v, 1);
  for (int i = 1; i <= m; ++i)
    if (o[i].tp != 2)
      o[i].k = lower_bound(v + 1, v + 1 + v[0], o[i].k) - v;
  for (int i = 1; i <= m; ++i)
    if (o[i].tp == 3) {
      int p = o[i].l;
      upd(p, a[p], -1), upd(p, a[p] = o[i].k, 1);
    } else {
      int l = o[i].l, r = o[i].r, k = o[i].k;
      if (o[i].tp == 1)
        putln(grk(l, r, k, 0));
      else if (o[i].tp == 2)
        putln(v[kth(l, r, k)]);
      else if (o[i].tp == 4) {
        int rk = grk(l, r, k, 0) - 1;
        putln(rk ? v[kth(l, r, rk)] : -inf);
      } else {
        int rk = grk(l, r, k, 1) + 1;
        putln(rk <= r - l + 1 ? v[kth(l, r, rk)] : inf);
      }
    }
  return 0;
}
