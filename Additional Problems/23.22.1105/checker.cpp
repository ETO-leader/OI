#include<bits/stdc++.h>
#include"testlib.h"

using namespace std;

using VI=vector<int>;

int main(int argc,char*argv[]){
    registerTestlibCmd(argc,argv);
    
    int T=inf.readInt();

    while(T--) [&]{
        int n=inf.readInt(),m=inf.readInt();
        
        vector<VI> a(n,VI(m));
        for(auto&i:a) for(auto&j:i) j=inf.readInt();

        bool alok=false;

        for(int i=0;i<m;++i) for(int j=i;j<m;++j){
            bool ok=true;
            for(auto&x:a){
                swap(x[i],x[j]);
                ok&=is_sorted(x.begin(),x.end());
                swap(x[i],x[j]);
            }
            alok|=ok;
        }

        if(!alok){
            if(ouf.readInt()!=-1){
                quitf(_wa,"Wrong Answer\n");
            }
        }else{
            int ax=ouf.readInt()-1,bx=ouf.readInt()-1;
            bool ok=true;
            for(auto&x:a){
                swap(x[ax],x[bx]);
                ok|=is_sorted(x.begin(),x.end());
                swap(x[ax],x[bx]);
            }
            if(!ok) quitf(_wa,"Wrong Answer\n");
        }
    }();

    quitf(_ok,"Accepted\n");
}
