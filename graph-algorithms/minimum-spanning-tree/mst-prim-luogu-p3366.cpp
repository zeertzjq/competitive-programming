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

typedef pair<int, int> hitem;

const int N = 5010, M = 200010, INF = 2147483647;
int n, m, e0[N], e1[M << 1], dst[M << 1], z[M << 1], dist[N], len = 0, vcnt = 0, hsz = 0;
hitem h[M];
greater<hitem> cmp;
bool vis[N];

void prim() {
    fill(dist + 1, dist + 1 + n, INF);
    dist[1] = 0;
    h[hsz++] = make_pair(0, 1);
    push_heap(h, h + hsz, cmp);
    while (hsz) {
        pop_heap(h, h + hsz--, cmp);
        int u = h[hsz].second;
        if (vis[u]) continue;
        vis[u] = true;  // IMPORTANT: mark u as visited
        len += dist[u];
        ++vcnt;
        if (vcnt == n) return;
        for (int e = e0[u]; e; e = e1[e]) {
            int v = dst[e];
            if (z[e] < dist[v]) {
                dist[v] = z[e];
                h[hsz++] = make_pair(dist[v], v);
                push_heap(h, h + hsz, cmp);
            }
        }
    }
}

int main() {
    n = gi();
    m = gi();
    for (int i = 1; i <= m; ++i) {
        int x = gi(), y = gi();
        z[i << 1] = z[i << 1 | 1] = gi();
        e1[i << 1] = e0[x];
        e0[x] = i << 1;
        dst[i << 1] = y;
        e1[i << 1 | 1] = e0[y];
        e0[y] = i << 1 | 1;
        dst[i << 1 | 1] = x;
    }
    prim();
    if (vcnt == n)
        putln(len);
    else
        puts("orz");
    return 0;
}
