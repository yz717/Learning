#include <iostream>
#include <cstring>
using namespace std;
const int N = 5010;
const int INF = 0x3f3f3f3f;
int n,m;
int edges[N][N];
int dist[N];
bool st[N];

int prim() {
    memset(dist, 0x3f, sizeof(dist));
    int ret = 0;
    dist[1] = 0; // 随便选一个开始 

    // 选 n 个点
    for(int i = 1; i <= n; i++) {
        // 选距离最小的点
        int t = 0; // 标记最小的点
        for(int j = 1; j <= n; j++) 
            if(!st[j] && dist[j] < dist[t]) t = j;
        // 判断 t 是否可达
        if(dist[t] == INF) return INF;
        st[t] = true; // 标记已加入
        ret += dist[t];

        // 更新最小距离
        for(int j = 1; j <= n; j++) 
            dist[j] = min(dist[j], edges[t][j]);
    }
    return ret;
}

int main() {
    memset(edges, 0x3f, sizeof(edges));
    cin >> n >> m;
    int x, y, z;
    while(m--) {
        cin >> x >> y >> z;
        // 需要处理重边
        edges[x][y] = edges[y][x] = min(edges[x][y], z);
    }
    int ret = prim();
    if(ret == INF) cout << "orz" << endl;
    else cout << ret << endl;
    return 0;
}
