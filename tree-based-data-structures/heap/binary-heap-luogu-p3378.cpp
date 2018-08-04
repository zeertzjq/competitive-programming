#include <bits/stdc++.h>
using namespace std;

inline int geti() {
    int x, f = 0;
    char c;
    while (!isdigit(c = getchar()))
        if (c == '-') f = 1;
    for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0')
        ;
    return f ? -x : x;
}

inline void puti(int x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) puti(x / 10);
    putchar(x % 10 + '0');
}

const int N = 1000000, INF = 2147483647;
int h[N + 1];

#define sz h[0]
#define lson (x << 1)
#define rson (x << 1 | 1)
#define dad (x >> 1)

bool leaf(int x) {
    return x << 1 > sz;
}

int minson(int x) {
    int l = lson <= sz ? h[lson] : INF, r = rson <= sz ? h[rson] : INF;
    return l < r ? lson : rson;
}

void heapup(int x) {
    while (x > 1 && h[dad] > h[x]) {
        swap(h[x], h[dad]);
        x >>= 1;
    }
}

void heapdown(int x) {
    int ms;
    while (!leaf(x) && h[x] > h[ms = minson(x)]) {
        swap(h[x], h[ms]);
        x = ms;
    }
}

int main() {
    int n = geti();
    while (n--)
        switch (geti()) {
            case 1:
                h[++sz] = geti();
                heapup(sz);
                break;
            case 2:
                puti(h[1]);
                putchar('\n');
                break;
            case 3:
                swap(h[1], h[sz--]);
                heapdown(1);
                break;
        }
    return 0;
}
