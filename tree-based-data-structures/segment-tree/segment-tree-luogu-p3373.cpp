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
int n, m, p;
long long a[N], sgt[N << 2], addt[N << 2], mult[N << 2];

#define L (x << 1)
#define R (x << 1 | 1)

inline void push(int x, int l, int r) {
    if (!addt[x] && mult[x] == 1) return;
    int m = (l + r) >> 1;
    sgt[L] = (sgt[L] * mult[x] + addt[x] * (m - l + 1)) % p;
    sgt[R] = (sgt[R] * mult[x] + addt[x] * (r - m)) % p;
    addt[L] = (addt[L] * mult[x] + addt[x]) % p;
    addt[R] = (addt[R] * mult[x] + addt[x]) % p;
    mult[L] = (mult[L] * mult[x]) % p;
    mult[R] = (mult[R] * mult[x]) % p;
    addt[x] = 0;
    mult[x] = 1;  // IMPORTANT: reset mult[x] to 1
}

void add(int x, int l, int r, int ll, int rr, long long v) {
    if (l > rr || r < ll) return;
    if (l >= ll && r <= rr) {
        sgt[x] = (sgt[x] + v * (r - l + 1)) % p;
        addt[x] = (addt[x] + v) % p;
        return;
    }
    push(x, l, r);
    int m = (l + r) >> 1;
    add(L, l, m, ll, rr, v);
    add(R, m + 1, r, ll, rr, v);
    sgt[x] = (sgt[L] + sgt[R]) % p;
}

void mul(int x, int l, int r, int ll, int rr, long long v) {
    if (l > rr || r < ll) return;
    if (l >= ll && r <= rr) {
        sgt[x] = (sgt[x] * v) % p;
        addt[x] = (addt[x] * v) % p;
        mult[x] = (mult[x] * v) % p;
        return;
    }
    push(x, l, r);
    int m = (l + r) >> 1;
    mul(L, l, m, ll, rr, v);
    mul(R, m + 1, r, ll, rr, v);
    sgt[x] = (sgt[L] + sgt[R]) % p;
}

long long qry(int x, int l, int r, int ll, int rr) {
    if (l > rr || r < ll) return 0;
    if (l >= ll && r <= rr) return sgt[x];
    push(x, l, r);
    int m = (l + r) >> 1;
    return (qry(L, l, m, ll, rr) + qry(R, m + 1, r, ll, rr)) % p;
}

void build(int x, int l, int r) {
    mult[x] = 1;  // IMPORTANT: initialize mult[x] to 1
    if (l == r) {
        sgt[x] = a[l];
        return;
    }
    int m = (l + r) >> 1;
    build(L, l, m);
    build(R, m + 1, r);
    sgt[x] = (sgt[L] + sgt[R]) % p;
}

int main() {
    n = gi();
    m = gi();
    p = gi();
    for (int i = 1; i <= n; ++i) a[i] = gll() % p;
    build(1, 1, n);
    while (m--) {
        int o = gi(), x = gi(), y = gi();
        if (o == 1)
            mul(1, 1, n, x, y, gll() % p);
        else if (o == 2)
            add(1, 1, n, x, y, gll() % p);
        else
            putln(qry(1, 1, n, x, y));
    }
    return 0;
}
