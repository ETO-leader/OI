#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m,l;cin>>n>>m>>l;
    vector<int> a(n),b(m),c(l);
    for(auto&i:a) cin>>i;
    for(auto&i:b) cin>>i;
    for(auto&i:c) cin>>i;
    // for(auto&i:c) a.push_back(i);
    map<tuple<vector<int>,vector<int>,vector<int>>,bool> f;
    auto solve=[&](auto __self,vector<int> st,vector<int> sa,vector<int> sc)->bool {
        if(f.count({st,sa,sc})) return f[{st,sa,sc}];
        if(!st.size()) return false;
        auto&res=f[{st,sa,sc}];
        cir(i,0,(int)(st.size())){
            auto nst=st;
            auto nsc=sc;
            nsc.push_back(st[i]);
            nst.erase(nst.begin()+i);
            ranges::sort(nsc);
            if(!__self(__self,sa,nst,nsc)) return res=true;
            cir(p,0,(int)(sc.size())) if(sc[p]<st[i]){
                auto cst=nst;
                cst.push_back(sc[p]);
                auto csc=sc;
                csc.erase(csc.begin()+p);
                csc.push_back(st[i]);
                ranges::sort(cst);
                ranges::sort(csc);
                if(!__self(__self,sa,cst,csc)) return res=true;
            }
        }
        return res=false;
    };
    cout<<(solve(solve,a,b,c)?"Takahashi":"Aoki")<<'\n';
    // auto solve=[&](auto __self,int cur,int st,int sa,int sc)->bool {
    //     if(cur&&(!st)) return false;
    //     if((!cur)&&(!sa)&&(!(sc^(st>>n)))) return false;
    //     if(cur){
    //         auto res=false;
    //         cir(i,0,(n+l)) if(st&(1<<i)){
    //             res|=(!__self(__self,cur^true,st^(1<<i),sa,sc));
    //             cir(p,0,l) if((!(sc&(1<<p)))&&l[p]<a[i]) res|=(!__self(__self,cur^true,(st^(1<<i))|(1<<p+n),sa,sc^(1<<p)));
    //         }
    //         return res;
    //     }else{
    //         auto res=true;
    //         cir(i,0,m) if(sa&(1<<i)){
    //             res|=(!__self(__self,cur^true,st,sa^(1<<i)),sc);
    //             cir(p,0,l) if((!(sc&(1<<p)))&&l[p]<b[i]) res|=(!__self(__self,cur^true,(st^(1<<i))))
    //         }
    //     }
    // };
    return 0;
}
