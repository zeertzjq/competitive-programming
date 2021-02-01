// vim: et sw=4 sts=4 fdm=marker
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

const int N = 100010, inf = ~0U >> 1;
const double eps = 1e-5;
int n;
double m[N], mls[N], mrs[N];

inline bool ck(double avg) {
    mls[1] = m[1] - avg, mrs[n] = m[n] - avg;
    double s = m[1] - avg;
    for (int i = 2; i <= n; ++i) s += m[i] - avg, mls[i] = min(mls[i - 1], s);
    s = m[n] - avg;
    for (int i = n - 1; i; --i) s += m[i] - avg, mrs[i] = min(mrs[i + 1], s);
    double ms = mls[1] + mrs[n];
    for (int i = 2; i < n; ++i) ms = min(ms, mls[i - 1] + mrs[i + 1]);
    return ms <= 0;
}

int main() {
    n = gi();
    double l = inf, r = 0;
    for (int i = 1; i <= n; ++i)
        m[i] = gi(), l = min(l, m[i]), r = max(r, m[i]);
    while (r - l >= eps) {
        double mid = (l + r) / 2;
        if (ck(mid))
            r = mid;
        else
            l = mid;
    }
    printf("%.3f\n", l);
    return 0;
}
