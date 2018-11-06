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

const int N = 500010;
int n, m, a[N], bit[N];

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
    n = geti();
    m = geti();
    for (int i = 1; i <= n; ++i) a[i] = geti();
    while (m--) {
        int o = geti(), x = geti();
        if (o == 1) {
            int y = geti(), k = geti();
            add(x, k);
            add(y + 1, -k);
        } else
            putln(a[x] + qry(x));
    }
    return 0;
}
