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

const int N = 1000010;
int len[N << 1], lk[N << 1], ch[N << 1][26], cnt[N << 1], idx[N << 1], clen[N], pre = 1, tot = 1;
char s[N];
long long ans = 0;

inline void sam(char c) {
    int x = ++tot;
    len[x] = len[pre] + 1;
    cnt[x] = 1;
    int p;
    for (p = pre; p && !ch[p][c]; p = lk[p]) ch[p][c] = x;
    if (p) {
        int q = ch[p][c];
        if (len[q] == len[p] + 1)
            lk[x] = q;
        else {
            int cq = ++tot;
            lk[cq] = lk[q];
            len[cq] = len[p] + 1;
            copy(ch[q], ch[q] + 26, ch[cq]);
            for (int i = p; i && ch[i][c] == q; i = lk[i]) ch[i][c] = cq;
            lk[q] = lk[x] = cq;
        }
    } else
        lk[x] = 1;
    pre = x;
}

int main() {
    scanf("%s", s);
    for (int i = 0; s[i]; ++i) sam(s[i] - 'a');
    for (int i = 1; i <= tot; ++i) ++clen[len[i]];
    for (int i = 1; clen[i]; ++i) clen[i] += clen[i - 1];
    for (int i = 1; i <= tot; ++i) idx[clen[len[i]]--] = i;
    for (int i = tot; i; --i) {
        int x = idx[i];
        cnt[lk[x]] += cnt[x];
        if (cnt[x] > 1) ans = max(ans, 1LL * cnt[x] * len[x]);
    }
    putln(ans);
    return 0;
}
