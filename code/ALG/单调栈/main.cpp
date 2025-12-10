#include <iostream>
#include <stack>
using namespace std;
const int N = 3e6 + 10;
int a[N];
int ret[N];
int n;


// 寻找当前元素左侧，离它最近，并且比它大的元素在哪
void test1() {
    stack<int> st;
    for(int i = 1; i <= n; i++) {
        while(st.size() && a[st.top()] <= a[i]) st.pop();
        if(st.size()) ret[i] = st.top();
        st.push(i);
    }
}

// 寻找当前元素左侧，离它最近，并且比它小的元素在哪
void test2() {
    stack<int> st;
    for(int i = 1; i <= n; i++) {
        while(st.size() && a[st.top()] >= a[i]) st.pop();
        if(st.size()) ret[i] = st.top();
        st.push(i);
    }
}

// 寻找当前元素右侧，离它最近，并且比它大的元素在哪
void test3() {
    stack<int> st;
    for(int i = n; i >= 1; i--) {
        while(st.size() && a[st.top()] <= a[i]) st.pop();
        if(st.size()) ret[i] = st.top();
        st.push(i);
    }
}

// 寻找当前元素右侧，离它最近，并且比它小的元素在哪
void test4() {
    stack<int> st;
    for(int i = n; i >= 1; i--) {
        while(st.size() && a[st.top()] >= a[i]) st.pop();
        if(st.size()) ret[i] = st.top();
        st.push(i);
    }
}

int main() {
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    test1();
    for(int i = 1; i <= n; i++) cout << ret[i] << " ";
    cout << endl;
    return 0;
}