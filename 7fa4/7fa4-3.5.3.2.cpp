#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
#define cirr(i,a,b) for(int i=b-1;i>=a;--i)
using namespace std;
const int nx=3007;
const int ht=12;
template<typename T>
class sparsetable{
private:
    array<vector<T>,ht> st;
    vector<int> lg2;
    void init(const vector<T>&v){
        int n=v.size();
        for(auto&i:st) i.resize(n);
        lg2.resize(1<<ht);
        cir(i,0,ht) cir(j,(1<<i),(1<<(i+1))) lg2[j]=i;
        cir(i,0,n) st[0][i]=v[i];
        cir(j,1,ht) cir(i,0,(n-(1<<(j-1))))
            st[j][i]=min(st[j-1][i],st[j-1][i+(1<<(j-1))]);
    }
public:
    T operator()(int l,int r) const{
        l=max(l,0);r=min<int>(r,st[0].size()-1);
        int lg=lg2[r-l+1];
        return min(st[lg][l],st[lg][r-(1<<lg)+1]);
    }
    sparsetable(const vector<T>&v){init(v);}
};
using VI=vector<int>;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;
    vector<VI> mp(n,VI(m)),D(n,VI(m));
    for(auto&i:mp) for(auto&j:i) cin>>j;
    auto lineid=[&](int x,int y){
        return m+n-x-y-2;};
    auto linepos=[&](int x,int y){
        const int l=mp[x][y];
        const int lx=x+l,ly=y;
        return make_pair(lineid(lx,ly),
            min(n-lx-1,m-ly-1));
    };
    array<list<pair<int,int>>,nx*2> lnx;
    vector<sparsetable<int>> dx;
    cir(i,0,n) cir(j,0,m){
        lnx[lineid(i,j)].push_back({i,j});
    }
    D[n-1][m-1]=0;
    [&](){
        VI empvec(1);
        dx.push_back(sparsetable<int>(empvec));
    }();
    vector<int> pst;
    cir(i,1,n+m-1){
        pst.clear();
        cout<<"114514"<<'\n';
        for(auto&[x,y]:lnx[i]){
            const auto [line,l]=linepos(x,y);
            const int r=l+mp[x][y]-1;
            if(line<0) continue;
            D[x][y]=dx[line](l,r)+1;
            pst.push_back(D[x][y]);
        }
        cout<<i<<' '<<pst.size()<<endl;
        dx.push_back(sparsetable<int>(pst));
    }
    cout<<D[0][0]<<'\n';
    return 0;
}
