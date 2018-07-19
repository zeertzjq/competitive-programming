#include <bits/stdc++.h>
using namespace std;

int geti() {
    int x, f = 0;
    char c;
    while (!isdigit(c = getchar()))
        if (c == '-') f = 1;
    for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0')
        ;
    return f ? -x : x;
}

void puti(int x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) puti(x / 10);
    putchar(x % 10 + '0');
}

long long getll() {
    long long x;
    int f = 0;
    char c;
    while (!isdigit(c = getchar()))
        if (c == '-') f = 1;
    for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0')
        ;
    return f ? -x : x;
}

void putll(long long x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) putll(x / 10);
    putchar(x % 10 + '0');
}

const int N = 50010;
int n, m;
struct query {
    bool tp;
    int l, r;
    long long c;
    int aidx;
} q[N], q1[N], q2[N];
int ans[N];
int aidx = 0;

long long sum[N << 2], tag[N << 2];
bool dirty[N << 2];

void upd(int p) {
    sum[p] = sum[p << 1] + sum[p << 1 | 1];
}

void push(int p, int l, int r) {
    if (dirty[p]) {
        dirty[p << 1] = dirty[p << 1 | 1] = 1;
        dirty[p] = sum[p << 1] = sum[p << 1 | 1] = tag[p << 1] = tag[p << 1 | 1] = 0;
    }
    if (tag[p]) {
        int m = (l + r) >> 1;
        // IMPORTANT: multiply by length
        sum[p << 1] += tag[p] * (m - l + 1);
        sum[p << 1 | 1] += tag[p] * (r - m);
        tag[p << 1] += tag[p];
        tag[p << 1 | 1] += tag[p];
        tag[p] = 0;
    }
}

void add(int p, int l, int r, int ml, int mr) {
    if (l > r) return;
    if (mr < l || ml > r) return;
    if (ml <= l && mr >= r) {
        sum[p] += r - l + 1;  // IMPORTANT: DON'T use ++sum[p]
        ++tag[p];
        return;
    }
    push(p, l, r);
    int m = (l + r) >> 1;
    add(p << 1, l, m, ml, mr);
    add(p << 1 | 1, m + 1, r, ml, mr);
    upd(p);
}

long long query(int p, int l, int r, int ql, int qr) {
    if (l > r) return 0;
    if (qr < l || ql > r) return 0;
    if (ql <= l && qr >= r) return sum[p];
    push(p, l, r);
    int m = (l + r) >> 1;
    return query(p << 1, l, m, ql, qr) + query(p << 1 | 1, m + 1, r, ql, qr);
}

void solve(int ql, int qr, int l, int r) {
    if (ql > qr || l > r) return;
    if (l == r) {
        for (int i = ql; i <= qr; ++i)
            if (q[i].tp) ans[q[i].aidx] = l;
        return;
    }
    int m = (l + r) >> 1;
    int p1 = 0, p2 = 0;
    tag[1] = sum[1] = 0;
    dirty[1] = 1;
    for (int i = ql; i <= qr; ++i)
        if (!q[i].tp) {
            if (q[i].c > m) {
                add(1, 1, n, q[i].l, q[i].r);
                q2[++p2] = q[i];
            } else
                q1[++p1] = q[i];
        } else {
            long long more = query(1, 1, n, q[i].l, q[i].r);  // IMPORTANT: DON'T use int
            if (q[i].c > more) {
                q[i].c -= more;
                q1[++p1] = q[i];
            } else
                q2[++p2] = q[i];
        }
    copy(q1 + 1, q1 + 1 + p1, q + 1);
    copy(q2 + 1, q2 + 1 + p2, q + 1 + p1);
    solve(1, p1, l, m);
    solve(p1 + 1, p1 + p2, m + 1, r);
}

int main() {
    n = geti();
    m = geti();
    for (int i = 1; i <= m; ++i) {
        q[i].tp = geti() - 1;
        q[i].l = geti();
        q[i].r = geti();
        q[i].c = q[i].tp ? getll() : geti();
        q[i].aidx = q[i].tp ? ++aidx : 0;
    }
    solve(1, m, -n, n);
    for (int i = 1; i <= aidx; ++i) {
        puti(ans[i]);
        printf("\n");
    }
    return 0;
}
