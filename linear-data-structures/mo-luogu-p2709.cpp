#include <bits/stdc++.h>
using namespace std;

const int N = 50010;

inline int geti() {
    int x, f = 0;
    char c;
    while (!isdigit(c = getchar()))
        if (c == '-') f = 1;
    for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0')
        ;
    return f ? -x : x;
}

void puti(long long x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) puti(x / 10);
    putchar(x % 10 + '0');
}

int n, m, k;
int cnt[N];
int a[N];

struct query {
    int id, l, r, idx;

    inline bool operator<(const query& rhs) {
        return id < rhs.id || (id == rhs.id && r < rhs.r);
    }
} q[N];

int aans[N];

int main() {
    n = geti();
    m = geti();
    k = geti();
    int bs = sqrt(n);
    for (int i = 1; i <= n; ++i) a[i] = geti();
    for (int i = 1; i <= m; ++i) {
        int l = geti(), r = geti();
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
    for (int i = 1; i <= m; ++i) {
        puti(aans[i]);
        putchar('\n');
    }
    return 0;
}