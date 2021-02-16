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

const int M1 = 1300, M2 = 2000010;
int N, prime[M2], pcnt = 0;
bool nprime[M2];

namespace phi {
int v[M2];
long long s0[M2], ad[M1];

inline void clr() { fill(ad + 1, ad + 1 + N / M2, 0); }

long long s(int n) {
  if (n < M2)
    return s0[n];
  int d = N / n;
  if (ad[d])
    return ad[d];
  long long ans = (1LL * (n + 1) * n) >> 1;
  for (int l = 2, r; l <= n; l = r + 1)
    r = n / (n / l), ans -= (r - l + 1) * s(n / l);
  return ad[d] = ans;
}
} // namespace phi

namespace mu {
int v[M2], s0[M2], ad[M1];

inline void clr() { fill(ad + 1, ad + 1 + N / M2, 0); }

int s(int n) {
  if (n < M2)
    return s0[n];
  int d = N / n;
  if (ad[d])
    return ad[d];
  int ans = 1;
  for (int l = 2, r; l <= n; l = r + 1)
    r = n / (n / l), ans -= (r - l + 1) * s(n / l);
  return ad[d] = ans;
}
} // namespace mu

inline void sieve() {
  phi::v[1] = mu::v[1] = 1;
  for (int i = 2; i < M2; ++i) {
    if (!nprime[i])
      prime[++pcnt] = i, phi::v[i] = i - 1, mu::v[i] = -1;
    for (int j = 1, c; j <= pcnt && i * prime[j] < M2; ++j) {
      nprime[c = i * prime[j]] = 1;
      if (!(i % prime[j])) {
        phi::v[c] = phi::v[i] * prime[j];
        break;
      }
      phi::v[c] = phi::v[i] * (prime[j] - 1);
      mu::v[c] = -mu::v[i];
    }
  }
  for (int i = 1; i < M2; ++i)
    phi::s0[i] = phi::s0[i - 1] + phi::v[i],
    mu::s0[i] = mu::s0[i - 1] + mu::v[i];
}

int main() {
  int _ = gi();
  sieve();
  while (_--)
    N = gi(), phi::clr(), mu::clr(), putsp(phi::s(N)), putln(mu::s(N));
  return 0;
}
