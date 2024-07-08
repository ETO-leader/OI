#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class notepad{
private:
    unordered_map<int,int> pgnd,f,fw;
    int u,ncnx;
    void insert(int n){
        f[++ncnx]=u;fw[ncnx]=n;
        u=ncnx;
    }
    void delete_x(){u=f[u];}
    void reload(int pg){u=pgnd[pg];}
    void save(int pg){pgnd[pg]=u;}
public:
    int submit(string op,int x){
        if(op=="DELETE") delete_x();
        else if(op=="SAVE") save(x);
        else if(op=="ADD") insert(x);
        else reload(x);
        return fw[u];
    }
    notepad():u(0),ncnx(0){fw[0]=-1;}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;notepad np;
    cir(i,0,n){
        string op;int x=0;
        cin>>op;
        if(op!="DELETE") cin>>x;
        cout<<np.submit(op,x)<<' ';
    }
    cout<<'\n';
    return 0;
}
