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

const int N = 100010;
int n, m, stmx[N][17], log2n;

inline int log2(int x) {
    int ans = 0;
    while (x >>= 1) ++ans;
    return ans;
}

inline void stinit() {
    for (int k = 1; k <= log2n; ++k)
        for (int i = 1; i + (1 << k) - 1 <= n; ++i)
            stmx[i][k] = max(stmx[i][k - 1], stmx[i + (1 << (k - 1))][k - 1]);
}

inline int stqry(int l, int r) {
    int k = log2(r - l + 1);
    return max(stmx[l][k], stmx[r - (1 << k) + 1][k]);
}

int main() {
    n = gi(), m = gi(), log2n = log2(n);
    for (int i = 1; i <= n; ++i) stmx[i][0] = gi();
    stinit();
    while (m--) {
        int l = gi(), r = gi();
        putln(stqry(l, r));
    }
    return 0;
}
