#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    static constexpr auto maxc=15;
    while(T--) []{
        int n;cin>>n;
        vector<pair<int,int>> es;
        cir(i,0,maxc){
            es.emplace_back(i*4,i*4+1);
            es.emplace_back(i*4+1,i*4+2);
            es.emplace_back(i*4+2,i*4+3);
            es.emplace_back(i*4+3,i*4+4);
            es.emplace_back(i*4+1,i*4+3);
            es.emplace_back(i*4+2,i*4+4);
        }
        auto cnt=maxc*4+1;
        auto cx=0,cy=3;
        cir(i,0,maxc){
            if(n%3==1) es.emplace_back(cx,cnt),es.emplace_back(cnt,cnt+1),++cnt;
            if(n%3==2) es.emplace_back(cy,cnt),es.emplace_back(cnt,cnt+1),++cnt;
            cx+=4;cy+=4;n/=3;
        }
        vector a(cnt+1,vector<int>(cnt+1));
        cir(i,1,cnt) a[i][i]=1;
        a[cnt][0]=1;
        for(auto&[x,y]:es) a[x][y]=-1;
        cout<<cnt+1<<'\n';
        for(auto&x:a){
            for(auto&y:x) cout<<y<<' ';
            cout<<'\n';
        } 
    }();
    return 0;
}
