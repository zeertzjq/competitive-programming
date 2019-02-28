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
inline void putsp(T x) {
    puti(x);
    putchar(' ');
}

template <typename T>
inline void putln(T x) {
    puti(x);
    putchar('\n');
}
//}}}

const int N = 40010;
int tail = 0, ext[N], orig[N];
char s0[N], s[N];

void manacher() {
    int pos = 1, r = 1;
    for (int i = 2; i <= tail; ++i) {
        if (i < r) ext[i] = min(ext[(pos << 1) - i], r - i);
        while (s[i + ext[i] + 1] == s[i - ext[i] - 1]) ++ext[i];
        if (i + ext[i] > r) {
            r = i + ext[i];
            pos = i;
        }
    }
}

int main() {
    s[tail] =
        '/';  // IMPORTANT: the first character must NOT be a null character
    s[++tail] = '.';
    char c;
    int olen = 0;
    while ((c = getchar()) != EOF) {
        s0[++olen] = c;
        if (isalpha(c)) {
            s[++tail] = tolower(c);
            orig[tail] = olen;
            s[++tail] = '.';
        }
    }
    manacher();
    int mid = max_element(ext + 1, ext + tail + 1) - ext;
    putln(ext[mid]);
    int l, r, dist = ext[mid] / 2;
    if (orig[mid]) {
        l = orig[mid] - 1;
        r = orig[mid] + 1;
    } else {
        l = orig[mid - 1];
        r = orig[mid + 1];
    }
    for (int i = 1; i <= dist; ++i, --l)
        while (!isalpha(s0[l])) --l;
    for (int i = 1; i <= dist; ++i, ++r)
        while (!isalpha(s0[r])) ++r;
    s0[r] = '\0';
    puts(s0 + l + 1);
    return 0;
}
