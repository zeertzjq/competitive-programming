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

const int N = 50010;
int n, top = -1, ch, ans = 0;

struct pt {
  int x, y;

  inline bool operator<(const pt & rhs) const {
    return x == rhs.x ? y < rhs.y : x < rhs.x;
  }
} p[N], s[N];

inline int sqr(int x) { return x * x; }

inline int slen(pt a, pt b) { return sqr(a.x - b.x) + sqr(a.y - b.y); }

inline bool ccw(pt a, pt b, pt c) {
  return (b.x - a.x) * (c.y - b.y) - (c.x - b.x) * (b.y - a.y) > 0;
}

inline int sa2(pt s1, pt s2, pt p) {
  return (p.x - s1.x) * (p.y - s2.y) - (p.x - s2.x) * (p.y - s1.y);
}

int main() {
  n = gi();
  for (int i = 1; i <= n; ++i)
    p[i].x = gi(), p[i].y = gi();
  if (n == 2) {
    putln(slen(p[1], p[2]));
    return 0;
  }
  sort(p + 1, p + 1 + n), s[++top] = p[1], s[++top] = p[2];
  for (int i = 3; i <= n; ++i) {
    while (top && !ccw(s[top - 1], s[top], p[i]))
      --top;
    s[++top] = p[i];
  }
  ch = top, s[++top] = p[n - 1];
  for (int i = n - 2; i; --i) {
    while (top > ch && !ccw(s[top - 1], s[top], p[i]))
      --top;
    s[++top] = p[i];
  }
  ch = top;
  for (int i = 0, j = 2; i < ch; ++i) {
    int sa0 = sa2(s[i], s[i + 1], s[j]), sa = sa2(s[i], s[i + 1], s[j + 1]);
    while (sa0 < sa)
      ++j %= ch, sa0 = sa, sa = sa2(s[i], s[i + 1], s[j + 1]);
    ans = max(ans, max(slen(s[i], s[j]), slen(s[i + 1], s[j])));
  }
  putln(ans);
  return 0;
}
