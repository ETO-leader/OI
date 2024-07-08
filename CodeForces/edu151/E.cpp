#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
const int MOD=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;VI stm(n),pos;
    const int sqrk=sqrt(k)*3;
    cir(i,0,n){
        cin>>stm[i];
        if(stm[i]) pos.push_back(i);
    }
    const int n1=pos.size();
    vector<vector<VI>> D(2,vector<VI>(n1+1,VI(k+1)));
    int step=0,cnt=0;
    D[step][0][0]=1;
    cir(i,0,n){
        step^=1;cnt+=stm[i];
        cir(j,max(0,cnt-sqrk),min(n1,cnt+sqrk)+1){
            cir(w,0,k+1){
                D[step][j][w]=D[step^1][j][w];
                if(w>=abs(i-pos[j-1])&&(j))
                    (D[step][j][w]+=D[step^1][
                        j-1][w-abs(i-pos[j-1])])%=MOD;
            }
        }
    }
    cout<<[&](){
        int res=0;
        cir(i,0,k+1) if((i&1)==(k&1))
            (res+=D[step][n1][i])%=MOD;
        return res;
    }()<<'\n';
    return 0;
}
