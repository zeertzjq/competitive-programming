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

const int N = 100010;
int n, m, stmax[N][17], log2n;

inline int log2(int x) {
    int ret = 0;
    while (x >>= 1) ++ret;
    return ret;
}

inline void stinit() {
    for (int k = 1; k <= log2n; ++k)
        for (int i = 1; i + (1 << k) - 1 <= n; ++i)
            stmax[i][k] = max(stmax[i][k - 1], stmax[i + (1 << (k - 1))][k - 1]);
}

inline int stquery(int l, int r) {
    int k = log2(r - l + 1);
    return max(stmax[l][k], stmax[r - (1 << k) + 1][k]);
}

int main() {
    n = geti();
    m = geti();
    log2n = log2(n);
    for (int i = 1; i <= n; ++i) stmax[i][0] = geti();
    stinit();
    while (m--) {
        int l = geti(), r = geti();
        putln(stquery(l, r));
    }
    return 0;
}
