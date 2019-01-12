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
void putsp(T x) {
    puti(x);
    putchar(' ');
}

template <typename T>
void putln(T x) {
    puti(x);
    putchar('\n');
}
//}}}

const int N = 500010;
int n, a[N], tmp[N];
long long ans = 0;

void solve(int l, int r) {
    if (l >= r) return;
    int m = (l + r) >> 1;
    solve(l, m);
    solve(m + 1, r);
    int p = l, q = m + 1, o = l;
    while (p <= m && q <= r)
        if (a[p] > a[q]) {
            ans += m - p + 1;
            tmp[o++] = a[q++];
        } else
            tmp[o++] = a[p++];
    while (p <= m) tmp[o++] = a[p++];
    while (q <= r) tmp[o++] = a[q++];
    copy(tmp + l, tmp + r + 1, a + l);
}

int main() {
    n = gi();
    for (int i = 1; i <= n; ++i) a[i] = gi();
    solve(1, n);
    putln(ans);
    return 0;
}
