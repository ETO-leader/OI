#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
using lf=long double;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;
    while(cin>>n) [n]{
        priority_queue<tuple<lf,lint,lint>,vector<tuple<lf,lint,lint>>,greater<>> q;
        cir(i,0,n){
            lf x,y,r;lint s,d;cin>>x>>y>>s>>r>>d;
            const auto dis=abs(complex<lf>(x-100,y))-r;
            q.emplace(dis,s,d);
        }
        lint hp;cin>>hp;
        auto udis=100ll;
        while(!q.empty()){
            const auto[dis,s,d]=q.top();q.pop();
            if(dis>udis) break;
            udis+=s;
            hp-=d;
        }
        cout<<(hp>0?"Safe!":"Danger!")<<'\n';
    }();
    return 0;
}

