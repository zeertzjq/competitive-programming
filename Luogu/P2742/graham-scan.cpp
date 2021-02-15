// vim: et sw=2 sts=2 fdm=marker
#include <bits/stdc++.h>
using namespace std;

//{{{
inline int gi() {
  int x, f = 0;
  char c;
  while (!isdigit(c = getchar()))
    c == '-' && (f = 1);
  for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0')
    ;
  return f ? -x : x;
}

inline long long gll() {
  int f = 0;
  long long x;
  char c;
  while (!isdigit(c = getchar()))
    c == '-' && (f = 1);
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

const int N = 10010;
int n, top = 0;
double ans = 0;

struct pt {
  double x, y;

  inline bool operator<(const pt &rhs) const {
    return x == rhs.x ? y < rhs.y : x < rhs.x;
  }
} p[N], stk[N];

inline double sqr(double x) { return x * x; }

inline double len(pt a, pt b) { return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y)); }

inline bool ccw(pt a, pt b, pt c) {
  return (b.x - a.x) * (c.y - b.y) - (c.x - b.x) * (b.y - a.y) > 0;
}

int main() {
  n = gi();
  for (int i = 1; i <= n; ++i)
    scanf("%lf%lf", &p[i].x, &p[i].y);
  sort(p + 1, p + 1 + n), stk[++top] = p[1], stk[++top] = p[2];
  for (int i = 3; i <= n; ++i) {
    while (top > 1 && !ccw(stk[top - 1], stk[top], p[i]))
      --top;
    stk[++top] = p[i];
  }
  for (int i = 1; i < top; ++i)
    ans += len(stk[i], stk[i + 1]);
  top = 0, stk[++top] = p[n], stk[++top] = p[n - 1];
  for (int i = n - 2; i; --i) {
    while (top > 1 && !ccw(stk[top - 1], stk[top], p[i]))
      --top;
    stk[++top] = p[i];
  }
  for (int i = 1; i < top; ++i)
    ans += len(stk[i], stk[i + 1]);
  printf("%.2lf\n", ans);
  return 0;
}
