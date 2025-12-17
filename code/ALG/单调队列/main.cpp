#include <iostream>
#include <deque>
const int N = 1e6 + 10;
int n, k;
int a[N];
using namespace std;

int main() {
    cin >> n >> k;
    for(int i = 1; i <= n; i++) cin >> a[i];
    deque<int> q;
    for(int i = 1; i <= n; i++) {
        while(q.size() && a[q.back()] >= a[i]) q.pop_back();
        q.push_back(i);
        if(q.back() - q.front() + 1 > k) q.pop_front();
        if(i >= k) cout << a[q.front()] << " ";
    }
    cout << endl;
    q.clear();
    for(int i = 1; i <= n; i++) {
        while(q.size() && a[q.back()] <= a[i]) q.pop_back();
        q.push_back(i);
        if(q.back() - q.front() + 1 > k) q.pop_front();
        if(i >= k) cout << a[q.front()] << " ";
    }
    cout << endl;
    return 0;
}