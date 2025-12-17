#include <iostream>
#include <deque>
const int N = 1e6 + 10;
int n, m;
int a[N];
using namespace std;

int main() {
    cin >> n >> m;
    deque<int> q;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        while(q.size() && a[q.back()] >= a[i]) q.pop_back();
        q.push_back(i);
        if(q.back() - q.front() + 1 > m) q.pop_front();
        if(i >= m) cout << a[q.front()] << endl;
    }
    return 0;
}



