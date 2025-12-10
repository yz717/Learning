#include <iostream>
using namespace std;
typedef long long LL;
#define lc p << 1
#define rc p << 1 | 1
const int N = 1e5 + 10;

struct node {
    int l, r;
    LL sum;
    int turn;
}tr[N << 2];

int n, m;
void pushup(int p) {
    tr[p].sum = tr[lc].sum + tr[rc].sum;
}
void build(int p, int l, int r) {
    tr[p] = {l, r, 0, 0};
    if(l == r) return;
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(p);
}

void lazy(int p) {
    int l = tr[p].l, r = tr[p].r;
    tr[p].sum = (r - l + 1) - tr[p].sum;
    tr[p].turn ^= 1;
}
void pushdown(int p) {
    if(tr[p].turn) {
        lazy(lc);
        lazy(rc);
        tr[p].turn = 0;
    }
}
void modify(int p, int x, int y) {
    int l = tr[p].l, r = tr[p].r;
    if(x <= l && r <= y) {
        lazy(p);
        return;
    }

    pushdown(p);
    int mid = (l + r) >> 1;
    if(x <= mid) modify(lc, x, y);
    if(mid + 1 <= y) modify(rc, x, y);  
    pushup(p);
}
int query(int p, int x, int y) {
    int l = tr[p].l, r = tr[p].r;
    if(x <= l && r <= y) return tr[p].sum;
    pushdown(p);
    int mid = (l + r) >> 1;
    int ret = 0;
    if(x <= mid) ret += query(lc, x, y);
    if(mid + 1 <= y) ret += query(rc, x, y);
    return ret;
}

int main() {
    cin >> n >> m;
    build(1, 1, n);
    while(m--) {
        int c, a, b;
        cin >> c >> a >> b;
        if( c == 0) modify(1, a, b);
        else cout << query(1, a, b) << endl;
    }
}

