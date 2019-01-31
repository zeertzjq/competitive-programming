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

const int N = 500010;
int n, m, s[N], bit[N];

inline void add(int k, int v) {
    while (k <= n) {
        bit[k] += v;
        k += k & -k;
    }
}

inline int qry(int k) {
    int ret = 0;
    while (k) {
        ret += bit[k];
        k &= k - 1;
    }
    return ret;
}

int main() {
    n = gi();
    m = gi();
    for (int i = 1; i <= n; ++i) s[i] = s[i - 1] + gi();
    while (m--) {
        int o = gi(), x = gi(), y = gi();
        if (o == 1)
            add(x, y);
        else
            putln(s[y] + qry(y) - s[x - 1] - qry(x - 1));
    }
    return 0;
}
