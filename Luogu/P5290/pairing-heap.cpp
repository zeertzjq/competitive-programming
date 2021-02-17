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

const int N = 200010;
int n, c0[N], c1[N], rt[N], m[N], c[N], sib[N], sz[N];

inline int mrg(int x, int y) {
  if (!x || !y)
    return x | y;
  if (m[x] < m[y])
    swap(x, y);
  sib[y] = c[x], c[x] = y, sz[x] += sz[y];
  return x;
}

int mrgl(int l0) {
  if (!l0 || !sib[l0])
    return l0;
  int l1 = sib[l0], l2 = sib[l1];
  sib[l0] = sib[l1] = 0;
  return mrg(mrg(l0, l1), mrgl(l2));
}

inline int pop(int u) {
  int ort = rt[u];
  rt[u] = mrgl(c[ort]), c[ort] = 0, sz[ort] = 1;
  return ort;
}

void dfs(int u) {
  if (!c0[u])
    return;
  int mx = 0;
  for (int v = c0[u]; v; v = c1[v]) {
    dfs(v);
    if (sz[rt[v]] > sz[rt[mx]])
      mx = v;
  }
  for (int v = c0[u]; v; v = c1[v])
    if (v != mx) {
      int tmp = 0;
      while (rt[v]) {
        int a = pop(mx), b = pop(v);
        tmp = mrg(tmp, m[a] > m[b] ? a : b);
      }
      rt[mx] = mrg(rt[mx], tmp);
    }
  rt[u] = mrg(rt[u], rt[mx]);
}

long long hsum(int rt) {
  long long ans = m[rt];
  for (int i = c[rt]; i; i = sib[i])
    ans += hsum(i);
  return ans;
}

int main() {
  n = gi();
  for (int i = 1; i <= n; ++i)
    rt[i] = i, m[i] = gi(), sz[i] = 1;
  for (int i = 2; i <= n; ++i) {
    int f = gi();
    c1[i] = c0[f], c0[f] = i;
  }
  dfs(1);
  putln(hsum(rt[1]));
  return 0;
}
