#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const int _inf=1e9+7;
const int maxk=31;
template<typename T>
class sparsetable{
private:
    vector<vector<T>> st;
    int ht,n;
    void init(const vector<T>&v){
        n=v.size();ht=log2(n)+3;
        st.assign(n,vector<T>(ht));
        cir(i,0,n) st[i][0]=v[i];
        cir(j,1,ht) cir(i,0,(n-(1<<(j-1))))
            st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
    }
public:
    T operator()(int l,int r) const{
        r=min(r,n-1);
        int lg=log2(r-l+1);
        if(l>r) abort();
        return max(st[l][lg],st[r-(1<<lg)+1][lg]);
    }
    sparsetable(const vector<T> v=vector<T>()){init(v);}
};
struct st_node{
    int p,ap;
    bool operator<(const st_node&s) const{
        return p+ap==s.p+s.ap?p<s.p:p+ap<s.p+s.ap;
    }
    st_node(int _p=0,int _ap=0):p(_p),ap(_ap){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;vector<int> a(n+2);
    const int __lg2=log2(n)+2;
    cir(i,1,n+1) cin>>a[i];a[n+1]=_inf;
    sparsetable<st_node> st([&](){
        vector<st_node> res(n+2);
        cir(i,1,n+2) res[i]={i,a[i]};
        return res;
    }());
    vector<vector<vector<int>>> D(
        n+2,vector<vector<int>>(maxk,vector<int>(__lg2))
    );
	[&](){
        cir(i,0,maxk) cir(j,0,__lg2)
            D[n+1][i][j]=n+1;
        cir(i,1,n+1){
            D[i][0][0]=st(i+1,i+a[i]).p;
            cir(w,1,maxk) D[i][w][0]=min(n+1,i+a[i]+w);
        }
        cir(stp,1,__lg2) cir(i,1,n+1) cir(w,0,maxk){
            cir(rw,0,maxk-w){
                auto&d=D[i][w+rw][stp];
                auto&nd=D[D[i][w][stp-1]][rw][stp-1];
                d=max(st_node(d,a[d]),st_node(nd,a[nd])).p;
            }
        }
    }();
    cir(cur,0,q){
        int l,r,k,ans(0);cin>>l>>r>>k;
        if(l==r){
            cout<<0<<'\n';continue;
        }
        if(l+a[l]+k>=r){
            cout<<1<<'\n';continue;
        }
        vector<int> subdp(k+1,l);
        for(int i=__lg2-1;~i;--i) [&](){
            cir(x,0,k+1) cir(y,0,k-x+1){
                const int u=D[subdp[x]][y][i];
                if(u+a[u]+(k-(x+y))>=r)
                    return;
            }
            ans+=(1<<i);
            for(int x=k;~x;--x) for(int y=k-x;~y;--y){
                subdp[x+y]=max(
                    st_node(subdp[x+y],a[subdp[x+y]]),
                    st_node(D[subdp[x]][y][i],
                    a[D[subdp[x]][y][i]])).p;
            }
        }();
        cout<<ans+2<<'\n';
    }
    return 0;
}
