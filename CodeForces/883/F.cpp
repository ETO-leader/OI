#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;
        unordered_map<int,int> cnx;
        cir(i,0,n){
            int x;cin>>x;cnx[x]++;
        }
        int id=-1;
        vector<int> v(n);
        while(true){
            cout<<"- 0"<<endl;
            unordered_map<int,int> ncnx;
            cir(i,0,n){
                cin>>v[i];int x=v[i];ncnx[x]++;
                for(auto&[a,b]:ncnx) if(b>cnx[a]){
                    id=a;break;
                }
            }
            if(id>-1) break;
        }
        int ncnx=n;
        stringstream ss;
        cir(i,0,n) if(v[i]!=id) (ss<<i+1<<' '),(--ncnx);
        cout<<"- "<<n-ncnx<<' '<<ss.str()<<endl;
        [&](){
            while(true){
                bool tagx=false;
                cir(i,0,ncnx){
                    int x;cin>>x;
                    if(x!=id){
                        cout<<"! "<<i+1<<endl;
                        tagx=true;
                    }
                }
                if(tagx) return;
                cout<<"- 0"<<endl;
            }
        }();
        cout.flush();
    }
    return 0;
}
