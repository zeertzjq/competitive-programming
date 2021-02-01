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

inline int pow(int n, int k, int p) {
    int ans = 1;
    for (; k; k >>= 1) k & 1 && (ans = 1LL * ans * n % p), n = 1LL * n * n % p;
    return ans;
}

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

inline int exbsgs(int a, int b, int p) {
    int d, k = 0, c = 1;
    while ((d = gcd(a, p)) != 1) {
        if (b % d) return -1;
        b /= d, p /= d, ++k, c = 1LL * a / d * c % p;
    }
    int n = sqrt(p) + 1, an = pow(a, n, p);
    unordered_map<int, int> mp;
    for (int i = 0, r = b; i <= n; ++i, r = 1LL * r * a % p) mp[r] = i;
    for (int i = 1, l = 1LL * c * an % p; i <= n; ++i, l = 1LL * l * an % p)
        if (mp.count(l)) return i * n + k - mp[l];
    return -1;
}

int main() {
    for (int a = gi(), p = gi(), b = gi(); a; a = gi(), p = gi(), b = gi()) {
        int x = exbsgs(a % p, b % p, p);
        if (~x)
            putln(x);
        else
            puts("No Solution");
    }
    return 0;
}
