#include <iostream>
#include <algorithm>
using namespace std;

const int N = 5010, M = 2e5 + 10, INF = 0x3f3f3f3f;
int n, m;
struct node{
    int x, y, z;
}a[M];
int fa[N];

int find(int x) {
    return x == fa[x] ? fa[x] : fa[x] = find(fa[x]);
}

int kk() {
    sort(a + 1, a + 1 + m, [](const node& a, const node& b) { return a.z < b.z; });
    int cnt = 0, ret = 0;
    for(int i = 1; i <= m; i++) {
        int fx = find(a[i].x);
        int fy = find(a[i].y);
        if(fx != fy) {
            cnt++;
            ret += a[i].z;
            fa[fx] = fy;
        }
    }
    return cnt == n - 1 ? ret : INF;
}

int main() {
    cin >> n >> m;
    for(int i = 1; i <= m; i++) cin >> a[i].x >> a[i].y >> a[i].z;
    for(int i = 1; i <= n; i++) fa[i] = i;
    int ret = kk();
    if(ret == INF) cout << "orz" << endl;
    else cout << ret << endl;
    return 0; 
}