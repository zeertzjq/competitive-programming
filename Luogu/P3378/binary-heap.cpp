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

const int N = 1000000, inf = ~0U >> 1;
int h[N + 1];

#define sz h[0]
#define L (x << 1)
#define R (x << 1 | 1)
#define P (x >> 1)

inline int minson(int x) {
  int l = L <= sz ? h[L] : inf, r = R <= sz ? h[R] : inf;
  return l < r ? L : R;
}

inline void heapup(int x) {
  while (x > 1 && h[P] > h[x])
    swap(h[x], h[P]), x >>= 1;
}

inline void heapdown(int x) {
  int ms;
  while (L <= sz && h[x] > h[ms = minson(x)])
    swap(h[x], h[ms]), x = ms;
}

int main() {
  int n = gi();
  while (n--)
    switch (gi()) {
    case 1:
      h[++sz] = gi(), heapup(sz);
      break;
    case 2:
      putln(h[1]);
      break;
    case 3:
      swap(h[1], h[sz--]), heapdown(1);
      break;
    }
  return 0;
}
