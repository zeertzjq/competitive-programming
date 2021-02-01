// vim: et sw=4 sts=4 fdm=marker
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

inline long long mul(long long a, long long b, long long p) {
    long long ans = 0;
    for (; b; b >>= 1) b & 1 && (ans = (ans + a) % p), a = (a << 1) % p;
    return ans;
}

inline long long pow(long long n, long long k, long long p) {
    long long ans = 1;
    for (; k; k >>= 1) k & 1 && (ans = mul(ans, n, p)), n = mul(n, n, p);
    return ans;
}

inline long long bsgs(long long a, long long b, long long p) {
    long long n = sqrt(p) + 1, an = pow(a, n, p);
    unordered_map<long long, long long> mp;
    for (long long i = 0, r = b; i <= n; ++i, r = mul(r, a, p)) mp[r] = i;
    for (long long i = 1, l = an; i <= n; ++i, l = mul(l, an, p))
        if (mp.count(l)) return i * n - mp[l];
    return -1;
}

int main() {
    long long k = gll(), m = gll();
    putln(bsgs(10, (k * 9 + 1) % m, m));
    return 0;
}
