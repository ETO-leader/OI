#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("matrix.in");
ofstream fcout("matrix.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using VI=vector<int>;
VI diff(VI a){
    auto cpa=a;
    sort(a.begin(),a.end());
    VI res(a.size());
    cir(i,0,a.size()) res[i]=(cpa[i]==a[i]);
    return res;
}
int main(){
    ios::sync_with_stdio(false),fcin.tie(0);
    int T;fcin>>T;
    while(T--) [](){
        int n,m;fcin>>n>>m;
        vector<VI> mx(n,VI(m));
        for(auto&i:mx) for(auto&j:i) fcin>>j;
        auto check=[&](VI a){
            VI s;
            cir(i,0,m) if(!a[i]) s.push_back(i);
            if(s.size()>2) return false;
            for(auto&i:mx){
                swap(i[s[0]],i[s[1]]);
                if(!is_sorted(i.begin(),i.end())){
                    return false;
                }
            }
            return true;
        };
        set<VI> s;
        for(auto&i:mx){
            if(!is_sorted(i.begin(),i.end())){
                s.insert(diff(i));
            }
        }
        if(s.empty()){
            fcout<<(m>513?"514 514":(m>113?
                "114 114":"1 1"))<<'\n';
        }else{
            auto&fst=*s.begin();
            if(s.size()>1||(!check(fst))){
                fcout<<"-1\n";
            }else{
                cir(i,0,m) if(!fst[i])
                    fcout<<i+1<<' ';
                fcout<<'\n';
            }
        }
    }();
    return 0;
}
