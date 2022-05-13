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

const int P = 10000010;
int prime[P], pcnt = 0, phi[P];
bool nprime[P];

inline void sieve() {
  phi[1] = 1;
  for (int i = 2; i < P; ++i) {
    if (!nprime[i])
      prime[++pcnt] = i, phi[i] = i - 1;
    for (int j = 1, c; j <= pcnt && i * prime[j] < P; ++j) {
      nprime[c = i * prime[j]] = 1;
      if (!(i % prime[j])) {
        phi[c] = phi[i] * prime[j];
        break;
      }
      phi[c] = phi[i] * (prime[j] - 1);
    }
  }
}

inline int pow(int n, int k, int p) {
  int ans = 1;
  for (; k; k >>= 1)
    k & 1 && (ans = 1LL * ans * n % p), n = 1LL * n * n % p;
  return ans;
}

int solve(int p) {
  if (p == 1)
    return 0;
  return pow(2, solve(phi[p]) + phi[p], p);
}

int main() {
  sieve();
  int _ = gi();
  while (_--)
    putln(solve(gi()));
  return 0;
}
