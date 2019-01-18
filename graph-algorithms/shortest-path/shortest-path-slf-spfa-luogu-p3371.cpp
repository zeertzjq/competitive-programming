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

struct qi {
    int val;
    qi *next;

    qi(int v, qi *n) : val(v), next(n) {}
};

const int N = 10010, M = 500010, INF = 2147483647;
int n, m, s, e0[N], e1[M], dst[M], w[M], dist[N];
bool inq[N];
qi *head = NULL, *tail = NULL;

inline void pf(int v) {
    head = new qi(v, head);
    if (!tail) tail = head;
}

inline void pb(int v) {
    tail = tail->next = new qi(v, NULL);
}

inline int pop() {
    qi *h = head;
    int ret = h->val;
    head = h->next;
    if (h == tail) tail = NULL;
    delete h;
    return ret;
}

void spfa() {
    fill(dist + 1, dist + 1 + n, INF);
    dist[s] = 0;
    pf(s);
    inq[s] = 1;
    while (head) {
        int u = pop();
        inq[u] = 0;
        for (int e = e0[u]; e; e = e1[e]) {
            int v = dst[e];
            int ndist = dist[u] + w[e];
            if (ndist < dist[v]) {
                dist[v] = ndist;
                if (!inq[v]) {
                    if (!head || ndist < dist[head->val])
                        pf(v);
                    else
                        pb(v);
                    inq[v] = 1;
                }
            }
        }
    }
}

int main() {
    n = gi();
    m = gi();
    s = gi();
    for (int i = 1; i <= m; ++i) {
        int f = gi();
        e1[i] = e0[f];
        e0[f] = i;
        dst[i] = gi();
        w[i] = gi();
    }
    spfa();
    for (int i = 1; i <= n; ++i) putsp(dist[i]);
    putchar('\n');
    return 0;
}
