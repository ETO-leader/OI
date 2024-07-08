#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("jump.in");
ofstream fcout("jump.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
};
using VI=vector<int>;
struct city{
    int x,y,id;
    auto operator<(const city&a) const{
        return y==a.y?id<a.id:y<a.y;
    }
    city(int _x=-1,int _y=-1,int _id=0):
        x(_x),y(_y),id(_id){}
};
struct square{
    int l,r,u,d;
    square(int _l=-1,int _r=-1,int _u=-1,
        int _d=-1):l(_l),r(_r),u(_u),d(_d){}
};
class setsegment{
private:
    vector<set<city>> tr;
    constexpr auto ls(int u){return u*2;}
    constexpr auto rs(int u){return u*2+1;}
    auto update(int u,int l,int r,
        int p,city x,auto f){
        f(u,x);
        if(l==r) return;
        const auto mid=(l+r)/2;
        if(p<mid+1) update(ls(u),l,mid,p,x,f);
        else update(rs(u),mid+1,r,p,x,f);
    }
    auto ckrng(int u,int l,int r,int ql,
        int qr,int rl,int rr,auto f){
        if(ql-1<l&&r-1<qr) return [&](){
            auto lx=tr[u].lower_bound(city(-1,rl,-1)),
            rx=tr[u].lower_bound(city(-1,rr+1,-1));
            for(auto it=lx;it!=rx;++it) f(*it);
        }();
        const auto mid=(l+r)/2;
        if(ql<mid+1) ckrng(ls(u),l,mid,ql,qr,rl,rr,f);
        if(mid<qr) ckrng(rs(u),mid+1,r,ql,qr,rl,rr,f);
    }
    int n;
public:
    auto update(int p,city c,auto f){
        update(1,1,n,p,c,f);
    }
    auto ckrng(int l,int r,int u,int d,auto f){
        ckrng(1,1,n,l,r,u,d,f);
    }
    function<void(int,city)> ins=[&](
        int u,city x){tr[u].insert(x);};
    function<void(int,city)> del=[&](
        int u,city x){tr[u].erase(x);};
    setsegment(int _n):n(_n),tr(_n<<2){}
};
struct heapnode{
    square sq;int k;
    bool operator<(const heapnode&x) const{
        return k>x.k;
    }
};
int main(){
    ios::sync_with_stdio(false),fcin.tie(0);
    int n,m,mx,my;fcin>>n>>m>>mx>>my;
    setsegment sg(mx+7);
    vector<city> cps;
    cir(i,0,n){
        int x,y;fcin>>x>>y;
        sg.update(x,city(x,y,i),sg.ins);
        cps.push_back(city(x,y,i));
    }
    vector<vector<heapnode>> sqs(n);
    cir(i,0,m){
        int c,t,l,r,u,d;
        fcin>>c>>t>>l>>r>>u>>d;
        sqs[c-1].push_back({square(l,r,u,d),t});
    }
    priority_queue<heapnode> pq;
    pq.push({square(cps[0].x,
        cps[0].x,cps[0].y,cps[0].y),0});
    VI ans(n,-1);
    while(!pq.empty()){
        auto[sq,w]=pq.top();pq.pop();
        vector<city> del;
        sg.ckrng(sq.l,sq.r,sq.u,
            sq.d,[&](const city&c){
            if(ans[c.id]>-1) return;
            del.push_back(c);ans[c.id]=w;
            for(auto&[sq,wx]:sqs[c.id]){
                pq.push({sq,w+wx});
            }
        });
        for(auto&i:del){
            sg.update(i.x,i,sg.del);
        }
    }
    ans.erase(ans.begin());
    for(auto&i:ans) fcout<<i<<'\n';
    return 0;
}
