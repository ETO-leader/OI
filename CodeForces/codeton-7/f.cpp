#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;n*=2;
        string s;cin>>s;
        vector<int> a(s.begin(),s.end());
        for(auto&x:a) x-='0';
        if(a[0]!=a[n-1]||(ranges::count(a,1)&1)) return cout<<-1<<'\n',void();
        vector<string> ans;
        if(a[0]){
            auto emp=(string)("(");
            cir(i,0,n/2-1) emp+="()";
            emp+=')';
            ans.emplace_back(emp);
            a[0]^=1;a[n-1]^=1;
        }
        [&]{
            auto emp=(string)("(");
            auto cnt=0;
            for(auto i=1;i+1<n-1;i+=2){
                if(a[i]!=a[i+1]){
                    if(cnt) emp+="))",--cnt,a[i]^=1;
                    else emp+="((",++cnt,a[i+1]^=1;
                }else{
                    emp+="()";
                }
            }
            emp+=")";
            a[0]^=1;
            a[n-1]^=1;
            ans.emplace_back(emp);
        }();
        [&]{
            auto emp=(string)("(");
            for(auto i=1;i+1<n-1;i+=2){
                if(a[i]==1&&a[i+1]==1) emp+=")(";
                else emp+="()";
            }
            emp+=")";
            ans.emplace_back(emp);
        }();
        cout<<ans.size()<<'\n';
        for(auto&x:ans) cout<<x<<'\n';
    }();
    return 0;
}
