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

const int N = 1010;
int n, m, e, xm[N], ym[N], ans = 0, vis[N];
bool g[N][N];

bool dfs(int x) {
    for (int y = 1; y <= m; ++y)
        if (g[x][y] && !vis[y]) {
            vis[y] = 1;
            if (!ym[y] || dfs(ym[y])) {
                xm[x] = y;
                ym[y] = x;
                return 1;
            }
        }
    return 0;
}

int main() {
    n = gi();
    m = gi();
    e = gi();
    while (e--) g[gi()][gi()] = 1;
    for (int x = 1; x <= n; ++x) {
        fill(vis + 1, vis + 1 + m, 0);
        ans += dfs(x);
    }
    putln(ans);
    return 0;
}
