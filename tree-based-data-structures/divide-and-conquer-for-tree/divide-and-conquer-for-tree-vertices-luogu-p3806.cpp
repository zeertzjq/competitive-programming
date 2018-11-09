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

const int N = 10010, M = 101, E = N << 1;
short n, m, e0[N], e1[E], c[E], dst[E], sz[N], tot, rt, rtmsz = N, dcnt = 0, vdcnt = 0;
int k[M], dist[N], vdist[2][N];
bool ans[M], vis[N], f;

void grt(short u, short fa) {
    short msz = 0;
    sz[u] = 1;
    for (short i = e0[u]; i; i = e1[i]) {
        short v = dst[i];
        if (v == fa || vis[v]) continue;  // IMPORTANT: skip the parent node or nodes not in the current tree
        grt(v, u);
        msz = max(msz, sz[v]);
        sz[u] += sz[v];
    }
    msz = max((int)msz, tot - sz[u]);  // IMPORTANT: the parent node is also the root of a subtree
    if (msz < rtmsz) {
        rtmsz = msz;
        rt = u;
    }
}

void gdist(short u, short fa, int d) {
    dist[++dcnt] = d;
    for (short i = e0[u]; i; i = e1[i]) {
        short v = dst[i];
        if (v == fa || vis[v]) continue;  // IMPORTANT: skip the parent node or nodes not in the current tree
        gdist(v, u, d + c[i]);
    }
}

inline void gans(int d) {
    vdist[f][vdcnt + 1] = 0;  // IMPORTANT: std::lower_bound may return a pointer to the element past the last
    for (int i = 1; i <= m; ++i) ans[i] |= *lower_bound(vdist[f] + 1, vdist[f] + 1 + vdcnt, k[i] - d) == k[i] - d;
}

void solve(short u) {
    f = 0;
    vis[u] = 1;
    vdcnt = 1;
    vdist[f][1] = 0;
    for (int i = e0[u]; i; i = e1[i]) {
        short v = dst[i];
        if (vis[v]) continue;
        dcnt = 0;
        dist[v] = c[i];
        gdist(v, u, c[i]);
        sort(dist + 1, dist + 1 + dcnt);  // IMPORTANT: sort the distances
        for (int i = 1; i <= dcnt; ++i) gans(dist[i]);
        merge(vdist[f] + 1, vdist[f] + 1 + vdcnt, dist + 1, dist + 1 + dcnt, vdist[!f] + 1);
        f ^= 1;
        vdcnt += dcnt;
    }
    for (int i = e0[u]; i; i = e1[i]) {
        short v = dst[i];
        if (vis[v]) continue;
        rt = 0;
        rtmsz = N;
        tot = sz[v] < sz[u] ? sz[v] : sz[v] - sz[u];  // IMPORTANT: update the tree size
        grt(v, 0);
        solve(rt);
    }
}

int main() {
    tot = n = geti();
    m = geti();
    for (short i = 1; i < n; ++i) {
        short a = geti(), b = geti();
        c[(i << 1) - 1] = c[i << 1] = geti();
        dst[(i << 1) - 1] = b;
        dst[i << 1] = a;
        e1[(i << 1) - 1] = e0[a];
        e1[i << 1] = e0[b];
        e0[a] = (i << 1) - 1;
        e0[b] = i << 1;
    }
    for (short i = 1; i <= m; ++i) k[i] = geti();
    grt(1, 0);
    solve(rt);
    for (short i = 1; i <= m; ++i) puts(ans[i] ? "AYE" : "NAY");
    return 0;
}
