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

const int N = 5010, M = 200010;

struct edge {
    int x, y, z;

    bool operator<(const edge &rhs) const {
        return z < rhs.z;
    }
} e[M];

int n, m, rnk[N], dad[N], len = 0, ecnt = 0;

inline void unions(int x, int y) {
    if (x == y) return;
    if (rnk[x] == rnk[y]) ++rnk[x];
    if (rnk[x] > rnk[y])
        dad[y] = x;
    else
        dad[x] = y;
}

int finds(int x) {
    return dad[x] == x ? x : dad[x] = finds(dad[x]);
}

void kruskal() {
    for (int i = 1; i <= m; ++i) {
        int rt1 = finds(e[i].x), rt2 = finds(e[i].y);
        if (rt1 == rt2) continue;
        len += e[i].z;
        ++ecnt;
        unions(rt1, rt2);
        if (ecnt == n - 1) return;
    }
}

int main() {
    n = geti();
    m = geti();
    for (int i = 1; i <= n; ++i) dad[i] = i;
    for (int i = 1; i <= m; ++i) {
        e[i].x = geti();
        e[i].y = geti();
        e[i].z = geti();
    }
    sort(e + 1, e + 1 + m);
    kruskal();
    if (ecnt == n - 1)
        putln(len);
    else
        puts("orz");
    return 0;
}
