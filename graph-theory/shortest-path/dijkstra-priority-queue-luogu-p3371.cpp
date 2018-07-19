#include <bits/stdc++.h>
using namespace std;

const int N = 10010, M = 500010, INF = 2147483647;

int geti() {
    int x /*, f = 0*/;
    char c;
    while (!isdigit(c = getchar()))
        /*if (c == '-') f = 1*/;
    for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0')
        ;
    return /*f ? -x : */ x;
}

void puti(int x) {
    /*if (x < 0) {
        putchar('-');
        x = -x;
    }*/
    if (x > 9) puti(x / 10);
    putchar(x % 10 + '0');
}

int n, m, s, e0[N], e1[M], dst[M], w[M], dist[N];
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;  // IMPORTANT: use std::greater<std::pair<int, int> > to make pq a min-heap
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
        vis[u] = 1;  // IMPORTANT: mark u as visited
        for (int e = e0[u]; e; e = e1[e]) {
            int v = dst[e];
            int ndist = dist[u] + w[e];
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
    for (int i = 1; i <= n; ++i) {
        puti(dist[i]);
        putchar(' ');
    }
    putchar('\n');
    return 0;
}
