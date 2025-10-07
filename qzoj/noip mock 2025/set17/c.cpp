#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
constexpr auto dist(int x,int y,int u,int v){
    if(x>u) swap(x,u),swap(y,v);
    if(y&1){                                           // Type I. trangle (x, y) is not upside-down
        const auto l_lim=y,r_lim=y+(u-x)*2;
        if(v&1){                                       // Type I-1. trangle (u, v) is not upside-down
            if(l_lim-1<v&&v-1<r_lim){                  // Type I-1-a. l_lim \le v \le r_lim
                return (u-x)*2;
            }else if(v<l_lim){                         // Type I-1-b. v < l_lim
                return (u-x)*2+(l_lim-v);
            }else if(v>r_lim){                         // Type I-1-c v > r_lim
                return (u-x)*2+(v-r_lim);
            }else{                                     // Type I-1-d. impossible
                assert(("Impossible case.",false));
            }
        }else{                                         // Type I-2. trangle (u, v) is upside-down
            if(l_lim-1<v&&v-1<r_lim){                  // Type I-2-a. l_lim \le v \le r_lim
                return (u-x)*2-1;
            }else if(v<l_lim){                         // Type I-2-b. v < l_lim
                return (u-x)*2+(l_lim-v);
            }else if(v>r_lim){                         // Type I-2-c v > r_lim
                return (u-x)*2+(v-r_lim);
            }else{                                     // Type I-2-d. impossible
                assert(("Impossible case.",false));
            }
        }
    }else{                                             // Type II. trangle (x, y) is upside-down
        const auto l_lim=y-1,r_lim=y+(u-x)*2+1;
        if(v&1){                                       // Type II-1. trangle (u, v) is not upside-down
            if(l_lim-1<v&&v-1<r_lim){                  // Type II-1-a. l_lim \le v \le r_lim
                return (u-x)*2+1;
            }else if(v<l_lim){                         // Type II-1-b. v < l_lim
                return (u-x)*2+1+(l_lim-v);
            }else if(v>r_lim){                         // Type II-1-c v > r_lim
                return (u-x)*2+1+(v-r_lim);
            }else{                                     // Type II-1-d. impossible
                assert(("Impossible case.",false));
            }
        }else{                                         // Type II-2. trangle (u, v) is upside-down
            if(l_lim-1<v&&v-1<r_lim){                  // Type II-2-a. l_lim \le v \le r_lim
                return (u-x)*2;
            }else if(v<l_lim){                         // Type II-2-b. v < l_lim
                return (u-x)*2+1+(l_lim-v);
            }else if(v>r_lim){                         // Type II-2-c v > r_lim
                return (u-x)*2+1+(v-r_lim);
            }else{                                     // Type II-2-d. impossible
                assert(("Impossible case.",false));
            }
        }
    }
    assert(("Impossible case.",false));
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    int x,y;cin>>x>>y;
    auto mn=_inf,px=-1,py=-1;
    cir(i,0,m){
        int u,v;cin>>u>>v;
        const auto ud=dist(x,y,u,v);
        if(ud<mn||(ud==mn&&u<px)){
            mn=ud;px=u;py=v;
        }
    }
    cout<<px<<' '<<py<<'\n';
    cout<<mn+1<<'\n';
    return 0;
}
