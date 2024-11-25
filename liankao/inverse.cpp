#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("inverse.in");
ofstream fcout("inverse.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
class segment{
private:
    struct node{
        int tag,mx;
        auto addnum(int wx){tag+=wx;mx+=wx;}
        node(int _mx=0):tag(0),mx(_mx){}
    };
    vector<node> a;
    constexpr auto ls(auto u) const{return u*2;}
    constexpr auto rs(auto u) const{return u*2+1;}
    auto maintain(int u){
        a[u].mx=std::max(a[ls(u)].mx,a[rs(u)].mx)+a[u].tag;
    }
    auto update(int u,int l,int r,int ql,int qr,int w){
        if(qr<l||r<ql) return;
        if(ql-1<l&&r-1<qr) return a[u].addnum(w);
        const auto mid=(l+r)/2;
        update(ls(u),l,mid,ql,qr,w);
        update(rs(u),mid+1,r,ql,qr,w);
        maintain(u);
    }
    int n;
public:
    auto update(int l,int r,int w){update(1,0,n-1,l,r,w);}
    auto max(){return a[1].mx;}
    segment(int _n):n(_n),a(_n<<2,node()){}
};
int main(){
    ios::sync_with_stdio(false),fcin.tie(nullptr);
    int n;fcin>>n;vector<int> a(n);
    for(auto&i:a) fcin>>i;
    vector<int> lfp,lfw,rgp,rgw;
    set<int> invaild;
    cir(i,0,n){
        if(lfp.empty()||a[lfp.back()]<a[i]) lfp.push_back(i),invaild.insert(i);
    }
    for(auto i=n-1;~i;--i){
        if(rgp.empty()||a[rgp.back()]>a[i]) rgp.push_back(i),invaild.insert(i);
    }
    for(auto&i:lfp) clog<<i<<' ';
    clog<<'\n';
    for(auto&i:rgp) clog<<i<<' ';
    clog<<'\n';
    reverse(rgp.begin(),rgp.end());
    for(auto&i:lfp) lfw.push_back(a[i]);
    for(auto&i:rgp) rgw.push_back(a[i]);
    vector<vector<tuple<int,int,int>>> ops(n);
    const auto rc=(int)(rgp.size())-1;
    cir(i,0,n) if(!invaild.count(i)){
        const auto lp=lower_bound(lfp.begin(),lfp.end(),i)-lfp.begin();
        const auto lw=lower_bound(lfw.begin(),lfw.end(),a[i])-lfw.begin();
        const auto rp=lower_bound(rgp.begin(),rgp.end(),i)-rgp.begin();
        const auto rw=lower_bound(rgw.begin(),rgw.end(),a[i])-rgw.begin();
        clog<<i<<"<-->"<<a[i]<<" --> "<<lp<<' '<<lw<<' '<<rp<<' '<<rw<<'\n';
        if(lp-1<lw||max(rp,rw)>rc) continue;
        ops[lp].emplace_back(max(rp,rw),rc,1);
        ops[lw].emplace_back(max(rp,rw),rc,-1);
    }
    auto ans=0;
    segment sg(n);
    cir(i,0,n){
        for(auto&[l,r,w]:ops[i]) sg.update(l,r,w),clog<<i<<' '<<l<<' '<<r<<' '<<w<<'\n';
        ans=max(ans,sg.max());
    }
    fcout<<ans*2+1<<'\n';
    return 0;
}
