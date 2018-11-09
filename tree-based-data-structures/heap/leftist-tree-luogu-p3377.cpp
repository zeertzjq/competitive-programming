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

const int N = 100010;

int dist[N], dad[N], son[N][2], val[N];
int n, m;

inline int root(int p) {
    while (dad[p]) p = dad[p];
    return p;
}

int merge(int l, int r) {
    if (!l) return r;
    if (!r) return l;
    if (l == r) return l;
    if (val[l] > val[r] || (val[l] == val[r] && l > r)) swap(l, r);
    son[l][1] = merge(son[l][1], r);
    dad[son[l][1]] = l;
    if (!son[l][0] || !son[l][1])
        dist[l] = 0;
    else {
        if (dist[son[l][1]] > dist[son[l][0]]) swap(son[l][1], son[l][0]);
        dist[l] = dist[son[l][1]] + 1;
    }
    return l;
}

int main() {
    n = geti();
    m = geti();
    for (int i = 1; i <= n; ++i) val[i] = geti();
    while (m--) {
        int op = geti();
        if (op == 1) {
            int x = geti(), y = geti();
            if (val[x] && val[y]) merge(root(x), root(y));
        } else {
            int x = geti();
            if (!val[x]) {
                puts("-1");
                continue;
            } else {
                int rt = root(x);
                putln(val[rt]);
                val[rt] = 0;
                dad[merge(son[rt][0], son[rt][1])] = 0;
            }
        }
    }
    return 0;
}
