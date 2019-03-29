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

const int N = 50;
int n;
long long b[N + 1];

int main() {
    n = gi();
    for (int i = 1; i <= n; ++i) {
        long long a = gll();
        for (int j = N; j >= 0; --j)
            if (a & 1LL << j) {
                if (b[j])
                    a ^= b[j];
                else {
                    b[j] = a;
                    break;
                }
            }
    }
    long long ans = 0;
    for (int i = N; i >= 0; --i) ans = max(ans, ans ^ b[i]);
    putln(ans);
    return 0;
}
