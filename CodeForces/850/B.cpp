#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
struct seg{
    int l,r;
    seg(int cent,int _r):l(cent-_r),r(cent+_r){}
};
const int _inf=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n,w,h;cin>>n>>w>>h;
        vector<seg> cake;
        //蛋糕，巧克力
        int mxu=_inf;
        cir(i,0,n){
            int ci;cin>>ci;
            cake.push_back(seg(ci,w));
        }
        int x;cin>>x;
        int posl=w*2-h*2,ad=x+h-cake[0].r;bool Tr=true;
        cir(i,1,n){
            int ci;cin>>ci;
            if(!Tr) continue;
            auto sg=seg(ci,h);
            cake[i].l+=ad;cake[i].r+=ad;
            if(sg.l>=cake[i].l&&sg.r<=cake[i].r){
               // cout<<cake[i].r-sg.r<<'\n';
                posl=min(posl,sg.l-cake[i].l);
                continue;
            }
            int chx=sg.r-cake[i].r;
            if(chx>0&&chx<=posl){
                posl-=chx;ad+=chx;
                cake[i].l+=chx;cake[i].r+=chx;
                posl=min(posl,sg.l-cake[i].l);
                continue;
            }
            Tr=false;
        }
        cout<<(Tr?"YES\n":"NO\n");
    }
    return 0;
}