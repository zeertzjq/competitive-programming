#include <bits/stdc++.h>
using namespace std;

//{{{
inline int gi() {
    int x, f = 0;
    char c;
    while (!isdigit(c = getchar()))
        if (c == '-') f = 1;
    for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0')
        ;
    return f ? -x : x;
}

inline long long gll() {
    int f = 0;
    long long x;
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
inline void putsp(T x) {
    puti(x);
    putchar(' ');
}

template <typename T>
inline void putln(T x) {
    puti(x);
    putchar('\n');
}
//}}}

const int N = 100010;
int n, m;
bool bit[N];

inline void add(int k) {
    while (k <= n) {
        bit[k] ^= 1;
        k += k & -k;
    }
}

inline bool qry(int k) {
    bool ret = 0;
    while (k) {
        ret ^= bit[k];
        k &= k - 1;
    }
    return ret;
}

int main() {
    n = gi();
    m = gi();
    while (m--) {
        int t = gi();
        if (t == 1) {
            add(gi());
            add(gi() + 1);
        } else
            putln(qry(gi()));
    }
    return 0;
}
