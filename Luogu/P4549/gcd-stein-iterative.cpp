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

inline int gcd(int a, int b) {
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

int main() {
    int _ = gi(), __ = 0;
    while (_--) __ = gcd(__, abs(gi()));
    putln(__);
    return 0;
}
