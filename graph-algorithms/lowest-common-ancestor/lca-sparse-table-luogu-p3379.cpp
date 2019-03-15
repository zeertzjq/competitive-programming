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

const int N = 500010;
int n, m, s, e0[N], e1[N << 1], anc[N][22], dep[N], dst[N << 1];

inline int log2(int x) {
    int ans = 0;
    while (x >>= 1) ++ans;
    return ans;
}

void dfs(int x) {
    int log2d = log2(dep[x]);
    for (int i = 1; i <= log2d; ++i) anc[x][i] = anc[anc[x][i - 1]][i - 1];
    for (int e = e0[x]; e; e = e1[e]) {
        int v = dst[e];
        if (v == anc[x][0]) continue;  // IMPORTANT: skip parent node
        anc[v][0] = x;
        dep[v] = dep[x] + 1;
        dfs(v);
    }
}

int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    while (dep[x] > dep[y]) x = anc[x][log2(dep[x] - dep[y])];
    if (x == y) return x;
    for (int d = log2(dep[x]); d >= 0; --d)
        if (anc[x][d] != anc[y][d]) {
            x = anc[x][d];
            y = anc[y][d];
        }
    return anc[x][0];
}

int main() {
    n = gi();
    m = gi();
    s = gi();
    for (int i = 1; i < n; ++i) {
        int x = gi(), y = gi();
        e1[i << 1] = e0[x];
        e0[x] = i << 1;
        dst[i << 1] = y;
        e1[i << 1 | 1] = e0[y];
        e0[y] = i << 1 | 1;
        dst[i << 1 | 1] = x;
    }
    dfs(s);
    while (m--) {
        int a = gi(), b = gi();
        putln(lca(a, b));
    }
    return 0;
}
