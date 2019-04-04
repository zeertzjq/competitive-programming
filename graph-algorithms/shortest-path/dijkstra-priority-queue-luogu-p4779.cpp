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

const int N = 100010, M = 200010;
const long long inf = 100000000000;
int n, m, s, e0[N], e1[M], dst[M], w[M], hsz = 0;

struct hitm {
    int d, u;

    inline bool operator<(const hitm &rhs) const { return d > rhs.d; }
} h[N];

long long dis[N];
bool vis[N];

void dijkstra() {
    fill(dis + 1, dis + 1 + n, inf), dis[s] = 0, h[hsz++] = {0, s},
                                     push_heap(h, h + hsz);
    while (hsz) {
        pop_heap(h, h + hsz--);
        int u = h[hsz].u;
        if (vis[u]) continue;
        vis[u] = 1;
        for (int e = e0[u]; e; e = e1[e]) {
            int v = dst[e];
            long long ndis = dis[u] + w[e];
            if (ndis < dis[v])
                dis[v] = ndis, h[hsz++] = {ndis, v}, push_heap(h, h + hsz);
        }
    }
}

int main() {
    n = gi(), m = gi(), s = gi();
    for (int i = 1; i <= m; ++i) {
        int f = gi();
        e1[i] = e0[f], e0[f] = i, dst[i] = gi(), w[i] = gi();
    }
    dijkstra();
    for (int i = 1; i <= n; ++i) putsp(dis[i]);
    putchar('\n');
    return 0;
}
