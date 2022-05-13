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

const int N = 200010;
int n, m, sgt[N << 2];
char s[N];
bool a[N], xt[N << 2];

#define L (x << 1)
#define R (x << 1 | 1)

inline void push(int x, int l, int r) {
  if (!xt[x])
    return;
  int m = (l + r) >> 1;
  sgt[L] = m - l + 1 - sgt[L], sgt[R] = r - m - sgt[R], xt[L] ^= 1, xt[R] ^= 1,
  xt[x] = 0;
}

void add(int x, int l, int r, int ll, int rr) {
  if (l > rr || r < ll)
    return;
  if (l >= ll && r <= rr) {
    sgt[x] = r - l + 1 - sgt[x], xt[x] ^= 1;
    return;
  }
  push(x, l, r);
  int m = (l + r) >> 1;
  add(L, l, m, ll, rr), add(R, m + 1, r, ll, rr), sgt[x] = sgt[L] + sgt[R];
}

int qry(int x, int l, int r, int ll, int rr) {
  if (l > rr || r < ll)
    return 0;
  if (l >= ll && r <= rr)
    return sgt[x];
  push(x, l, r);
  int m = (l + r) >> 1;
  return qry(L, l, m, ll, rr) + qry(R, m + 1, r, ll, rr);
}

void bld(int x, int l, int r) {
  if (l == r) {
    sgt[x] = a[l];
    return;
  }
  int m = (l + r) >> 1;
  bld(L, l, m), bld(R, m + 1, r), sgt[x] = sgt[L] + sgt[R];
}

int main() {
  n = gi(), m = gi(), scanf("%s", s + 1);
  for (int i = 1; i <= n; ++i)
    a[i] = s[i] == '1';
  bld(1, 1, n);
  while (m--) {
    int p = gi(), l = gi(), r = gi();
    if (p)
      putln(qry(1, 1, n, l, r));
    else
      add(1, 1, n, l, r);
  }
  return 0;
}
