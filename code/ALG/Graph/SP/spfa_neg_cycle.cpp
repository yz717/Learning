#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;
typedef pair<int, int> PII;
const int N = 2e3 + 10;
vector<PII> adj[N];
int dist[N];
bool st[N];
int cnt[N];
int n, m;
bool spfa() {
    memset(dist, 0x3f, sizeof(dist));
    memset(st, 0, sizeof(st));
    memset(cnt, 0, sizeof(cnt));
    queue<int> q;
    dist[1] = 0;
    q.push(1); st[1] = true;
    while(q.size()) {
        int u = q.front(); q.pop(); st[u] = false;
        for(auto&p : adj[u]) {
            int v = p.first, w = p.second;
            if(dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                cnt[v] = cnt[u] + 1;
                if(cnt[v] >= n) return true;
                if(!st[v]) q.push(v), st[v] = true;
            }
        }
    }
    return false;
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
        if(spfa()) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}
