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

struct node {
    node *c[26];
    node *fail;
    int end;

    node() {
        fill(c, c + 26, (node *)NULL);
        fail = NULL;
        end = 0;
    }
};

const int S = 75, N = 155, T = 1000010;
node *rt, *q[N * S];
int n, head, tail, maxcnt, cnt[N];
char s[N][S], t[T];

void build(int n) {
    node *cur = rt;
    for (int i = 0; s[n][i]; ++i) {
        char c = s[n][i] - 'a';
        if (!cur->c[c]) cur->c[c] = new node();
        cur = cur->c[c];
    }
    cur->end = n;
}

void gfail() {
    head = tail = 0;
    rt->fail = rt;
    for (int i = 0; i < 26; ++i)
        if (rt->c[i]) {
            rt->c[i]->fail = rt;
            q[tail++] = rt->c[i];
        } else
            rt->c[i] = rt;
    while (head < tail) {
        node *u = q[head++];
        for (int i = 0; i < 26; ++i)
            if (u->c[i]) {
                u->c[i]->fail = u->fail->c[i];
                q[tail++] = u->c[i];
            } else
                u->c[i] = u->fail->c[i];
    }
}

int main() {
    while (n = geti()) {
        rt = new node();
        for (int i = 1; i <= n; ++i) {
            scanf("%s", s[i]);
            build(i);
        }
        gfail();
        scanf("%s", t);
        fill(cnt + 1, cnt + 1 + n, 0);
        maxcnt = 0;
        node *u = rt;
        for (int i = 0; t[i]; ++i) {
            u = u->c[t[i] - 'a'];
            for (node *v = u; v != rt; v = v->fail)
                if (v->end) maxcnt = max(maxcnt, ++cnt[v->end]);
        }
        putln(maxcnt);
        for (int i = 1; i <= n; ++i)
            if (cnt[i] == maxcnt) printf("%s\n", s[i]);
        for (int i = 0; i < tail; ++i) delete q[i];
    }
    return 0;
}
