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

inline int phi(int n) {
    int ans = n;
    for (int i = 2; i * i <= n; ++i)
        if (!(n % i)) {
            ans -= ans / i;
            while (!(n % i)) n /= i;
        }
    if (n > 1) ans -= ans / n;
    return ans;
}

inline int pow(int n, int k, int p) {
    int ans = 1;
    for (; k; k >>= 1) k & 1 && (ans = 1LL * ans * n % p), n = 1LL * n * n % p;
    return ans;
}

int main() {
    int a = gi(), b = gi();
    putln(pow(a, phi(b) - 1, b));
    return 0;
}
