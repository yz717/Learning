#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
typedef pair<int, int> PII;
const int N = 5010;
const int INF = 0x3f3f3f3f;

int n, m;
vector<PII> edges[N];
int dist[N];
bool st[N];

int prim() {
    // 初始化距离为无穷大
    memset(dist, 0x3f, sizeof(dist));
    int ret = 0; // 最小生成树的总权值
    int cnt = 0; // 记录已经加入生成树的点数量
    // 小根堆：距离越小越在上面
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    // 从 1 号点开始
    dist[1] = 0;
    heap.push({0, 1}); // {距离, 点}
    while (heap.size()) {
        // 取出当前距离生成树最近的点
        auto t = heap.top();
        heap.pop();
        int distance = t.first;
        int u = t.second;
        // 如果这个点已经在生成树里了，跳过
        if (st[u]) continue;
        // 标记并累加
        st[u] = true;
        ret += distance;
        cnt++;
        // 扫描邻居，更新距离
        for (auto& p : edges[u]) {
            int v = p.first;
            int w = p.second;
            // 如果通过 u 到达 v 的距离比 v 当前记录的距离更短
            if (dist[v] > w) {
                dist[v] = w;
                heap.push({dist[v], v}); 
            }
        }
    }
    // 判断连通性：如果加入的点少于 n 个，说明图不连通
    if (cnt < n) return INF;
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
