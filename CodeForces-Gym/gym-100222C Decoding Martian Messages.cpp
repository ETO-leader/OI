#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
#if not defined(__DEBUG__)
ifstream inf("decoding.in");
ofstream ouf("decoding.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
#define cin inf
#define cout ouf
#endif
using lf=long double;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int c,k,t;cin>>c>>k>>t;
    vector<string> strs(c);
    for(auto&i:strs) cin>>i;
    vector<vector<int>> fstr(c);
    cir(i,0,c) cir(j,0,c){
        if(strs[i].substr(1)==strs[j].substr(0,k-1)){
            fstr[i].push_back(j);
        }
    }
    int n;cin>>n;
    vector<vector<lf>> p(n,vector<lf>(t));
    for(auto&i:p) for(auto&j:i) cin>>j;
    vector<lf> f(c);
    vector<vector<int>> fr(n,vector<int>(c));
    cir(i,0,c){
        auto px=1.0l;
        cir(x,0,k) px*=p[x][strs[i][x]-'a'];
        f[i]=px;
    }
    cir(i,k,n){
        const auto g=f;
        fill(f.begin(),f.end(),0.0l);
        cir(x,0,c) for(const auto&nx:fstr[x]){
            const auto px=g[x]*p[i][strs[nx][k-1]-'a'];
            if(px>f[nx]) f[nx]=px,fr[i][nx]=x;
        }
    }
    const auto mxp=max_element(f.begin(),f.end())-f.begin();
    if(f[mxp]==0){
        exit((cout<<"---"<<'\n',0));
    }
    function<void(int,int)> print=[&](int px,int id){
        if(px==k-1) return cout<<strs[id],void();
        print(px-1,fr[px][id]);
        cout<<strs[id][k-1];
    };
    print(n-1,mxp);cout<<'\n';
    return 0;
}
