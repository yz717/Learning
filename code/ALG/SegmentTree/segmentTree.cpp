#include <iostream>
using namespace std;
// p << 1 等价于 p * 2，即左儿子
// p << 1 | 1 等价于 p * 2 + 1，即右儿子
#define lc p << 1
#define rc p << 1 | 1
typedef long long LL; 
const int N = 1e5 + 10; 

int a[N]; 
int n, m;
struct node {
    int l, r;   // 节点维护的区间范围 [l, r]
    LL sum;     // 区间和
    LL add;     // 懒标记（记录待下发的累加值）
} tr[N << 2];   // 线段树数组开 4 倍大小

// p: 当前节点索引, k: 要增加的数值
void lazy(int p, LL k) {
    // 更新当前节点的区间和
    tr[p].sum += (LL)(tr[p].r - tr[p].l + 1) * k;
    
    // 累加懒标记，暂不下发给子节点
    tr[p].add += k;
}

// 向上更新（Push Up）：用子节点的信息更新父节点
void pushup(int p) {
    tr[p].sum = tr[lc].sum + tr[rc].sum;
}

// 向下下发标记（Push Down）：在访问子节点前，把当前节点的懒标记传下去
void pushdown(int p) {
    if (tr[p].add) { // 如果有欠债（懒标记不为0）
        lazy(lc, tr[p].add); // 把债分给左儿子
        lazy(rc, tr[p].add); // 把债分给右儿子
        tr[p].add = 0;       // 标记清零
    }
}

// 建树
void build(int p, int l, int r) {
    tr[p] = {l, r, (LL)a[l], 0};
    
    if (l == r) return; // 叶子节点，递归结束

    int mid = (l + r) >> 1;
    build(lc, l, mid);      // 递归建左树
    build(rc, mid + 1, r);  // 递归建右树
    pushup(p);              // 回溯时更新当前节点的 sum
}

// 区间修改：将区间 [x, y] 内的所有数加上 k
void modify(int p, int x, int y, LL k) {
    int l = tr[p].l, r = tr[p].r;
    // 如果当前节点管理的区间完全包含在修改范围内
    if (x <= l && r <= y) {
        lazy(p, k); // 直接打标记并更新 sum，不再递归
        return;
    }
    // 如果没完全包含，先下发之前的标记，因为要深入子节点
    pushdown(p);
    int mid = (l + r) >> 1;
    // 判断是否需要递归左边
    if (x <= mid) modify(lc, x, y, k);
    // 判断是否需要递归右边
    if (mid + 1 <= y) modify(rc, x, y, k);
    // 子节点更新完了，记得更新父节点
    pushup(p);
}

// 区间查询：查询 [x, y] 的和
LL query(int p, int x, int y) {
    int l = tr[p].l, r = tr[p].r;
    // 如果当前区间完全在查询范围内，直接返回当前 sum
    if (x <= l && r <= y) {
        return tr[p].sum;
    }
    // 递归子节点，必须先下发懒标记
    pushdown(p);
    int mid = (l + r) >> 1;
    LL sum = 0;
    // 累加左半部分的查询结果
    if (x <= mid) sum += query(lc, x, y);
    // 累加右半部分的查询结果
    if (mid + 1 <= y) sum += query(rc, x, y);
    return sum;
}
