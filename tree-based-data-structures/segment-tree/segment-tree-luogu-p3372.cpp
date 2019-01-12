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

const int N = 100010;
int n, m;
long long a[N], sgt[N << 2], addt[N << 2];

#define L (x << 1)
#define R (x << 1 | 1)

inline void push(int x, int l, int r) {
    if (!addt[x]) return;
    int m = (l + r) >> 1;
    sgt[L] += addt[x] * (m - l + 1);
    sgt[R] += addt[x] * (r - m);
    addt[L] += addt[x];
    addt[R] += addt[x];
    addt[x] = 0;
}

void add(int x, int l, int r, int ll, int rr, long long v) {
    if (l > rr || r < ll) return;
    if (l >= ll && r <= rr) {
        sgt[x] += v * (r - l + 1);
        addt[x] += v;
        return;
    }
    push(x, l, r);
    int m = (l + r) >> 1;
    add(L, l, m, ll, rr, v);
    add(R, m + 1, r, ll, rr, v);
    sgt[x] = sgt[L] + sgt[R];
}

long long qry(int x, int l, int r, int ll, int rr) {
    if (l > rr || r < ll) return 0;
    if (l >= ll && r <= rr) return sgt[x];
    push(x, l, r);
    int m = (l + r) >> 1;
    return qry(L, l, m, ll, rr) + qry(R, m + 1, r, ll, rr);
}

void build(int x, int l, int r) {
    if (l == r) {
        sgt[x] = a[l];
        return;
    }
    int m = (l + r) >> 1;
    build(L, l, m);
    build(R, m + 1, r);
    sgt[x] = sgt[L] + sgt[R];
}

int main() {
    n = gi();
    m = gi();
    for (int i = 1; i <= n; ++i) a[i] = gll();
    build(1, 1, n);
    while (m--) {
        int o = gi(), x = gi(), y = gi();
        if (o == 1)
            add(1, 1, n, x, y, gll());
        else
            putln(qry(1, 1, n, x, y));
    }
    return 0;
}
