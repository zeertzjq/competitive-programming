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

const int N = 22000010;
int tail = 0, ext[N];
char s[N];

void manacher() {
    int pos = 1, r = 1;
    for (int i = 2; i <= tail; ++i) {
        if (i < r) ext[i] = min(ext[(pos << 1) - i], r - i);
        while (s[i + ext[i] + 1] == s[i - ext[i] - 1]) ++ext[i];
        if (i + ext[i] > r) r = i + ext[i], pos = i;
    }
}

int main() {
    s[tail] = '/';
    s[++tail] = '.';
    char c;
    while (!islower(c = getchar()))
        ;
    do
        s[++tail] = c, s[++tail] = '.';
    while (islower(c = getchar()));
    manacher(), putln(*max_element(ext + 1, ext + tail + 1));
    return 0;
}
