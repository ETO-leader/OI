#include<bits/stdc++.h>
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define add(x, y) ((x + y >= mod) ? (x + y - mod) : (x + y))
#define dec(x, y) ((x - y < 0) ? (x - y + mod) : (x - y))
#define popcnt(x) __builtin_popcount(x)
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
using namespace std;
typedef __int128 __;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 5e5 + 10;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _infl=(int64_t)(1e12l);
class sp{
private:
    vector<int64_t> d;
    vector<int64_t> sd,td;
    vector<int> visd,ord,inq;
    queue<int> q;
    auto init(int s){
        const auto n=(int)(d.size());
        vector<int> vis(n);
        sd[s]=0;
        cir(i,0,min(400,n)){
            auto mns=pair(_infl,-1);
            cir(i,0,n) if(!vis[i]) mns=min(mns,{sd[i],i});
            const auto u=mns.second;
            vis[u]=true;
            cir(i,0,n) sd[(u+i)%n]=min(sd[(u+i)%n],sd[u]+d[i]);
        }
        ord.resize(n);
        iota(ord.begin(),ord.end(),0);
        sort(ord.begin(),ord.end(),[&](auto u,auto v){return d[u]<d[v];});
    }
public:
    auto calc(int t){
        const auto n=(int)(d.size());
        auto ans=sd[t];
        q.emplace(t);
        td[t]=0;
        cir(i,0,min(80,n)){
            if(q.empty()) break;
            const auto u=q.front();q.pop();
            q.emplace(u);
            inq[u]=false;
            cir(c,0,min(10,n)){
                const auto v=(u+n-ord[c])%n;
                if(td[v]>td[u]+d[ord[c]]){
                    td[v]=td[u]+d[ord[c]];
                    if(!inq[v]) q.emplace(v);
                    inq[v]=true;
                    ans=min(ans,td[v]+sd[v]);
                }
            }
        }
        while(!q.empty()) visd.emplace_back(q.front()),q.pop();
        for(auto&x:visd) inq[x]=false,td[x]=_infl;
        visd.clear();
        return ans;
    }
    sp(vector<int64_t> _d,int s):d(_d),sd(_d.size(),_infl),td(_d.size(),_infl),inq(_d.size()){init(s);}
};

int n, mn, p, cnt;
int a[N], d[N], id[N];
ll dis[N];
bool f[N], vis[N];
priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> Q;
bool End;
int main(){
	n = read();
	for(int i = 0; i < n; ++i)
	  a[i] = read();
	mn = a[0];
	for(int i = 1; i < n; ++i){
		if(a[i] < mn){
			mn = a[i];
			p = i;
		}
	}
	vector<int64_t> d;
	for(int i = 0; i < n; ++i)
	  d.push_back(a[(p + i) % n] - mn);
	sp spqwq(d, 0);
	for(int i = 0; i < n; ++i){
		write(1ll * mn * n + spqwq.calc(i));
		putchar(' ');
	}
	//cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}

