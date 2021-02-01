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

const int N = 10000010;
int n, m, prime[N], pcnt = 0, mu[N], ms[N];
bool nprime[N];
long long mss[N];

inline void sieve() {
    mu[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (!nprime[i]) prime[++pcnt] = i, mu[i] = -1;
        for (int j = 1, c; j <= pcnt && i * prime[j] < N; ++j) {
            nprime[c = i * prime[j]] = 1;
            if (!(i % prime[j])) break;
            mu[c] = -mu[i];
        }
    }
    for (int j = 1; j <= pcnt; ++j)
        for (int i = 1; i * prime[j] < N; ++i) ms[i * prime[j]] += mu[i];
    for (int i = 1; i < N; ++i) mss[i] = mss[i - 1] + ms[i];
}

int main() {
    int _ = gi();
    sieve();
    while (_--) {
        n = gi(), m = gi();
        if (n > m) swap(n, m);
        long long ans = 0;
        for (int l = 1, r; l <= n; l = r + 1)
            r = min(n / (n / l), m / (m / l)),
            ans += (mss[r] - mss[l - 1]) * (n / l) * (m / l);
        putln(ans);
    }
    return 0;
}
