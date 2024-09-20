#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("d.in");
ofstream fcout("d.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;fcin>>n;
    if(n<10){
        vector<tuple<int,int,int>> ar(n);
        for(auto&[a,b,c]:ar) fcin>>a>>b>>c;
        vector<int> rk(n);
        iota(rk.begin(),rk.end(),0);
        auto ans=numeric_limits<lint>::max();
        do{
            vector<tuple<int,int,int>> na;
            for(auto&i:rk) na.push_back(ar[i]);
            auto chk=0ll;
            cir(i,1,n){
                chk+=max(get<0>(na[i-1])-get<0>(na[i]),0);
                get<0>(na[i])=max(get<0>(na[i]),get<0>(na[i-1]));
                chk+=max(get<1>(na[i-1])-get<1>(na[i]),0);
                get<1>(na[i])=max(get<1>(na[i]),get<1>(na[i-1]));
                chk+=max(get<2>(na[i-1])-get<2>(na[i]),0);
                get<2>(na[i])=max(get<2>(na[i]),get<2>(na[i-1]));
            }
            ans=min(ans,chk);
        }while(next_permutation(rk.begin(),rk.end()));
        fcout<<ans<<'\n';
    }else{
        fcout<<0<<'\n';
    }
    return 0;
}
