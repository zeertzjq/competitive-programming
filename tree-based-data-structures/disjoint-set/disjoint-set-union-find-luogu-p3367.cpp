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

const int N = 10010;
int dad[N], rnk[N];

int finds(int x) {
    return dad[x] == x ? x : dad[x] = finds(dad[x]);
}

inline void unions(int x, int y) {
    if (x == y) return;  // IMPORTANT: the two sets must not be the same
    if (rnk[x] == rnk[y]) ++rnk[x];
    if (rnk[x] > rnk[y])
        dad[y] = x;
    else
        dad[x] = y;
}

int main() {
    int n = geti(), m = geti();
    for (int i = 1; i <= n; ++i) dad[i] = i;
    while (m--) {
        int z = geti(), x = geti(), y = geti();
        if (z == 1)
            unions(finds(x), finds(y));
        else
            puts(finds(x) == finds(y) ? "Y" : "N");
    }
    return 0;
}
