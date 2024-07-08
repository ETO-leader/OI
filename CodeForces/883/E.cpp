#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using db=long double;
using lint=long long;
const lint mx=1e18+7;
namespace math{
    //Solve ax^2+bx+c=0
    pair<db,db> solve(db a,db b,db c){
        const db delta=b*b-4*a*c;
        return {(-b-sqrt(delta))/(a*2),
            (-b+sqrt(delta)/(a*2))};
    }
};
//x-1=k^2+k
lint calc(lint x){
    if(x<2) return -114514;
    return x*x+x;
}
bool checksp(lint x){
    auto [w1,w2]=math::solve(1,1,-x-1);
    lint k1=w1,k2=w2;
    cir(i,-1,2) if(calc(k1+i)==x-1)
        return true;
    cir(i,-1,2) if(calc(k2+i)==x-1)
        return true;
    return false;
}
unordered_set<lint> sp;
__int128 calcbsc(__int128 x){return x*x*x+x*x+x+1;}
void init(){
    for(__int128 i=2;;++i){
        __int128 cnx=calcbsc(i);
        if(calcbsc(i)>mx) break;
        sp.insert(calcbsc(i));
        __int128 k=i*i*i*i;
        while(cnx+k<=mx){
            sp.insert(cnx+=k);k*=i;
        }
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    init();int T;cin>>T;
    while(T--){
        lint x;cin>>x;
        cout<<((sp.count(x)||
            checksp(x))?"YES\n":"NO\n");
    }
    return 0;
}
