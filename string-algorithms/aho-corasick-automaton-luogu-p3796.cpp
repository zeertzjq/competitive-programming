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

const int S = 75, N = 155, W = N * S, T = 1000010;
int n, rt, head, tail, q[W], tot, c[W][26], fail[W], e[W], mcnt, cnt[N];
char s[N][S], t[T];

inline int mk() {
    fail[++tot] = 0;
    e[tot] = 0;
    fill(c[tot], c[tot + 26], 0);
    return tot;
}

inline void build(int n) {
    int cur = rt;
    for (int i = 0; s[n][i]; ++i) {
        char ch = s[n][i] - 'a';
        if (!c[cur][ch]) c[cur][ch] = mk();
        cur = c[cur][ch];
    }
    e[cur] = n;
}

inline void gfail() {
    head = tail = 0;
    fail[rt] = rt;
    for (int i = 0; i < 26; ++i)
        if (c[rt][i]) {
            fail[c[rt][i]] = rt;
            q[tail++] = c[rt][i];
        } else
            c[rt][i] = rt;
    while (head < tail) {
        int u = q[head++];
        for (int i = 0; i < 26; ++i)
            if (c[u][i]) {
                fail[c[u][i]] = c[fail[u]][i];
                q[tail++] = c[u][i];
            } else
                c[u][i] = c[fail[u]][i];
    }
}

int main() {
    while (n = gi()) {
        tot = 0;
        rt = mk();
        for (int i = 1; i <= n; ++i) {
            scanf("%s", s[i]);
            build(i);
        }
        gfail();
        scanf("%s", t);
        fill(cnt + 1, cnt + 1 + n, 0);
        mcnt = 0;
        int u = rt;
        for (int i = 0; t[i]; ++i) {
            u = c[u][t[i] - 'a'];
            for (int v = u; v != rt; v = fail[v])
                if (e[v]) mcnt = max(mcnt, ++cnt[e[v]]);
        }
        putln(mcnt);
        for (int i = 1; i <= n; ++i)
            if (cnt[i] == mcnt) printf("%s\n", s[i]);
    }
    return 0;
}
