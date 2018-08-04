#include <bits/stdc++.h>
using namespace std;

priority_queue<int, vector<int>, greater<int> > pq;

inline int geti() {
    int x, f = 0;
    char c;
    while (!isdigit(c = getchar()))
        if (c == '-') f = 1;
    for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0')
        ;
    return f ? -x : x;
}

inline int puti(int x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) puti(x / 10);
    putchar(x % 10 + '0');
}

int main() {
    int n = geti();
    while (n--)
        switch (geti()) {
            case 1:
                pq.push(geti());
                break;
            case 2:
                puti(pq.top());
                putchar('\n');
                break;
            case 3:
                pq.pop();
                break;
        }
    return 0;
}
