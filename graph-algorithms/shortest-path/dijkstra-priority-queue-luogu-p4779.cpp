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

const int N = 100010, M = 200010;
const long long INF = 100000000000;
int n, m, s, e0[N], e1[M], dst[M], w[M];
long long dist[N];
priority_queue<qitem, vector<qitem>, greater<qitem> > pq;  // IMPORTANT: pq should be a min-heap
bool vis[N];

// IMPORTANT: for acyclic graphs with non-negative edge weights ONLY
void dijkstra() {
    fill(dist + 1, dist + 1 + n, INF);
    dist[s] = 0;
    while (!pq.empty()) pq.pop();
    pq.push(make_pair(0, s));
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if (vis[u]) continue;
        vis[u] = true;  // IMPORTANT: mark u as visited
        for (int e = e0[u]; e; e = e1[e]) {
            int v = dst[e];
            long long ndist = dist[u] + w[e];
            if (ndist < dist[v]) {
                dist[v] = ndist;
                pq.push(make_pair(ndist, v));
            }
        }
    }
}

int main() {
    n = geti();
    m = geti();
    s = geti();
    for (int i = 1; i <= m; ++i) {
        int f = geti();
        e1[i] = e0[f];
        e0[f] = i;
        dst[i] = geti();
        w[i] = geti();
    }
    dijkstra();
    for (int i = 1; i <= n; ++i) putsp(dist[i]);
    putchar('\n');
    return 0;
}
