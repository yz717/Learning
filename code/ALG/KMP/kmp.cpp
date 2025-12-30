#include <iostream>
#include <string>
using namespace std;
const int N = 1e6 + 10;
string s, t;
int ne[N];
int n, m;
int main() {
    cin >> s >> t;
    n = s.size(), m = t.size();
    s = ' ' + s; t = ' ' + t;
    for(int i = 2; i <= m; i++) {
        int j = ne[i - 1];
        while(j && t[i] != t[j + 1]) j = ne[j];
        if(t[i] == t[j + 1]) j++;
        ne[i] = j;
    }
    for(int i = 1, j = 0; i <= n; i++) {
        while(j && s[i] != t[j + 1]) j = ne[j];
        if(s[i] == t[j + 1]) j++;
        if(j == m) {
            cout << i - m + 1 << endl;
        }
    }
    for(int i = 1; i <= m; i++) cout << ne[i] << " ";
    return 0;
}