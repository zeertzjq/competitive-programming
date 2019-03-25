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

const int N = 1010, inf = ~0U >> 1;
const double eps = 1e-15;
int seed = 19260817, n, x[N], y[N], w[N];
double ax = 0, ay = 0, af = INFINITY, r = 0.997;

inline int ran() { return seed = (seed * 1103515245LL + 12345LL) & inf; }

inline double sqr(double x) { return x * x; }

inline double f(double x0, double y0) {
    double ans = 0;
    for (int i = 1; i <= n; ++i)
        ans += sqrt(sqr(x0 - x[i]) + sqr(y0 - y[i])) * w[i];
    return ans;
}

inline void sa() {
    double t = 2333, x0 = ax, y0 = ay;
    while (t > eps) {
        double x = x0 + t * (ran() - (inf >> 1)),
               y = y0 + t * (ran() - (inf >> 1)), nf = f(x, y), d = nf - af;
        if (d < 0)
            ax = x0 = x, ay = y0 = y, af = nf;
        else if (exp(-d / t) * inf > ran())
            x0 = x, y0 = y;
        t *= r;
    }
}

int main() {
    n = gi();
    for (int i = 1; i <= n; ++i) x[i] = gi(), y[i] = gi(), w[i] = gi();
    sa(), sa(), sa();
    printf("%.3lf %.3lf\n", ax, ay);
    return 0;
}
