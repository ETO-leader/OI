#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using db=long double;
const db _inf=1e18L+7;
struct state{db a,b;};
vector<state> st;
db __getw(int c,const int k){
    vector<vector<db>> D(
        st.size(),vector<db>(c+1,_inf));
    D[0][0]=0;
    cir(i,1,st.size()){
        cir(w,0,min(i,c)+1){
            D[i][w]=D[i-1][w]+st[i].a/(db)(c+1);
            if(st[i].b<_inf&&w){
                D[i][w]=min(D[i][w],
                    D[i-1][w-1]+st[i].b/w);
            }
        }
    }
    db res=D[k][c];
    priority_queue<db,vector<db>,greater<db>> pq;
    cir(i,k,st.size()) pq.push(st[i].a/(db)(c+1));
    db cnx=0;
    for(int i=k-1;i>c-1;--i){
        cnx+=pq.top();pq.pop();
        res=min(res,D[i][c]+cnx);
        pq.push(st[i].a/(db)(c+1));
    }
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;st.resize(n+1);
    cir(i,1,n+1) cin>>st[i].a>>st[i].b;
    int c_ok=n;
    cir(i,0,n+1) if(st[i].b<0)
        st[i].b=_inf,--c_ok;
    sort(st.begin(),st.end(),[](state&a,state&b){
        return a.b<b.b;});
    db ans=_inf;
    cir(i,0,min(c_ok,k)+1) ans=min(ans,__getw(i,k));
    cout<<fixed<<setprecision(15)<<ans<<'\n';
    return 0;
}
