#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("perm.in");
ofstream ouf("perm.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
uint64_t f(uint64_t x){
    x^=x<<13;
    x^=x>>7;
    x^=x<<17;
    return x;
}
class invaild{};
auto gauss(vector<vector<int>> a){
    const auto n=(int)(a.size());
    cir(i,0,n){
        auto p=i;
        while(p<(int)(a.size())&&(!(a[p][i]))) ++p;
        if(p==(int)(a.size())) continue;
        swap(a[i],a[p]);
        cir(x,i+1,n) if(a[x][i]){
            cir(j,i,n+1) a[x][j]^=a[i][j];
        }
    }
    vector<int> ans(n);
    for(auto i=n-1;~i;--i){
        auto cur=(int)(a[i][n]);
        auto ok=true;
        cir(j,i+1,n) if(ans[j]>-1) cur^=ans[j]*a[i][j]; else if(a[i][j]) ok=false;
        if((!ok)||(!a[i][i])) ans[i]=-1;
        else ans[i]=cur;
    }
    return make_pair(ans,a);
}
class base{
private:
    vector<uint64_t> b;
    static constexpr auto bx=64;
public: 
    auto emplace(uint64_t x){
        for(auto i=bx-1;~i;--i) if((x>>i)&1){
            if(b[i]){
                x^=b[i];
            }else{
                b[i]=x;
                return true;
            }
        }
        return false;
    }
    base():b(bx){}
};
static constexpr auto maxn=(int)(1e5+7);
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int T;inf>>T;
    vector<vector<uint64_t>> b(maxn,vector<uint64_t>(64));
    // b(i,w) 表示 r_(i-1) 的 w 位在 x 上的系数
    cir(i,0,64) b[0][i]=(uint64_t)(1)<<i;
    vector<uint64_t> bx;
    cir(i,1,maxn){
        bx=b[i-1];
        b[i]=b[i-1];
        cir(w,13,64) b[i][w]^=bx[w-13];
        bx=b[i];
        cir(w,0,57) b[i][w]^=bx[w+7];
        bx=b[i];
        cir(w,17,64) b[i][w]^=bx[w-17];
    }
    vector<vector<pair<uint64_t,int>>> pre(64);
    while(T--) [&]{
        int n;inf>>n;vector<int> p(n);
        for(auto&i:p) inf>>i;
        const auto px=p;
        vector<pair<int,int>> pos;
        sort(pos.begin(),pos.end());
        vector<int> r(n);
        vector<int> posx(n+1);
        cir(i,0,n) posx[p[i]]=i;
        for(auto i=n-1;~i;--i){
            r[i]=posx[i+1];
            posx[p[i]]=posx[i+1];
            swap(p[posx[i+1]],p[i]);
        }
        cir(i,0,n) pos.emplace_back(i+1,r[i]);
        p=px;
        auto chk=[&](uint64_t x){
            vector<int> a(n);
            iota(a.begin(),a.end(),1);
            cir(i,0,n) swap(a[i],a[(x=f(x))%(i+1)]);
            return a==p;
        };
        for(auto&i:pre) i.clear();
        base bx;
        vector<vector<int>> f(64,vector<int>(65));
        auto cnt=-1;
        vector<int> ax;
        for(auto&[p,px]:pos){
            const auto wx=(int)(log2(p&(-p)));
            cir(x,0,wx){
                ax.clear();
                cir(i,0,64) if((b[p][x]>>i)&1) ax.emplace_back(i);
                if(ax.empty()) continue;
                const auto c=ax.front();
                auto w=(uint64_t)(0);
                for(auto&i:ax) w|=(1ull<<i);
                if(!bx.emplace(w)) continue;
                ++cnt;
                for(auto&i:ax) f[cnt][i]=1;
                f[cnt][64]=((px>>x)&1);
                pre[c].emplace_back(w,(px>>x)&1);
            }
        }
        const auto[axf,qax]=gauss(f);
        if(!count(axf.begin(),axf.end(),-1)){
            auto ans=0ull;
            cir(i,0,64) if(axf[i]) ans|=(1ull<<i);
            ouf<<ans<<'\n';
            return;
        }
        for(auto&x:qax){
            auto w=0ull;
            auto lb=64;
            cir(i,0,64) if(x[i]) w|=(1ull<<i),lb=min(lb,i);
            if(!w) continue;
            pre[lb].emplace_back(w,x[64]);
        }
        auto dfs=[&](auto __self,int p,uint64_t cur){
            if(p<0){
                if(chk(cur)) throw cur;
                return;
            }
            if(!pre[p].empty()){
                vector<int> must(2);
                for(auto&[s,w]:pre[p]){
                    must[w^(__builtin_popcountll(cur&s)&1)]=true;
                    if(must[0]&&must[1]) return;
                }
                if(must[0]) __self(__self,p-1,cur);
                else __self(__self,p-1,cur|(1ull<<p));
            }else{
                __self(__self,p-1,cur);
                __self(__self,p-1,cur|(1ull<<p));
            }
        };
        try{
            dfs(dfs,63,0);
            abort();
        }catch(uint64_t ans){
            ouf<<ans<<'\n';
        }
    }();
    return 0;
}
