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
int n, m, s, e0[N], e1[N << 1], dest[N << 1], q0[N], q1[N << 1], qi[N << 1], aidx[N << 1], ans[N], dad[N];
bool vis[N];

int finds(int x) {
    return dad[x] == x ? x : dad[x] = finds(dad[x]);
}

void tarjan(int u, int pre) {
    for (int i = e0[u]; i; i = e1[i]) {
        int v = dest[i];
        if (v == pre) continue;  // IMPORTANT: skip parent node
        tarjan(v, u);
        dad[finds(v)] = u;
        vis[v] = true;
    }
    for (int i = q0[u]; i; i = q1[i]) {
        int a = aidx[i], v = qi[i];
        if (vis[v] && !ans[a]) ans[a] = finds(v);
    }
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
    for (int i = 1; i <= m; ++i) {
        int a = geti(), b = geti();
        aidx[(i << 1) - 1] = aidx[i << 1] = i;
        qi[(i << 1) - 1] = b;
        qi[i << 1] = a;
        q1[(i << 1) - 1] = q0[a];
        q1[i << 1] = q0[b];
        q0[a] = (i << 1) - 1;
        q0[b] = i << 1;
    }
    for (int i = 1; i <= n; ++i) dad[i] = i;
    tarjan(s, 0);
    for (int i = 1; i <= m; ++i) putln(ans[i]);
    return 0;
}
