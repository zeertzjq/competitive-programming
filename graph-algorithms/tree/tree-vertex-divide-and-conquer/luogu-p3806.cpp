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

const int N = 10010, M = 101, E = N << 1;
int n, m, e0[N], e1[E], c[E], dst[E], sz[N], tot, rt,
    rtmsz = N, dcnt = 0, vdcnt = 0, k[M], dis[N], vdis[2][N];
bool ans[M], vis[N], f;

void grt(int u, int fa) {
    int msz = 0;
    sz[u] = 1;
    for (int e = e0[u]; e; e = e1[e]) {
        int v = dst[e];
        if (v == fa || vis[v]) continue;
        grt(v, u), msz = max(msz, sz[v]), sz[u] += sz[v];
    }
    msz = max((int)msz, tot - sz[u]);
    if (msz < rtmsz) rtmsz = msz, rt = u;
}

void gdis(int u, int fa, int d) {
    dis[++dcnt] = d;
    for (int e = e0[u]; e; e = e1[e]) {
        int v = dst[e];
        if (v == fa || vis[v]) continue;

        gdis(v, u, d + c[e]);
    }
}

inline void gans(int d) {
    vdis[f][vdcnt + 1] = 0;
    for (int i = 1; i <= m; ++i)
        ans[i] |= *lower_bound(vdis[f] + 1, vdis[f] + 1 + vdcnt, k[i] - d) ==
                  k[i] - d;
}

void solve(int u) {
    f = 0, vis[u] = 1, vdcnt = 1, vdis[f][1] = 0;
    for (int e = e0[u]; e; e = e1[e]) {
        int v = dst[e];
        if (vis[v]) continue;
        dcnt = 0, dis[v] = c[e], gdis(v, u, c[e]);
        sort(dis + 1, dis + 1 + dcnt);
        for (int i = 1; i <= dcnt; ++i) gans(dis[i]);
        merge(vdis[f] + 1, vdis[f] + 1 + vdcnt, dis + 1, dis + 1 + dcnt,
              vdis[!f] + 1),
            f ^= 1, vdcnt += dcnt;
    }
    for (int e = e0[u]; e; e = e1[e]) {
        int v = dst[e];
        if (vis[v]) continue;
        rt = 0, rtmsz = N, tot = sz[v] < sz[u] ? sz[v] : sz[v] - sz[u],
        grt(v, 0), solve(rt);
    }
}

int main() {
    tot = n = gi(), m = gi();
    for (int i = 1; i < n; ++i) {
        int a = gi(), b = gi();
        c[i << 1] = c[i << 1 | 1] = gi(), e1[i << 1] = e0[a], e0[a] = i << 1,
               dst[i << 1] = b, e1[i << 1 | 1] = e0[b], e0[b] = i << 1 | 1,
               dst[i << 1 | 1] = a;
    }
    for (int i = 1; i <= m; ++i) k[i] = gi();
    grt(1, 0), solve(rt);
    for (int i = 1; i <= m; ++i) puts(ans[i] ? "AYE" : "NAY");
    return 0;
}
