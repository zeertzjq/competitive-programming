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
queue<int> q;
bool vis[N];

void spfa() {
    fill(dist + 1, dist + 1 + n, INF);
    dist[s] = 0;
    while (!q.empty()) q.pop();
    q.push(s);
    vis[s] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for (int e = e0[u]; e; e = e1[e]) {
            int v = dst[e];
            int ndist = dist[u] + w[e];
            if (ndist < dist[v]) {
                dist[v] = ndist;
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = 1;
                }
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
    spfa();
    for (int i = 1; i <= n; ++i) {
        puti(dist[i]);
        putchar(' ');
    }
    printf("\n");
    return 0;
}
