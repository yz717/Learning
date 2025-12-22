#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
typedef pair<int, int> PII;
const int N = 2e3 + 10;
vector<PII> adj[N];
int dist[N];
int n, m;
bool bf() {
    memset(dist, 0x3f, sizeof(dist));
    dist[1] = 0;
    bool flag;
    for(int i = 1; i <= n; i++) {
        flag = false;
        for(int u = 1; u <= n; u++) {
            if(dist[u] == 0x3f3f3f3f) continue;
            for(auto& p : adj[u]) {
                int v = p.first, w = p.second;
                if(dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    flag = true;
                }
            }
        }
        if(!flag) return false;
    }
    return flag;
}

int main() {
    int T;
    cin >> T;
    while(T--) {
        cin >> n >> m;
        for(int i = 0; i <= n; i++) adj[i].clear();
        for(int i = 1; i <= m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].push_back({v, w});
            if(w >= 0) adj[v].push_back({u, w});
        }
        if(bf()) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}
