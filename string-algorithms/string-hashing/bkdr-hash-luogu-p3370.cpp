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

const unsigned long long seed = 131LL, mod = 1111111111111111111LL, N = 10010, M = 1510;

unsigned long long uhash(unsigned long long a, char b) {
    return (a * seed + b) % mod;
}

int n;
unsigned long long a[N];

int main() {
    n = gi();
    for (int i = 1; i <= n; ++i) {
        char c;
        while (!isalnum(c = getchar()))
            ;
        for (a[i] = c; isalnum(c = getchar()); a[i] = uhash(a[i], c))
            ;
    }
    sort(a + 1, a + 1 + n);
    putln(unique(a + 1, a + 1 + n) - a - 1);
    return 0;
}
