#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
enum oper{mintag,sumtag};
template<typename T>
class segment{
private:
    struct node{
        T mx,mn,sum,add;int l,r;
        node&operator+=(node x){
            mx+=x.add;mn+=x.add;add+=x.add;
            sum+=x.add*(r-l+1);
            return *this;
        }
        void set(){add=0;}
        void settag(T x){
            add+=x;mn+=x;mx+=x;sum+=(r-l+1)*x;
        }
        bool cansqr(){
            return (mx-(T)(sqrt(mx)))==
                (mn-(T)(sqrt(mn)));
        }
        void setsqr(){settag(-(mx-(T)(sqrt(mx))));}
    };
    const T _inf=numeric_limits<T>::max();
    vector<node> tr;
    void push_down(int u){
        tr[u*2]+=tr[u];tr[u*2+1]+=tr[u];
        tr[u].set();
    }
    void maintain(int u){
        tr[u].sum=tr[u*2].sum+tr[u*2+1].sum;
        tr[u].mx=max(tr[u*2].mx,tr[u*2+1].mx);
        tr[u].mn=min(tr[u*2].mn,tr[u*2+1].mn);
    }
    void add(int u,int l,int r,int ql,int qr,T w){
        if(ql<=l&&r<=qr) return tr[u].settag(w);
        push_down(u);
        const int ls=u*2,rs=u*2+1,mid=(l+r)/2;
        if(ql<=mid) add(ls,l,mid,ql,qr,w);
        if(qr>mid) add(rs,mid+1,r,ql,qr,w);
        maintain(u);
    }
    void sqr(int u,int l,int r,int ql,int qr){
        if(!tr[u].mx) return;
        if(ql<=l&&r<=qr&&tr[u].cansqr())
            return tr[u].setsqr();
        push_down(u);
        const int ls=u*2,rs=u*2+1,mid=(l+r)/2;
        if(ql<=mid) sqr(ls,l,mid,ql,qr);
        if(qr>mid) sqr(rs,mid+1,r,ql,qr);
        maintain(u);
    }
    T query(int u,int l,int r,int ql,int qr,oper t){
        if(ql<=l&&r<=qr) return t?tr[u].sum:tr[u].mn;
        push_down(u);
        const int ls=u*2,rs=u*2+1,mid=(l+r)/2;
        T w1=(t?0:_inf),w2=(t?0:_inf);
        if(ql<=mid) w1=query(ls,l,mid,ql,qr,t);
        if(qr>mid) w2=query(rs,mid+1,r,ql,qr,t);
        maintain(u);
        return t?(w1+w2):min(w1,w2);
    }
    void build(int u,int l,int r,vector<T>&v){
        if(l==r){
            tr[u]={v[l],v[l],v[l],0,l,r};
            return;
        }
        const int ls=u*2,rs=u*2+1,mid=(l+r)/2;
        tr[u].l=l;tr[u].r=r;
        build(ls,l,mid,v);build(rs,mid+1,r,v);
        maintain(u);
    }
    int n;
public:
    void add(int l,int r,T w){add(1,1,n,l,r,w);}
    void sqr(int l,int r){sqr(1,1,n,l,r);}
    T operator()(int l,int r,oper tag){
        return query(1,1,n,l,r,tag);
    }
    segment(vector<T>&v):n(v.size()-1),
        tr(v.size()*4){build(1,1,n,v);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;vector<lint> v(n);
    for(auto&i:v) cin>>i;
    v.insert(v.begin(),0);
    segment<lint> seg(v);
    cir(i,0,q){
        int x;cin>>x;
        if(x==1){
            int l,r,k;cin>>l>>r>>k;
            seg.add(l,r,k);
        }else if(x==2){
            int l,r;cin>>l>>r;
            seg.sqr(l,r);
        }else{
            int l,r;cin>>l>>r;
            cout<<seg(l,r,sumtag)<<'\n';
        }
    }
    return 0;
}
