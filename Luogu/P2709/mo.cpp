#include <bits/stdc++.h>
using namespace std;

//{{{
inline int gi() {
    int x, f = 0;
    char c;
    while (!isdigit(c = getchar())) c == '-' && (f = 1);
    for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0')
        ;
    return f ? -x : x;
}

inline long long gll() {
    int f = 0;
    long long x;
    char c;
    while (!isdigit(c = getchar())) c == '-' && (f = 1);
    for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0')
        ;
    return f ? -x : x;
}

template <typename T>
void puti(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) puti(x / 10);
    putchar(x % 10 + '0');
}

template <typename T>
inline void putsp(T x) {
    puti(x), putchar(' ');
}

template <typename T>
inline void putln(T x) {
    puti(x), putchar('\n');
}
//}}}

const int N = 50010;
int n, m, k, bs, cnt[N], a[N], ans[N];

struct query {
    int b, l, r, id;

    inline bool operator<(const query& rhs) const {
        return b == rhs.b ? r < rhs.r : b < rhs.b;
    }
} q[N];

int main() {
    n = gi(), m = gi(), k = gi(), bs = sqrt(n);
    for (int i = 1; i <= n; ++i) a[i] = gi();
    for (int i = 1; i <= m; ++i)
        q[i].l = gi(), q[i].r = gi(), q[i].b = q[i].l / bs, q[i].id = i;
    sort(q + 1, q + 1 + m);
    int lp = q[1].l, rp = lp;
    ++cnt[a[lp]];
    long long cur = 1;
    for (int i = 1; i <= m; ++i) {
        while (lp > q[i].l) cur += 2 * cnt[a[--lp]]++ + 1;
        while (rp < q[i].r) cur += 2 * cnt[a[++rp]]++ + 1;
        while (lp < q[i].l) cur -= 2 * --cnt[a[lp++]] + 1;
        while (rp > q[i].r) cur -= 2 * --cnt[a[rp--]] + 1;
        ans[q[i].id] = cur;
    }
    for (int i = 1; i <= m; ++i) putln(ans[i]);
    return 0;
}
