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

const int base[8] = {2, 3, 5, 7, 11, 13, 17, 19};
const long long U = ~0ULL >> 4;
long long seed = 19260817LL, n, ans;

inline long long ran() { return seed = (seed * 1103515245LL + 12345LL) & U; }

inline long long gcd(long long a, long long b) {
    if (!(a && b)) return a | b;
    int k = 0;
    while (!((a | b) & 1)) a >>= 1, b >>= 1, ++k;
    while (!(a & 1)) a >>= 1;
    do {
        while (!(b & 1)) b >>= 1;
        if (a > b) swap(a, b);
        b -= a;
    } while (b);
    return a << k;
}

inline long long mul(long long a, long long b, long long p) {
    // return (__int128)a * (__int128)b % p;
    long long ans = 0;
    for (; b; b >>= 1) b & 1 && (ans = (ans + a) % p), a = (a << 1) % p;
    return ans;
}

inline long long pow(long long n, long long k, long long p) {
    long long ans = 1;
    for (; k; k >>= 1) k & 1 && (ans = mul(ans, n, p)), n = mul(n, n, p);
    return ans;
}

inline bool miller_test(int a, long long d, long long n) {
    if (n == a) return 1;
    if (!(n % a)) return 0;
    long long x = pow(a, d, n);
    if (x == 1 || x == n - 1) return 1;
    while (d != n - 1) {
        x = mul(x, x, n), d <<= 1;
        if (x == 1) return 0;
        if (x == n - 1) return 1;
    }
    return 0;
}

inline bool miller_rabin(long long n) {
    if (n < 2) return 0;
    long long d = n - 1;
    while (!(d & 1)) d >>= 1;
    for (int i = 0; i < 8; ++i)
        if (!miller_test(base[i], d, n)) return 0;
    return 1;
}

inline long long f(long long x, long long c, long long n) {
    return mul(x, x, n) + c % n;
}

long long find_cycle(long long n) {
    long long x, y = ran() % (n - 1), c = ran() % (n - 1), d;
    for (long long len = 1;; len <<= 1) {
        x = y;
        long long z = 1;
        for (int i = 0; i < len; ++i) {
            y = f(y, c, n), z = mul(z, abs(x - y), n);
            if (!(i & 127) && (d = gcd(z, n)) > 1) return d;
        }
        if ((d = gcd(z, n)) > 1) return d;
    }
}

void pollard_rho(long long n) {
    if (n <= ans) return;
    if (!(n & 1)) {
        while (!(n & 1)) n >>= 1;
        ans = 2, pollard_rho(n);
        return;
    }
    if (miller_rabin(n)) {
        ans = max(ans, n);
        return;
    }
    long long d;
    for (d = find_cycle(n); d == n; d = find_cycle(n))
        ;
    pollard_rho(d), pollard_rho(n / d);
}

int main() {
    int _ = gi();
    while (_--) {
        n = gll(), ans = 1, pollard_rho(n);
        if (ans == n)
            puts("Prime");
        else
            putln(ans);
    }
    return 0;
}
