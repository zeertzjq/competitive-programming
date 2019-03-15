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

const int N = 10010;
int dad[N], rk[N];

int finds(int x) { return dad[x] == x ? x : dad[x] = finds(dad[x]); }

inline void unions(int x, int y) {
    if (x == y) return;  // IMPORTANT: the two sets must not be the same
    if (rk[x] == rk[y]) ++rk[x];
    if (rk[x] > rk[y])
        dad[y] = x;
    else
        dad[x] = y;
}

int main() {
    int n = gi(), m = gi();
    for (int i = 1; i <= n; ++i) dad[i] = i;
    while (m--) {
        int z = gi(), x = gi(), y = gi();
        if (z == 1)
            unions(finds(x), finds(y));
        else
            puts(finds(x) == finds(y) ? "Y" : "N");
    }
    return 0;
}
