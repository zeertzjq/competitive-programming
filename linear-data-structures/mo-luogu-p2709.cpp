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
inline void putsp(T x) {
    puti(x);
    putchar(' ');
}

template <typename T>
inline void putln(T x) {
    puti(x);
    putchar('\n');
}
//}}}

const int N = 50010;
int n, m, k, cnt[N], a[N], aans[N];

struct query {
    int id, l, r, idx;

    inline bool operator<(const query& rhs) {
        return id < rhs.id || (id == rhs.id && r < rhs.r);
    }
} q[N];

int main() {
    n = gi();
    m = gi();
    k = gi();
    int bs = sqrt(n);
    for (int i = 1; i <= n; ++i) a[i] = gi();
    for (int i = 1; i <= m; ++i) {
        int l = gi(), r = gi();
        q[i].id = l / bs;
        q[i].l = l;
        q[i].r = r;
        q[i].idx = i;
    }
    sort(q + 1, q + 1 + m);
    int lp = q[1].l, rp = lp;
    ++cnt[a[lp]];
    long long ans = 1;
    for (int i = 1; i <= m; ++i) {
        while (lp > q[i].l) ans += 2 * cnt[a[--lp]]++ + 1;
        while (rp < q[i].r) ans += 2 * cnt[a[++rp]]++ + 1;
        while (rp > q[i].r) ans -= 2 * --cnt[a[rp--]] + 1;
        while (lp < q[i].l) ans -= 2 * --cnt[a[lp++]] + 1;
        aans[q[i].idx] = ans;
    }
    for (int i = 1; i <= m; ++i) putln(aans[i]);
    return 0;
}
