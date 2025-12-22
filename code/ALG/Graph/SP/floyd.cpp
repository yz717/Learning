#include <iostream>
#include <cstring>
using namespace std;
const int N = 110;
int n, m;
int f[N][N];
int main() {
    cin >> n >> m;
    memset(f, 0x3f, sizeof(f));
    for(int i = 1; i <= n; i++) f[i][i] = 0;
    int u, v, w;
    for(int i = 1; i <= m; i++) {
        cin >> u >> v >> w;
        f[u][v] = f[v][u] = min(f[u][v], w);
    }

    for(int k = 1; k <= n; k++) 
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++) 
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
    
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cout << f[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}