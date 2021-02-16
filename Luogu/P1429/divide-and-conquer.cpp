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

const int N = 200010, inf = ~0U >> 1;
int n, tmp[N];

struct point {
  double x, y;

  inline bool operator<(const point &rhs) const {
    return x == rhs.x ? y < rhs.y : x < rhs.x;
  }
} p[N];

inline bool cmpy(int a, int b) { return p[a].y < p[b].y; }

inline double sqr(double n) { return n * n; }

inline double dis(int a, int b) {
  return sqrt(sqr(p[b].x - p[a].x) + sqr(p[b].y - p[a].y));
}

double solve(int l, int r) {
  if (l == r)
    return inf;
  if (l + 1 == r)
    return dis(l, r);
  int m = (l + r) >> 1;
  double d = min(solve(l, m), solve(m + 1, r));
  int c = 0;
  for (int i = l; i <= r; ++i)
    if (fabs(p[m].x - p[i].x) < d)
      tmp[++c] = i;
  sort(tmp + 1, tmp + 1 + c, cmpy);
  for (int i = 1; i < c; ++i)
    for (int j = i + 1; j <= c && p[tmp[j]].y - p[tmp[i]].y < d; ++j)
      d = min(d, dis(tmp[i], tmp[j]));
  return d;
}

int main() {
  n = gi();
  for (int i = 1; i <= n; ++i)
    scanf("%lf%lf", &p[i].x, &p[i].y);
  sort(p + 1, p + 1 + n);
  printf("%.4lf", solve(1, n));
  return 0;
}
