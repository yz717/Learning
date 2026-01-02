#include <iostream>
using namespace std;
const int N = 1e5 + 10;
int a[N], tr[N * 32][2];
int idx, n;

void insert(int x) {
    int cur = 0;
    for(int i = 31; i >= 0; i--) {
        int path = (x >> i) & 1;
        if(tr[cur][path] == 0) tr[cur][path] = ++idx;
        cur = tr[cur][path];
    }
}
int find(int x) {
    int cur = 0;
    int ret = 0;
    for(int i = 31; i >= 0; i--) {
        int path = (x >> i) & 1;
        if(tr[cur][path ^ 1]) {
            ret |= 1 << i;
            cur = tr[cur][path ^ 1];
        } else {
            cur = tr[cur][path];
        }
    }
    return ret;
}

int main() {
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        insert(a[i]);
    }
    int ret = 0;
    for(int i = 1; i <= n; i++) {
        ret = max(ret, find(a[i]));
    }
    cout << ret << endl;
    return 0;
}