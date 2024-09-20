#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
class mathbase{
public:
    constexpr auto phi(lint x){
        auto res=1ll;
        for(auto i=2ll;i*i<x+1;++i){
            auto nw=1ll,wx=0ll;
            while(!(x%i)) x/=i,wx=nw,nw*=i;
            res*=(nw-wx);
        }
        return res*(x-1?x-1:1);
    }
} math;
class segment{
private:
    struct node{
        lint sum,prod;
        auto mul(lint x){
            (sum*=x)%=MOD;(prod*=x)%=MOD;
        }
        node():sum(0),prod(1){}
    };
    vector<node> tr;
    vector<vector<int>> contains,sc;
    vector<int> px;
    constexpr auto ls(int u){return u*2;}
    constexpr auto rs(int u){return u*2+1;}
    auto push_down(int u){
        const auto cntp=(int)(px.size());
        tr[ls(u)].mul(tr[u].prod);
        tr[rs(u)].mul(tr[u].prod);
        cir(i,0,cntp) contains[ls(u)][i]|=contains[u][i];
        cir(i,0,cntp) contains[rs(u)][i]|=contains[u][i];
        cir(i,0,cntp) sc[ls(u)][i]|=sc[u][i];
        cir(i,0,cntp) sc[rs(u)][i]|=sc[u][i];
        tr[u].prod=1;
    }
    auto maintain(int u){
        const auto cntp=(int)(px.size());
        tr[u].sum=(tr[ls(u)].sum+tr[rs(u)].sum)%MOD;
        cir(i,0,cntp) contains[u][i]=contains[ls(u)][i]&contains[rs(u)][i];
        cir(i,0,cntp) sc[u][i]=(contains[ls(u)][i]==contains[rs(u)][i])&sc[ls(u)][i]&sc[rs(u)][i];
    }
    auto build(int u,int l,int r,vector<lint>&phx,vector<vector<int>>&cts){
        if(l==r){
            const auto cntp=(int)(px.size());
            tr[u].sum=phx[l];contains[u]=cts[l];
            fill(sc[u].begin(),sc[u].end(),true);
            return;
        }
        const auto mid=(l+r)/2;
        build(ls(u),l,mid,phx,cts);build(rs(u),mid+1,r,phx,cts);
        maintain(u);
    }
    auto update(int u,int l,int r,int ql,int qr,int id){
        // cerr<<l<<' '<<r<<' '<<ql<<' '<<qr<<'\n';
        if(r<ql||qr<l) return;
        if(ql-1<l&&r-1<qr&&sc[u][id]){
            tr[u].mul(px[id]-(!contains[u][id]));
            contains[u][id]=true;
            return;
        }
        const auto mid=(l+r)/2;
        push_down(u);
        update(ls(u),l,mid,ql,qr,id);
        update(rs(u),mid+1,r,ql,qr,id);
        maintain(u);
    }
    auto query(int u,int l,int r,int ql,int qr){
        if(r<ql||qr<l) return 0ll;
        if(ql-1<l&&r-1<qr) return tr[u].sum;
        const auto mid=(l+r)/2;
        push_down(u);
        return (query(ls(u),l,mid,ql,qr)+query(rs(u),mid+1,r,ql,qr))%MOD;
    }
    int n;
public:
    auto update(int l,int r,int id){
        update(1,0,n-1,l,r,id);
    }
    auto query(int l,int r){
        return query(1,0,n-1,l,r);
    }
    segment(int _n,vector<lint> phi,vector<vector<int>> cs,vector<int> p):
        n(_n),tr(_n<<2),px(p),contains(_n<<2,vector<int>(p.size())),sc(_n<<2,vector<int>(p.size())){
        build(1,0,_n-1,phi,cs);
    }
};
const auto arrp=vector{2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;vector<lint> px(n);
    vector contains(n,vector<int>(25));
    cir(i,0,n){
        cin>>px[i];
        cir(x,0,25) contains[i][x]=(!(px[i]%arrp[x]));
        px[i]=math.phi(px[i]);
    }
    segment sg(n,px,contains,arrp);
    cir(i,0,m){
        int op;cin>>op;
        if(!op){
            int l,r,w;cin>>l>>r>>w;--l;--r;
            cir(i,0,25) while(!(w%arrp[i])) sg.update(l,r,i),w/=arrp[i];
        }else{
            int l,r;cin>>l>>r;--l;--r;
            cout<<sg.query(l,r)<<'\n';
        }
    }
    return 0;
}
