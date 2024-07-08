#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<short>;
struct line{
    int k,b;
    int operator()(int x){return k*x+b;}
    line(int _k=0,int _b=0):k(_k),b(_b){}
};
template<int siz>
class segment{
private:
    struct node{
        line f;
        node(){f=line(0,0);}
    };
    array<node,siz*4> sg;
    void update(int u,int l,int r,line&ln){
        if(sg[u].f(l)<ln(l)&&sg[u].f(r)<ln(r))
            return sg[u].f=ln,void();
        if(sg[u].f(l)>=ln(l)&&sg[u].f(r)>=ln(r))
            return;
        if(l==r) return;
        const int ls=u*2,rs=u*2+1,mid=(l+r)/2;
        auto gotols=[&](line&lx){
            update(ls,l,mid,lx);
        };
        auto gotors=[&](line&lx){
            update(rs,mid+1,r,lx);
        };
        auto lf=sg[u].f;
        if(sg[u].f.k<ln.k){
            if(sg[u].f(mid)<ln(mid))
                return sg[u].f=ln,gotols(lf);
            return gotors(ln);
        }else{
            if(sg[u].f(mid)<ln(mid))
               return sg[u].f=ln,gotors(lf);
            return gotols(ln);
        }
    }
    int query(int u,int l,int r,int q){
        if(l==r) return sg[u].f(q);
        const int ls=u*2,rs=u*2+1,mid=(l+r)/2;
        return max((q>mid?query(rs,mid+1,r,q):
            query(ls,l,mid,q)),sg[u].f(q));
    }
public:
    void insert(line ln){
        update(1,1,siz,ln);
    }
    auto operator()(int q){
        return query(1,1,siz,q);
    }
};
const int max_q=3e3+7;
auto dp(string s,int k,char col){
    const int n=s.size();
    vector<VI> res(n,VI(k+1));
    vector<vector<VI>> D(n,vector<VI>(k+1,VI(2)));
    if((s[0]!=col)<k+1){
        D[0][s[0]!=col][1]=1;
        res[0][s[0]!=col]=1;
    }
    cir(i,1,k+1) cir(x,0,2){
        D[0][i][x]=max(D[0][i][x],D[0][i-1][x]);
        res[0][i]=max(res[0][i],D[0][i][x]);
    }
    cir(i,1,n) cir(j,0,k+1){
        if(s[i]==col)
            D[i][j][1]=D[i-1][j][1]+1;
        else if(j)
            D[i][j][1]=D[i-1][j-1][1]+1;
        D[i][j][0]=max({D[i][j][0],
            D[i-1][j][0],D[i-1][j][1]});
        if(j) cir(k,0,2)
            D[i][j][k]=max(D[i][j][k],D[i][j-1][k]);
        res[i][j]=max(D[i][j][0],D[i][j][1]);
    }
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n,k;string s;cin>>n>>k>>s;
        auto sl1=dp(s,k,'0');
        auto sl2=dp(s,k,'1');
        reverse(s.begin(),s.end());
        auto sr1=dp(s,k,'0');
        auto sr2=dp(s,k,'1');
        reverse(sr1.begin(),sr1.end());
        reverse(sr2.begin(),sr2.end());
        segment<max_q> seg;
        cir(i,-1,n) cir(w,0,k+1){
            seg.insert(line((i<0?0:sl1[i][w]),
                (i>n-2?0:sr2[i+1][k-w])));
            seg.insert(line((i>n-2?0:sr1[i+1][k-w]),
                (i<0?0:sl2[i][w])));
        }
        cir(i,1,n+1) cout<<seg(i)<<' ';
        cout<<'\n';
    }
    return 0;
}