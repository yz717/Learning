#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
typedef pair<int, int> PII;
const int N = 5010;
const int INF = 0x3f3f3f3f;

int n, m;
vector<PII> edges[N];
int dist[N];
bool st[N];

int prim() {
    memset(dist, 0x3f, sizeof(dist));
    dist[1] = 0;
    int ret = 0;
    for(int i = 1; i <= n; i++) {
        int t = 0;
        for(int j = 1; j <= n; j++)
            if(!st[j] && dist[j] < dist[t]) t = j;

        if(dist[t] == INF) return INF;
        st[t] = true;
        ret += dist[t];

        for(auto& p : edges[t]) {
            int v = p.first, w = p.second;
            dist[v] = min(dist[v], w);
        }
    }
    return ret;
}
int main() {
    cin >> n >> m;
    int x, y, z;
    while (m--)
    {
        cin >> x >> y >> z;
        // 可以不处理重边
        edges[x].push_back({y,z});
        edges[y].push_back({x,z});
    }

    int ret = prim();
    if(ret == INF) cout << "orz" << endl;
    else cout << ret << endl;
    return 0;
}
