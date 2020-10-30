// vim: sw=4 ts=4 sts=4 et fdm=marker
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

const int N = 100010;

int n, m, c[N], sib[N], p[N], v[N];

int finds(int x) { return p[x] == x ? x : p[x] = finds(p[x]); }

inline int mrg(int x, int y) {
    if (!x || !y) return x | y;
    if (v[x] > v[y] || (v[x] == v[y] && x > y)) swap(x, y);
    sib[y] = c[x], c[x] = y, p[x] = p[y] = x;
    return x;
}

int mrgl(int l0) {
    if (!l0 || !sib[l0]) return p[l0] = l0;
    int l1 = sib[l0], l2 = sib[l1];
    sib[l0] = sib[l1] = 0;
    return mrg(mrg(l0, l1), mrgl(l2));
}

int main() {
    n = gi(), m = gi();
    for (int i = 1; i <= n; ++i) v[i] = gi(), p[i] = i;
    while (m--) {
        int op = gi();
        if (op == 1) {
            int x = gi(), y = gi();
            if (v[x] && v[y]) mrg(finds(x), finds(y));
        } else {
            int x = gi();
            if (!v[x]) {
                puts("-1");
                continue;
            } else {
                int rt = finds(x);
                putln(v[rt]), v[rt] = 0, p[rt] = mrgl(c[rt]);
            }
        }
    }
    return 0;
}
