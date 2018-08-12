#include <bits/stdc++.h>
using namespace std;

int main() {
    unsigned long long b, p, k;
    cin >> b >> p >> k;
    cout << b << "^" << p << " mod " << k << "=";
    unsigned long long a = b % k, ans = 1;
    while (p) {
        if (p & 1) ans = (ans * a) % k;
        a = (a * a) % k;
        p >>= 1;
    }
    cout << ans % k << endl;
    return 0;
}
