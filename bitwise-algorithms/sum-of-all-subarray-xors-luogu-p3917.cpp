#include <bits/stdc++.h>
using namespace std;

//{{{
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

const int N = 100010, K = 32;
int n, c[2][K];
bool f = 0;

int main() {
    n = geti();
    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
        int a = geti();
        f ^= 1;
        for (int j = 0; j < K; ++j) ans += 1LL * (c[f][j] = a & 1 << j ? i - c[!f][j] : c[!f][j]) << j;
    }
    putln(ans);
    return 0;
}
