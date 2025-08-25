#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e5+7);
class node:public array<array<lint,4>,4>{
public:
    auto operator*(const node x) const{
        auto res=node();
        cir(k,0,4) cir(i,0,4) cir(j,0,4) (res[i][j]+=(*this)[i][k]*x[k][j])%=MOD;
        return res;
    }
    node(){for(auto&x:*this) for(auto&i:x) i=0;}
};
class segment{
private:
    vector<node> tr;
    constexpr auto ls(int u) const{return u*2;}
    constexpr auto rs(int u) const{return u*2+1;}
    auto maintain(int u){
        tr[u]=tr[ls(u)]*tr[rs(u)];
    }
    auto update(int u,int l,int r,int p,node w){
        if(l==r) return tr[u]=w,void();
        const auto mid=(l+r)/2;
        p-1<mid?update(ls(u),l,mid,p,w):update(rs(u),mid+1,r,p,w);
        maintain(u);
    }
    const int n;
public:
    auto update(int p,node w){
        update(1,0,n-1,p,w);
    }
    auto value(){
        return tr[1];
    }
    segment(int _n):tr(_n<<2),n(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    string s;cin>>s;
    const auto n=(int)(s.size());
    /**
     * 0: SUM
     * 1: LPROD
     * 2: PRODS
     * 3: 1
     */
    segment sg(n);
    auto update=[&](int i){
        auto nd=node();
        if(isdigit(s[i])){
            nd[0][0]=1;
            nd[1][1]=1;
            nd[2][2]=10;
            nd[1][2]=s[i]-'0';
        }else if(s[i]=='*'){
            nd[0][0]=1;
            nd[2][1]=1;
        }else if(s[i]=='+'){
            nd[0][0]=1;
            nd[2][0]=1;
            nd[3][1]=1;
        }
        nd[3][3]=1;
        sg.update(i,nd);
    };
    cir(i,0,n) update(i);
    auto ml=node(),mr=node();
    ml[0][1]=ml[0][3]=1;
    mr[0][0]=mr[2][0]=1;
    int q;cin>>q;
    cir(i,0,q){
        int p;cin>>p>>s[p-1];--p;
        update(p);
        cout<<(ml*sg.value()*mr)[0][0]<<'\n';
    }
    return 0;
}
