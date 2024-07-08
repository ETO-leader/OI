#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;
typedef pair<int, int> PII;
const int maxn = 1005;

bool G[maxn][maxn];//判断能否一次到达
int n;
struct Diagonal{//待操作对角线
    int u, v;
}D[maxn];
PII steps[maxn * 20];//记录步骤
int tot;
struct Edge{//图上的边
    int v, next;
    bool st;
}e[maxn << 3];
int p[maxn], len;

void add(int u, int v){
    e[len] = (Edge){v, p[u], false}, p[u] = len ++;
}

int prev(int p){//找环上前一个点
    return p == 1 ? n : p - 1;
}

int next(int p){//找环上后一个点
    return p % n + 1;
}

void init(){
    memset(p, -1, sizeof p), len = 0;
    memset(G, 0, sizeof G);
    for (int i = 1; i <= n; i ++){
        int u = i, v = next(u);
        G[u][v] = G[v][u] = true;
        add(u, v), add(v, u);
    }
}

void getMethod(int &cnt, bool st){
    init();
    cnt = 0;
    queue<Diagonal> q;
    for (int i = 1, u, v; i <= n - 3; i ++){
        cin >> u >> v;
        add(u, v), add(v, u);
        if (u > v) swap(u, v);//钦定 u < v
        D[i] = (Diagonal){u, v}, G[u][v] = G[v][u] = true;
        if (u != 1 && v != 1) q.push(D[i]);//与 1 相连没必要再操作了
    }
    while (!q.empty()){
        Diagonal D = q.front();
        q.pop();
        int u = D.u, v = D.v;
        if (!G[u][1] || !G[v][1]){//不能与 1 构成三角形
            q.push(D); 
            continue;
        }
        int temp = -1, idx = -1;//另一个三角形的第三个顶点；决策对角线的索引（方便删除）
        for (int i = p[u]; ~i; i = e[i].next){
            int to = e[i].v;
            if (to == v && !e[i].st) idx = i;
            if (to >= v || e[i].st || to == 1){
                continue;
            }
            if (G[to][v]){
                temp = to;
                break;
            }
        }
        if (temp == -1){//找不到另一个合法三角形
            q.push(D); 
            continue;
        }
        /* 删除原对角线，加入新对角线，注意图中边和一步到达状态也要更改 */
        G[u][v] = G[v][u] = false;
        G[1][temp] = G[temp][1] = true;
        e[idx].st = e[idx ^ 1].st = true;
        add(1, temp), add(temp, 1);
        /* 插入操作。如果操作要反过来翻转的对角线就是决策中新的对角线 */
        steps[++ tot] = st ? make_pair(1, temp) : make_pair(u, v), cnt ++;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n;
    tot = 0;
    int cnt1 = 0, cnt2 = 0;
    /* now -> P1 */
    getMethod(cnt1, 0);
    /* now -> P2 */
    getMethod(cnt2, 1);
    
    /* out */
    cout << tot << endl;
    /* 原始状态到中继状态的操作方案 */
    for (int i = 1; i <= cnt1; i ++){
        cout << steps[i].first << ' ' << steps[i].second << endl;
    }
    /* 中继状态到最终状态的操作方案 注意操作步骤要反过来 */
    for (int i = tot; i > cnt1; i --){
        cout << steps[i].first << ' ' << steps[i].second << endl;
    }
    return 0;
}