#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
class segment{
private:
    struct node{
        int mx,tag;
        auto update(auto w){
            mx+=w;tag+=w;
        }
        node():mx(0),tag(0){}
    };
    vector<node> tr;
    constexpr auto ls(auto u) const{return u*2;}
    constexpr auto rs(auto u) const{return u*2+1;}
    auto push_down(int u){
        tr[ls(u)].update(tr[u].tag);
        tr[rs(u)].update(tr[u].tag);
        tr[u].tag=0;
    }
    auto maintain(int u){
        tr[u].mx=max(tr[ls(u)].mx,tr[rs(u)].mx);
    }
    auto update(int u,int l,int r,int ql,int qr,auto w){
        if(r<ql||qr<l) return;
        if(ql-1<l&&r-1<qr) return tr[u].update(w);
        const auto mid=(l+r)/2;
        push_down(u);
        update(ls(u),l,mid,ql,qr,w);
        update(rs(u),mid+1,r,ql,qr,w);
        maintain(u);
    }
    const int n;
public:
    auto update(int l,int r,auto w){
        update(1,0,n-1,l,r,w);
    }
    auto query() const{
        return tr[1].mx;
    }
    segment(int _n):n(_n),tr(_n<<2){}
};
static constexpr auto maxv=(int)(8e4+7);
static constexpr auto valad=(int)(4e4);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int s,w;cin>>s>>w;
    int n;cin>>n;
    vector<vector<int>> pos(maxv);
    cir(i,0,n){
        int x,y;cin>>x>>y;x+=valad;y+=valad;
        pos[x].emplace_back(y);
    }
    segment sg(maxv);
    auto ans=0;
    cir(i,0,maxv){
        for(auto&x:pos[i]) sg.update(max(x-w,0),x,1);
        if(i-s-1>-1) for(auto&x:pos[i-s-1]) sg.update(max(x-w,0),x,-1);
        ans=max(ans,sg.query());
    }
    cout<<ans<<'\n';
    return 0;
}

