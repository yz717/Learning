#include <iostream>
using namespace std;
const int N = 1e5 + 10;
int a[N], b[N], c[N];
int la, lb, lc;

void mul(int a[], int b[], int c[]) {
    for(int i = 0; i < la; i++) {
        for(int j = 0; j < lb; j++) {
            c[i + j] += a[i] * b[j];
        }
    }
    for(int i = 0; i < lc; i++) {
        c[i + 1] += c[i] / 10;
        c[i] %= 10;
    }
    while(lc > 1 && c[lc - 1] == 0) lc--;
}

int main() {
    string x, y; cin >> x >> y;
    la = x.size(); lb = y.size(); lc = la + lb;
    for(int i = 0; i < la; i++) a[la - 1 - i] = x[i] - '0';
    for(int i = 0; i < lb; i++) b[lb - 1 - i] = y[i] - '0';
    mul(a, b, c);
    for(int i = lc - 1; i >= 0; i--) cout << c[i];
    return 0;
}