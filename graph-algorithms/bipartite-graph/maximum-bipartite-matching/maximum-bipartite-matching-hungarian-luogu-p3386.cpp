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
                return true;
            }
        }
    return false;
}

int main() {
    n = geti();
    m = geti();
    e = geti();
    while (e--) g[geti()][geti()] = true;
    for (int x = 1; x <= n; ++x) {
        fill(vis + 1, vis + 1 + m, 0);
        ans += dfs(x);
    }
    putln(ans);
    return 0;
}
