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

const int N = 1000010;
int n, k, q1[N], q2[N], h1 = 1, t1 = 0, h2 = 1, t2 = 0, a[N], a1[N], a2[N];

void push(int k) {
    while (h1 <= t1 && a[k] <= a[q1[t1]]) --t1;
    q1[++t1] = k;
    while (h2 <= t2 && a[k] >= a[q2[t2]]) --t2;
    q2[++t2] = k;
}

int main() {
    n = gi(), k = gi();
    for (int i = 1; i <= n; ++i) a[i] = gi();
    for (int i = 1; i < k; ++i) push(i);
    for (int i = k; i <= n; ++i) {
        push(i);
        while (h1 <= t1 && q1[h1] <= i - k) ++h1;
        a1[i] = a[q1[h1]];
        while (h2 <= t2 && q2[h2] <= i - k) ++h2;
        a2[i] = a[q2[h2]];
    }
    for (int i = k; i <= n; ++i) putsp(a1[i]);
    putchar('\n');
    for (int i = k; i <= n; ++i) putsp(a2[i]);
    putchar('\n');
    return 0;
}
