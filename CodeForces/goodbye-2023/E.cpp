#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
struct seg{
    int l,r;
    bool operator<(const seg&s) const{
        return l<s.l;
    }
    seg(int _l,int _r):l(_l),r(_r){}
};
template<typename T>
class segment{
private:
    vector<T> add,mx;
    static int ls(int u){return u*2;}
    static int rs(int u){return u*2+1;}
    auto push_down(int u){
        add[ls(u)]+=add[u];add[rs(u)]+=add[u];
        mx[ls(u)]+=add[u];mx[rs(u)]+=add[u];
        add[u]=0;
    }
    auto maintain(int u){
        mx[u]=max(mx[ls(u)],mx[rs(u)]);
    }
    auto update(int u,int l,int r,int ql,int qr,T x){
        if(ql-1<l&&r-1<qr)
            return add[u]+=x,mx[u]+=x,void();
        const auto mid=(l+r)/2;
        push_down(u);
        if(ql<mid+1) update(ls(u),l,mid,ql,qr,x);
        if(mid<qr) update(rs(u),mid+1,r,ql,qr,x);
        maintain(u);
    }
    auto query(int u,int l,int r,int ql,int qr){
        if(ql-1<l&&r-1<qr) return mx[u];
        const auto mid=(l+r)/2;
        push_down(u);T res=0;
        if(ql<mid+1)
            res=max(res,query(ls(u),l,mid,ql,qr));
        if(mid<qr)
            res=max(res,query(rs(u),mid+1,r,ql,qr));
        return maintain(u),res;
    }
    int n;
public:
    auto update(int l,int r,T x){
        //clog<<l<<' '<<r<<' '<<x<<'\n';
        update(1,1,n,l,r,x);
    }
    auto query(int l,int r){
        return query(1,1,n,l,r);
    }
    segment(int _n):n(_n),add(_n<<2),mx(_n<<2){}
};
vector<VI> G;
vector<int> col,inx,oux;
vector<set<seg>> sgs;
auto dfs(int u,segment<lint>&sg,
    int&cx,lint&ans,int f=0)->void{
    inx[u]=++cx;
    for(auto&i:G[u]) if(i!=f)
        dfs(i,sg,cx,ans,u);
    oux[u]=++cx;
    auto lb=sgs[col[u]].lower_bound({
        inx[u],114514});
    auto cplb=lb;
    for(;lb!=sgs[col[u]].end()&&
        lb->r<oux[u]+1;++lb){
        sg.update(lb->l,lb->r,-1);
    }
    sgs[col[u]].erase(cplb,lb);
    sgs[col[u]].insert({inx[u],oux[u]});
    sg.update(inx[u],oux[u],1);
    VI a;
    for(auto&i:G[u]) if(i!=f){
        a.push_back(sg.query(inx[i],oux[i]));
    }
    sort(a.begin(),a.end(),greater<lint>());
    lint res=1;
    if(a.size()) res=a[0];
    if(a.size()>1) res=max(res,a[0]*a[1]);
    ans=max(ans,res);
}
auto init(int n){
    G.clear();col.clear();inx.clear();
    sgs.clear();oux.clear();
    G.resize(n+1);col.resize(n+1);
    inx.resize(n+1);oux.resize(n+1);
    sgs.resize(n+1);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;init(n);
        cir(i,2,n+1){
            int f;cin>>f;
            G[f].push_back(i);
            G[i].push_back(f);
        }
        cir(i,1,n+1) cin>>col[i];
        segment<lint> sg(n*2+7);
        lint ans=1;
        int c=0;dfs(1,sg,c,ans);
        cout<<ans<<'\n';
    }
    return 0;
}
