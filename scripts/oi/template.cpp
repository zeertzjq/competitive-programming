#include <bits/stdc++.h>
using namespace std;

int geti() {
    int x, f = 0;
    char c;
    while (!isdigit(c = getchar()))
        if (c == '-') f = 1;
    for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0')
        ;
    return f ? -x : x;
}

void puti(int x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) puti(x / 10);
    putchar(x % 10 + '0');
}

long long getll() {
    int f = 0;
    long long x;
    char c;
    while (!isdigit(c = getchar()))
        if (c == '-') f = 1;
    for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0')
        ;
    return f ? -x : x;
}

void putll(long long x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) putll(x / 10);  // IMPORTANT: DON'T use puti
    putchar(x % 10 + '0');
}

int main() {
    freopen("%%.in", "r", stdin);
    freopen("%%.out", "w", stdout);

    fclose(stdin);
    fclose(stdout);
    return 0;
}
