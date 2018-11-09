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

const int N = 500010;
int n, m, s, e0[N], e1[N << 1], anc[N][22], dep[N], dest[N << 1];

inline int log2(int x) {
    int ret = 0;
    while (x >>= 1) ++ret;
    return ret;
}

void dfs(int x) {
    int log2d = log2(dep[x]);
    for (int i = 1; i <= log2d; ++i)
        anc[x][i] = anc[anc[x][i - 1]][i - 1];
    for (int i = e0[x]; i; i = e1[i]) {
        int v = dest[i];
        if (v == anc[x][0]) continue;  // IMPORTANT: skip parent node
        anc[v][0] = x;
        dep[v] = dep[x] + 1;
        dfs(v);
    }
}

int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    while (dep[x] > dep[y])
        x = anc[x][log2(dep[x] - dep[y])];
    if (x == y) return x;
    for (int d = log2(dep[x]); d >= 0; --d)
        if (anc[x][d] != anc[y][d]) {
            x = anc[x][d];
            y = anc[y][d];
        }
    return anc[x][0];
}

int main() {
    n = geti();
    m = geti();
    s = geti();
    for (int i = 1; i < n; ++i) {  // IMPORTANT: edge indexes CANNOT start at 0
        int x = geti(), y = geti();
        dest[(i << 1) - 1] = y;
        dest[i << 1] = x;
        e1[(i << 1) - 1] = e0[x];
        e1[i << 1] = e0[y];
        e0[x] = (i << 1) - 1;
        e0[y] = i << 1;
    }
    dfs(s);
    while (m--) {
        int a = geti(), b = geti();
        putln(lca(a, b));
    }
    return 0;
}
