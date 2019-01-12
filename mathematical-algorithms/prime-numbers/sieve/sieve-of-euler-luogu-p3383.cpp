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

const int N = 10000010;
int n, m, prime[N], pcnt;
bool nprime[N];

int main() {
    n = gi();
    m = gi();
    nprime[1] = true;  // IMPORTANT: 1 is NOT a prime number
    for (int i = 2; i <= n; ++i) {
        if (!nprime[i]) prime[++pcnt] = i;
        for (int j = 1; j <= pcnt; ++j) {
            int c = i * prime[j];
            if (c > n) break;
            nprime[c] = true;
            if (!(i % prime[j])) break;
        }
    }
    while (m--) puts(nprime[gi()] ? "No" : "Yes");
    return 0;
}
