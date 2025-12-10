#include <iostream>
using namespace std;
typedef long long LL;
const int N = 1e5 + 10;
int a[N], c[N];
int la, lc;
int b;

void div(int a[], int b, int c[]) {
    LL t = 0;
    for(int i = la - 1; i >= 0; i--) {
        t = t * 10 + a[i];
        c[i] = t / b;
        t %= b;
    }
    while(lc > 1 && c[lc - 1] == 0) lc--;
}

int main() {
    string x; cin >> x >> b;
    la = x.size();  lc = la;
    for(int i = 0; i < la; i++) a[la - 1 - i] = x[i] - '0';
    div(a, b, c);
    for(int i = lc - 1; i >= 0; i--) cout << c[i];
    return 0;
}