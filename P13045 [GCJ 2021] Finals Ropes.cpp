#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T,n,w;cin>>T>>n>>w;
    while(T--){
        vector<int> p(2*n+1),q(2*n+1);
        vector<pair<int,int>> ropes;
        cir(r,0,n){
            auto a=-1,b=-1;
            if(!r){
                a=10;b=10;
            }else{
                auto f=-1,bx=0,by=0;
                cir(x,1,2*n+1){
                    if(p[x]) continue;
                    cir(y,1,2*n+1){
                        if(q[y]) continue;
                        int ans=0;
                        for(auto&[ra,rb]:ropes){
                            int u=ra,v=rb;
                            if((u<x&&v>y)||(u>x&&v<y)) ++ans;
                        }
                        if(ans>f){
                            f=ans;
                            bx=x;
                            by=y;
                        }else if(ans==f){
                            if(x+y<bx+by) bx=x,by=y;
                            else if(x+y==bx+by&&x<bx) bx=x,by=y;
                        }
                    }
                }
                a=bx;b=by;
            }
            cout<<a<<' '<<b<<'\n';
            cout.flush();
            p[a]=true;q[b]=true;
            ropes.emplace_back(a,b);
            int c,d;cin>>c>>d;
            p[c]=true;q[d]=true;
            ropes.emplace_back(c,d);
        }
        int res;cin>>res;
    }
    return 0;
}
