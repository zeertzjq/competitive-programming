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

const int N = 1000010, B = 1010;
int n, q, bs, bc, a[N], bi[N], b[N], ll[B], rr[B], t[B];

inline void reset(int bb) {
  copy(a + ll[bb], a + rr[bb] + 1, b + ll[bb]),
      sort(b + ll[bb], b + rr[bb] + 1);
}

inline void init() {
  bs = sqrt(n), bc = n / bs;
  if (bs * bc < n)
    ++bc;
  for (int i = 1; i <= n; ++i)
    bi[i] = (i - 1) / bs + 1;
  for (int i = 1; i <= bc; ++i)
    ll[i] = (i - 1) * bs + 1, rr[i] = i * bs;
  rr[bc] = n;
  for (int i = 1; i <= bc; ++i)
    reset(i);
}

inline void upd(int l, int r, int w) {
  for (int i = l; i <= min(rr[bi[l]], r); ++i)
    a[i] += w;
  reset(bi[l]);
  if (bi[l] == bi[r])
    return;
  for (int i = ll[bi[r]]; i <= r; ++i)
    a[i] += w;
  reset(bi[r]);
  for (int i = bi[l] + 1; i < bi[r]; ++i)
    t[i] += w;
}

inline int qry(int l, int r, int w) {
  int ans = 0;
  for (int i = l; i <= min(rr[bi[l]], r); ++i)
    if (a[i] + t[bi[l]] >= w)
      ++ans;
  if (bi[l] == bi[r])
    return ans;
  for (int i = ll[bi[r]]; i <= r; ++i)
    if (a[i] + t[bi[r]] >= w)
      ++ans;
  for (int i = bi[l] + 1; i < bi[r]; ++i)
    ans += b + rr[i] + 1 - lower_bound(b + ll[i], b + rr[i] + 1, w - t[i]);
  return ans;
}

int main() {
  n = gi(), q = gi();
  for (int i = 1; i <= n; ++i)
    a[i] = gi();
  init();
  while (q--) {
    char o = gc();
    int l = gi(), r = gi(), w = gi();
    if (o == 'M')
      upd(l, r, w);
    else
      putln(qry(l, r, w));
  }
  return 0;
}
