// vim: sw=4 ts=4 sts=4 et fdm=marker
#include <bits/stdc++.h>
using namespace std;

//{{{
inline int gi() {
    int x, f = 0;
    char c;
    while (!isdigit(c = getchar())) c == '-' && (f = 1);
    for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0')
        ;
    return f ? -x : x;
}

inline long long gll() {
    int f = 0;
    long long x;
    char c;
    while (!isdigit(c = getchar())) c == '-' && (f = 1);
    for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0')
        ;
    return f ? -x : x;
}

template <typename T>
void puti(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) puti(x / 10);
    putchar(x % 10 + '0');
}

template <typename T>
inline void putsp(T x) {
    puti(x), putchar(' ');
}

template <typename T>
inline void putln(T x) {
    puti(x), putchar('\n');
}
//}}}

int p, ans = 0;
long long n, m;

inline int pow(int n, long long k, int p) {
    int ans = 1;
    for (; k; k >>= 1) k & 1 && (ans = 1LL * ans * n % p), n = 1LL * n * n % p;
    return ans;
}

int exgcd(int a, int b, int &x, int &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    int x0, y0, c = exgcd(b, a % b, x0, y0);
    x = y0, y = x0 - a / b * y0;
    return c;
}

inline int inv(int n, int p) {
    int r, t;
    exgcd(n, p, r, t);
    return (r % p + p) % p;
}

int fct(long long n, int pi, int pk) {
    if (!n) return 1;
    int ans = 1;
    for (int i = 2; i < pk; ++i)
        if (i % pi) ans = 1LL * ans * i % pk;
    ans = pow(ans, n / pk, pk);
    for (int i = 2; i <= n % pk; ++i)
        if (i % pi) ans = 1LL * ans * i % pk;
    return 1LL * ans * fct(n / pi, pi, pk) % pk;
}

inline int C(long long n, long long m, int pi, int pk) {
    long long k = 0;
    for (long long i = n; i; i /= pi) k += i / pi;
    for (long long i = m; i; i /= pi) k -= i / pi;
    for (long long i = n - m; i; i /= pi) k -= i / pi;
    return 1LL * fct(n, pi, pk) * inv(fct(m, pi, pk), pk) *
           inv(fct(n - m, pi, pk), pk) * pow(pi, k, pk) % pk;
}

int main() {
    n = gll(), m = gll(), p = gi();
    int tmp = p;
    for (int i = 2; i * i <= tmp; ++i)
        if (!(tmp % i)) {
            int pk = 1;
            while (!(tmp % i)) pk *= i, tmp /= i;
            int m0 = p / pk;
            ans = (ans + 1LL * C(n, m, i, pk) * m0 * inv(m0, pk)) % p;
        }
    if (tmp > 1) {
        int m0 = p / tmp;
        ans = (ans + 1LL * C(n, m, tmp, tmp) * m0 * inv(m0, tmp)) % p;
    }
    putln(ans);
    return 0;
}
