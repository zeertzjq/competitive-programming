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
int n, a[N], b[N], bit[N];
long long ans = 0;

inline void add(int k) {
    while (k <= n) {
        ++bit[k];
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
    for (int i = 1; i <= n; ++i) a[i] = b[i] = gi();
    sort(b + 1, b + 1 + n);
    int *r = unique(b + 1, b + 1 + n);
    for (int i = 1; i <= n; ++i) a[i] = lower_bound(b + 1, r, a[i]) - b;
    for (int i = 1; i <= n; ++i) {
        ans += i - 1 - qry(a[i]);
        add(a[i]);
    }
    putln(ans);
    return 0;
}
