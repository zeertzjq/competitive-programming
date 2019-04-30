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

const int N = 2010, p = 998244353;
int n, k, x[N], y[N], ans = 0;

int getinv(int x) {
    return x == 1 ? 1 : (p - 1LL * p / x * getinv(p % x) % p) % p;
}

int main() {
    n = gi(), k = gi();
    for (int i = 1; i <= n; ++i) x[i] = gi(), y[i] = gi();
    for (int i = 1; i <= n; ++i) {
        int l = 1;
        for (int j = 1; j <= n; ++j)
            if (j != i) l = (1LL * l * (x[i] - x[j]) % p + p) % p;
        l = getinv(l);
        for (int j = 1; j <= n; ++j)
            if (j != i) l = (1LL * l * (k - x[j]) % p + p) % p;
        ans = (ans + 1LL * y[i] * l) % p;
    }
    putln(ans);
    return 0;
}
