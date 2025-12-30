#include <iostream>
#include <string>
using namespace std;
const int N = 2e6 + 10;
int pi[N];
string s, t;
int n, m;
int main() {
    cin >> s >> t;
    n = s.size(), m = t.size();
    s = ' ' + t + '#' + s;
    for(int i = 2, j = 0; i <= n + m + 1; i++) {
        // int j = pi[i - 1];
        while(j && s[i] != s[j + 1]) j = pi[j];
        if(s[i] == s[j + 1]) j++;
        pi[i] = j;
        if(j == m) {
            cout << i - 2 * m << endl;
        }
    }
    for(int i = 1; i <= m; i++) cout << pi[i] << " ";
    return 0;
}