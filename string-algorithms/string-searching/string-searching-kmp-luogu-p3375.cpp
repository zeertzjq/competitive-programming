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

const int N = 1000010;
char s1[N], s2[N];
int fail[N], len1, len2;

int main() {
    scanf("%s", s1 + 1);
    scanf("%s", s2 + 1);
    len1 = strlen(s1 + 1);
    len2 = strlen(s2 + 1);
    fail[0] = -1;
    for (int i = 1; i <= len2; ++i) {
        int j = fail[i - 1];
        while (j >= 0 && s2[j + 1] != s2[i]) j = fail[j];
        fail[i] = j + 1;
    }
    for (int i = 1, j = 0; i <= len1; ++i) {
        while (j >= 0 && s2[j + 1] != s1[i]) j = fail[j];
        if (++j == len2) putln(i - len2 + 1);
    }
    for (int i = 1; i <= len2; ++i) putsp(fail[i]);
    putchar('\n');
    return 0;
}
