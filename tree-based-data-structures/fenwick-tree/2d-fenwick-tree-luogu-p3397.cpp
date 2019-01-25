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

const int N = 1010;
int n, m, bit[N][N];

inline void add(int x, int y, int v) {
    for (int i = x; i <= n; i += i & -i)
        for (int j = y; j <= n; j += j & -j)
            bit[i][j] += v;
}

inline int qry(int x, int y) {
    int ret = 0;
    for (int i = x; i; i &= i - 1)
        for (int j = y; j; j &= j - 1)
            ret += bit[i][j];
    return ret;
}

int main() {
    n = gi();
    m = gi();
    while (m--) {
        int x1 = gi(), y1 = gi(), x2 = gi(), y2 = gi();
        add(x1, y1, 1);
        add(x1, y2 + 1, -1);
        add(x2 + 1, y1, -1);
        add(x2 + 1, y2 + 1, 1);
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) putsp(qry(i, j));
        putchar('\n');
    }
    return 0;
}
