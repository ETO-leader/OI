#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto eps=1e-10;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    auto n=0,s=0;
    cir(i,0,100) cir(j,0,100){
        println(cout,"? {:.5f} {:.5f} {:.5f} {:.5f} {:.5f} {:.5f} {:.5f} {:.5f}",i-0.005,j-0.005,i-0.005,j+0.005,i+0.005,j+0.005,i+0.005,j-0.005);
        cout.flush();
        double siz;cin>>siz;
        if(siz>eps){
            if(siz<(0.01*0.01)-eps) ++s;
            else ++n;
        }
    }
    println(cout,"! {:.15f}",n+s*0.5-1);
    cout.flush();
    return 0;
}
