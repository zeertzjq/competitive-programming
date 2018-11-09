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

typedef pair<int, int> qitem;

const int N = 5010, M = 200010, INF = 2147483647;
int n, m, e0[N], e1[M << 1], dst[M << 1], z[M << 1], dist[N], len = 0, vcnt = 0;
priority_queue<qitem, vector<qitem>, greater<qitem> > pq;  // IMPORTANT: pq should be a min-heap
bool vis[N];

void prim() {
    fill(dist + 1, dist + 1 + n, INF);
    dist[1] = 0;
    pq.push(make_pair(0, 1));
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if (vis[u]) continue;
        vis[u] = true;  // IMPORTANT: mark u as visited
        len += dist[u];
        ++vcnt;
        if (vcnt == n) return;
        for (int i = e0[u]; i; i = e1[i]) {
            int v = dst[i];
            if (z[i] < dist[v]) {
                dist[v] = z[i];
                pq.push(make_pair(dist[v], v));
            }
        }
    }
}

int main() {
    n = geti();
    m = geti();
    for (int i = 1; i <= m; ++i) {
        int x = geti(), y = geti();
        z[(i << 1) - 1] = z[i << 1] = geti();
        dst[(i << 1) - 1] = y;
        dst[i << 1] = x;
        e1[(i << 1) - 1] = e0[x];
        e1[i << 1] = e0[y];
        e0[x] = (i << 1) - 1;
        e0[y] = i << 1;
    }
    prim();
    if (vcnt == n)
        putln(len);
    else
        puts("orz");
    return 0;
}
