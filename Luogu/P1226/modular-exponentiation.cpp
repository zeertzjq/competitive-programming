// vim: et sw=4 sts=4 fdm=marker
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long b, p, k;
    cin >> b >> p >> k;
    cout << b << "^" << p << " mod " << k << "=";
    long long a = b % k, ans = 1;
    for (; p; p >>= 1) p & 1 && (ans = ans * a % k), a = a * a % k;
    cout << ans % k << endl;
    return 0;
}
