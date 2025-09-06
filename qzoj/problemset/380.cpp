#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _inf=(int)(1e9+7);
class bst{
private:
    struct node{
        uint ls,rs,siz;lint w;
        node()=default;
        node(lint _w):ls(0),rs(0),siz(1),w(_w){}
    };
    static constexpr auto alpha=0.95;
    vector<node> tr;
    vector<lint> val;
    vector<uint> stc;
    uint cnt,p,root;
    auto&ls(auto u){return tr[u].ls;}
    auto&rs(auto u){return tr[u].rs;}
    auto newnode(auto w){
        ++cnt;tr[cnt]=node(w);
        return cnt;
    }
    auto destroy(uint u)->void{
        ls(u)?destroy(ls(u)):void();
        val[p]=tr[u].w;stc[p]=u;
        ++p;
        rs(u)?destroy(rs(u)):void();
    }
    auto rebuild(int l,int r)->uint{
        const auto mid=(l+r)>>1;
        const auto u=stc[mid];
        tr[u].w=val[mid];
        ls(u)=l>mid-1?0u:rebuild(l,mid-1);
        rs(u)=mid+1>r?0u:rebuild(mid+1,r);
        tr[u].siz=tr[ls(u)].siz+tr[rs(u)].siz+1;
        return u;
    }
    inline auto rebuild(uint u){
        p=0;
        destroy(u);
        return rebuild(0,p-1);
    }
    inline auto check(uint u){
        return max(tr[ls(u)].siz,tr[rs(u)].siz)*19>(tr[u].siz<<4);
    }
    auto emplace(uint&u,lint w){
        if(!u) return u=newnode(w),void();
        ++tr[u].siz;
        emplace(tr[u].w>w?ls(u):rs(u),w);
        u=check(u)?rebuild(u):u;
    }
    auto find_by_order(uint u,uint rk){
        const auto ulsiz=tr[ls(u)].siz+1;
        if(rk==ulsiz) return tr[u].w;
        return rk<ulsiz?find_by_order(ls(u),rk):find_by_order(rs(u),rk-ulsiz);
    }
    auto order_of_key(uint u,lint w){
        auto res=0u;
        while(u){
            tr[u].w>w?u=ls(u):(res+=tr[ls(u)].siz+1,u=rs(u));
        }
        return res;
    }
public:
    auto emplace(lint w){
        tr.emplace_back();
        val.emplace_back();
        stc.emplace_back();
        if(!root) root=newnode(w);
        else emplace(root,w);
    }
    auto order_of_key(lint w){
        return cnt?order_of_key(root,w):0;
    }
    auto find_by_order(uint rk){
        return find_by_order(root,rk);
    }
    bst():cnt(0),root(0),p(0),tr(1),val(1),stc(1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    bst qwq;
    qwq.emplace(-_inf);
    qwq.emplace(_inf);
    auto ans=0ll;
    cir(i,0,n){
        int x;cin>>x;
        if(i){
            const auto p=qwq.order_of_key(x);
            ans+=min(
                abs(qwq.find_by_order(p)-x),
                abs(qwq.find_by_order(p+1)-x)
            );
        }else{
            ans+=x;
        }
        qwq.emplace(x);
    }
    cout<<ans<<".00"<<'\n';
    return 0;
}
