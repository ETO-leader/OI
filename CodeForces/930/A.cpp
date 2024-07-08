#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;
        //find the number n-1
        int posm=0;
        cir(i,1,n){
            cout<<"? "<<posm<<' '<<posm<<' '<<i<<' '<<i<<'\n';
            cout.flush();
            char c;cin>>c;
            if(c=='<') posm=i;
        }
        //get the acceptable numbers
        vector<int> posx;posx.push_back(0);
        cir(i,1,n) if(i!=posm){
            const auto las=posx.back();
            cout<<"? "<<las<<' '<<posm<<' '<<i<<' '<<posm<<'\n';
            cout.flush();
            char c;cin>>c;
            if(c=='='){
                posx.push_back(i);
            }else if(c=='<'){
                posx.clear();posx.push_back(i);
            }
        }
        //get the min one
        int posn=0;
        cir(i,1,(int)(posx.size())){
            cout<<"? "<<posx[posn]<<' '<<posx[posn]<<' '<<posx[i]<<' '<<posx[i]<<'\n';
            cout.flush();
            char c;cin>>c;
            if(c=='>') posn=i;
        }
        cout<<"! "<<posm<<' '<<posx[posn]<<'\n';
        cout.flush();
    }
    return 0;
}
