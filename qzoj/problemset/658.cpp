#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class segment{
private:
    struct node{
        node*ls,*rs;
        lint tag,sum,area;
        auto mktag(lint w){
            tag+=w;
            sum+=area*w;
        }
        auto maintain(){
            sum=tag*area;
            if(ls) sum+=ls->sum;
            if(rs) sum+=rs->sum;
        }
        node(lint _area):area(_area),ls(nullptr),rs(nullptr),tag(0),sum(0){}
        ~node(){
            if(ls) delete ls;
            if(rs) delete rs;
        }
    };
    node*root;
    constexpr auto midpoint(auto l,auto r) const{return l+(r-l)/2;}
    int cnt=0;
    template<const int _type>
    auto update(node*&u,int al,int ar,int au,int ad,int ql,int qr,int qu,int qd,lint w){
        if(qr<al||ar<ql||qd<au||ad<qu) return;
        if(!u) u=new node((lint)(ar-al+1)*(ad-au+1));
        ++cnt;
        cerr<<cnt<<' '<<al<<' '<<ar<<' '<<au<<' '<<ad<<'\n';
        if(ql-1<al&&ar-1<qr&&qu-1<au&&ad-1<qd) return u->mktag(w);
        if(!_type){
            const auto mid=midpoint(al,ar);
            update<_type^1>(u->ls,al,mid,au,ad,ql,qr,qu,qd,w);
            update<_type^1>(u->rs,mid+1,ar,au,ad,ql,qr,qu,qd,w);
        }else{
            const auto mid=midpoint(au,ad);
            update<_type^1>(u->ls,al,ar,au,mid,ql,qr,qu,qd,w);
            update<_type^1>(u->rs,al,ar,mid+1,ad,ql,qr,qu,qd,w);
        }
        u->maintain();
    }
    template<const int _type>
    auto query(node*u,int al,int ar,int au,int ad,int ql,int qr,int qu,int qd){
        if((!u)||(qr<al||ar<ql||qd<au||ad<qu)) return 0ll;
        if(ql-1<al&&ar-1<qr&&qu-1<au&&ad-1<qd) return u->sum;
        const auto adc=u->tag*(lint)(min(qr,ar)-max(ql,al)+1)*(min(qd,ad)-max(qu,au)+1);
        if(!_type){
            const auto mid=midpoint(al,ar);
            return query<_type^1>(u->ls,al,mid,au,ad,ql,qr,qu,qd)+query<_type^1>(u->rs,mid+1,ar,au,ad,ql,qr,qu,qd)+adc;
        }else{
            const auto mid=midpoint(au,ad);
            return query<_type^1>(u->ls,al,ar,au,mid,ql,qr,qu,qd)+query<_type^1>(u->rs,al,ar,mid+1,ad,ql,qr,qu,qd)+adc;
        }
    }
    const int n;
public:
    auto update(int l,int r,int u,int d,int w){
        cnt=0;
        update<0>(root,-n,n-1,-n,n-1,l,r,u,d,w);
        cerr<<cnt<<'\n';
    }
    auto query(int l,int r,int u,int d){
        return query<0>(root,-n,n-1,-n,n-1,l,r,u,d);
    }
    segment(int _n):n(_n),root(nullptr){}
    ~segment(){if(root) delete root;}
};
static constexpr auto maxt=(int)(1e6+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    segment sg(maxt);
    cir(i,0,n){
        int l,r,u,d;cin>>l>>u>>r>>d;
        sg.update(l,r,u,d,1);
    }
    int q;cin>>q;
    cir(i,0,q){
        int w;cin>>w;
        cout<<sg.query(-w,w,-w,w)<<'\n';
    }
    return 0;
}
