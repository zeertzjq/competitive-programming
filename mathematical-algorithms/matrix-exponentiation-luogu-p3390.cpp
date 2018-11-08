#include <bits/stdc++.h>
using namespace std;

inline int geti() {
    int x, f = 0;
    char c;
    while (!isdigit(c = getchar()))
        if (c == '-') f = 1;
    for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0')
        ;
    return f ? -x : x;
}

inline long long getll() {
    long long x;
    int f = 0;
    char c;
    while (!isdigit(c = getchar()))
        if (c == '-') f = 1;
    for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0')
        ;
    return f ? -x : x;
}

template <typename T>
void puti(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) puti(x / 10);
    putchar(x % 10 + '0');
}

template <typename T>
void putsp(T x) {
    puti(x);
    putchar(' ');
}

template <typename T>
void putln(T x) {
    puti(x);
    putchar('\n');
}

const int N = 101, mod = 1000000007;
int n, a[2][N][N], r[2][N][N];
long long k;
bool fa = false, fr = false;

inline void multra() {
    fr ^= 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            r[fr][i][j] = 0;
            for (int k = 1; k <= n; ++k)
                r[fr][i][j] = (r[fr][i][j] + 1LL * r[!fr][i][k] * a[fa][k][j]) % mod;
        }
}

inline void multaa() {
    fa ^= 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            a[fa][i][j] = 0;
            for (int k = 1; k <= n; ++k)
                a[fa][i][j] = (a[fa][i][j] + 1LL * a[!fa][i][k] * a[!fa][k][j]) % mod;
        }
}

int main() {
    n = geti();
    k = getll();
    for (int i = 1; i <= n; ++i) r[fr][i][i] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            a[fa][i][j] = geti();
    while (k) {
        if (k & 1) multra();
        multaa();
        k >>= 1;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j < n; ++j) putsp(r[fr][i][j]);
        putln(r[fr][i][n]);
    }
    return 0;
}
