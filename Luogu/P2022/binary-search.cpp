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

const long long R = 1000000000000000000;
int k, m, p, pv;

inline void p10(int n) {
    p = 0, pv = 1;
    while (n > 9) n /= 10, ++p, pv *= 10;
}

inline long long rk(long long n, int k) {
    long long ans = 1;
    for (long long i = pv, u = k; i <= n; i *= 10, u *= 10)
        ans += min(u - 1, n) - i + 1;
    for (long long i = pv / 10, u = k / 10; u; i /= 10, u /= 10)
        ans += min(u, n) - i + 1;
    return ans;
}

int main() {
    k = gi(), m = gi(), p10(k);
    if (pv == k)
        putln(m == p + 1 ? k : 0);
    else if (rk(k, k) > m)
        puts("0");
    else {
        long long l = k, r = R;
        while (l < r) {
            long long mid = (l + r) >> 1;
            if (rk(mid, k) >= m)
                r = mid;
            else
                l = mid + 1;
        }
        putln(l);
    }
    return 0;
}
