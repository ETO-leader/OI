#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
const int _inf=1e9+7;
struct seg{int l,r;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;
    vector<seg> sg(k);
    for(auto&[l,r]:sg) cin>>l>>r;
    vector<VI> D(2,VI(n*2+1,_inf));
    int stp=0;D[stp][0]=0;
    for(auto&[l,r]:sg){
        stp^=1;
        D[stp]=D[stp^1];
        [&](){
            deque<int> q;
            for(int i=r;~i;--i){
                while((!q.empty())&&q.front()<(
                    l-i)) q.pop_front();
                while((!q.empty())&&D[stp^1][q.back()
                    ]>(D[stp^1][r-i]-1)) q.pop_back();
                q.push_back(r-i);
                D[stp][i]=min(D[stp][i],
                    D[stp^1][q.front()]+1);
            }
        }();
        [&](){
            deque<int> q;
            cir(i,0,r+1){
                while((!q.empty())&&q.front()<(
                    i-(r-l))) q.pop_front();
                while((!q.empty())&&D[stp^1][q.back()
                    ]>(D[stp^1][i]-1)) q.pop_back();
                q.push_back(i);
                D[stp][i]=min(D[stp][i],
                    D[stp^1][q.front()]+2);
            }
        }();
    }
    if(D[stp][n]==_inf){
        cout<<"Hungry\n";
    }else{
        cout<<"Full\n"<<D[stp][n]<<'\n';
    }
    return 0;
}
