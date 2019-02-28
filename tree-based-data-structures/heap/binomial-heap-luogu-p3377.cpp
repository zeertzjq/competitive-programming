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

const int N = 100010;

int val[N], chd[N], dad[N], sb1[N], sb0[N], deg[N], n, m;

inline int merge(int h1, int h2) {
    if (h1 == h2) return h1;
    int ret = deg[h1] > deg[h2] ? h2 : h1;
    int last = 0;
    while (h1 && h2) {
        if (deg[h1] > deg[h2]) swap(h1, h2);
        sb1[h1] = last;
        dad[h1] = 0;
        if (last) sb0[last] = h1;
        last = h1;
        h1 = sb0[h1];
    }
    if (h1 || h2) {
        sb1[h1 + h2] = last;
        if (last) sb0[last] = h1 + h2;
        for (int i = h1 + h2; i; i = sb0[i])
            dad[i] = 0;  // IMPORTANT: the root node of a binomial tree must
                         // have NO parent
    }
    return ret;
}

inline void adjust(int l) {
    int m = sb0[l], r = sb0[m];
    if (!m) return;
    while (l && m) {
        if (deg[l] == deg[m] && !(r && deg[r] == deg[m])) {
            if (val[l] < val[m] ||
                (val[l] == val[m] &&
                 l < m)) {  // IMPORTANT: if the root nodes of the two binomial
                            // trees to be merged have identical values, the one
                            // whose index is SMALLER should be the new root
                swap(sb0[l], sb0[m]);
                swap(sb1[l], sb1[m]);
                swap(l, m);
            }
            dad[l] = m;
            sb0[l] = chd[m];
            sb1[chd[m]] = l;
            chd[m] = l;
            ++deg[m];  // IMPORTANT: update the degree of the new binomial tree
            sb1[m] = sb1[l];
            if (sb1[m]) sb0[sb1[m]] = m;
            sb1[l] = 0;
            if (sb0[m]) sb1[sb0[m]] = m;  // IMPORTANT: update siblings
        }
        l = m;
        m = r;
        r = sb0[r];
    }
}

inline int head(int x) {
    while (dad[x]) x = dad[x];
    while (sb1[x]) x = sb1[x];
    return x;
}

inline int hmin(int h) {
    int ret = h;
    for (h = sb0[h]; h; h = sb0[h])
        if (val[h] < val[ret])
            ret = h;
        else if (val[h] == val[ret] &&
                 h < ret)  // IMPORTANT: if there are multiple minimum values in
                           // the heap, the found node should also have the
                           // smallest possible index
            ret = h;
    return ret;
}

int main() {
    n = gi();
    m = gi();
    for (int i = 1; i <= n; ++i) val[i] = gi();
    while (m--)
        if (gi() == 1) {
            int x = gi(), y = gi();
            if (val[x] && val[y]) adjust(merge(head(x), head(y)));
        } else {
            int x = gi();
            if (!val[x]) {
                puts("-1");
                continue;
            } else {
                int h = head(x);
                int m = hmin(h);
                if (m == h)
                    h = sb0[m];  // IMPORTANT: the node with the minimum value
                                 // will NO LONGER be in the heap and thus
                                 // CANNOT represent the heap
                putln(val[m]);
                val[m] = 0;
                if (sb1[m]) sb0[sb1[m]] = sb0[m];
                if (sb0[m]) sb1[sb0[m]] = sb1[m];  // IMPORTANT: update siblings
                adjust(merge(h, chd[m]));
            }
        }
    return 0;
}
