#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class node{
public:
    array<array<int,2>,2> fu,fs;
    auto operator*(const node nd) const{
        auto res=node();
        cir(lw,0,2) cir(rw,0,2){
            res.fu[lw][rw]=max({
                nd.fu[lw][rw],
                fu[lw][0]+nd.fu[1][rw],
                fu[lw][1]+nd.fu[0][rw],
                fu[lw][0]+nd.fu[0][rw]
            });
            res.fs[lw][rw]=max({
                nd.fs[lw][rw],
                fs[lw][0]+nd.fu[1][rw],
                fs[lw][1]+nd.fu[0][rw],
                fs[lw][0]+nd.fu[0][rw],
                fu[lw][0]+nd.fs[1][rw],
                fu[lw][1]+nd.fs[0][rw],
                fu[lw][0]+nd.fs[0][rw]
            });
        }
        return res;
    }
    node(){
        memset(fu.begin(),0,sizeof(fu));
        memset(fs.begin(),0,sizeof(fs));
    }
};
class segment{
private:
    vector<node> tr;
    constexpr auto ls(int u){return u*2;}
    constexpr auto rs(int u){return u*2+1;}
    auto maintain(int u){
        tr[u]=tr[ls(u)]*tr[rs(u)];
    }
    auto update(int u,int l,int r,int p,node w){
        if(l==r) return tr[u]=w,void();
        const auto mid=midpoint(l,r);
        p-1<mid?update(ls(u),l,mid,p,w):update(rs(u),mid+1,r,p,w);
        maintain(u);
    }
    int n;
public:
    auto update(int p,node w){
        update(1,0,n-1,p,w);
    }
    auto value(){
        return max({
            tr[1].fs[0][0],
            tr[1].fs[0][1],
            tr[1].fs[1][0],
            tr[1].fs[1][1],
        });
    }
    segment(int _n):tr(_n<<2),n(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;multimap<int,int,greater<int>> mp;
        cir(i,0,n){
            int x;cin>>x;mp.emplace(x,i);
        }
        segment sg(n);
        auto ans=0;
        for(auto&[w,p]:mp){
            node upd;
            upd.fu[1][1]=1;
            upd.fs[1][1]=w+1;
            sg.update(p,upd);
            ans=max(ans,sg.value()+w);
        }
        println("{}",ans);
    }();
    return 0;
}
