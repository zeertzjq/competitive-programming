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

const int N = 20;
const double eps = 1e-7;
int n;
double l, r, a[N];

inline double f(double x) {
    double ans = 0;
    for (int i = n; i >= 0; --i) ans = ans * x + a[i];
    return ans;
}

int main() {
    n = gi(), scanf("%lf%lf", &l, &r);
    for (int i = n; i >= 0; --i) scanf("%lf", a + i);
    while (r - l >= eps) {
        double m = (l + r) / 2;
        if (f(m - eps) < f(m + eps))
            l = m;
        else
            r = m;
    }
    printf("%.5lf\n", l);
    return 0;
}
