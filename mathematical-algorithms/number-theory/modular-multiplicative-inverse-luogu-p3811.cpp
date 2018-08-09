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

void puti(int x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) puti(x / 10);
    putchar(x % 10 + '0');
}

int n;
long long p;
int inv[20000529];

int getinv(int x) {
    return inv[x] ? inv[x] : inv[x] = (p - (p / x) * getinv(p % x) % p) % p;
}

int main() {
    n = geti();
    p = geti();
    inv[1] = 1;
    for (int i = 1; i <= n; ++i) {
        puti(getinv(i));
        putchar('\n');
    }
    return 0;
}
