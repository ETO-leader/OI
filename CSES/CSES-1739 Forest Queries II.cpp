#include<bits/stdc++.h>
#define expcir(i,a,exp,x)\
    for(auto i=a;exp;i+=x)
#define addcir(i,a,b,x) for(auto i=a;i<b;i+=x)
#define cir(i,a,b) addcir(i,a,b,1)
using namespace std;
template<typename T>
class bit2D{
private:
    vector<vector<T>> val;size_t n,m;
    size_t lowbit(size_t x){return x&(-x);}
    T _quary(int x,int y){
        T res=0;
        expcir(_x,x,_x,-(int)(lowbit(_x)))
            expcir(_y,y,_y,-(int)(lowbit(_y)))
                res+=val[_x][_y];
        return res;
    }
public:
    void update(size_t x,size_t y,T v){
        addcir(_x,x,n+1,lowbit(_x))
            addcir(_y,y,m+1,lowbit(_y)){
                val[_x][_y]+=v;
            }
    }
    T range(size_t lx,size_t ly,size_t rx,size_t ry){
        return _quary(rx,ry)+_quary(lx-1,ly-1)-
            _quary(lx-1,ry)-_quary(rx,ly-1);
    }
    bit2D(size_t _n,size_t _m):n(_n),m(_m),
        val(_n,vector<T>(_m)){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;bit2D<int> bx(n+1,n+1);
    vector<vector<bool>> st(n+1,vector<bool>(n+1));
    cir(i,1,n+1) cir(j,1,n+1){
        char s;cin>>s;bool sx=s=='*';
        bx.update(i,j,sx);st[i][j]=sx;
    }
    cir(i,0,q){
        int op;cin>>op;
        if(op==1){
            int x,y;cin>>x>>y;st[x][y]=(!st[x][y]);
            bx.update(x,y,(st[x][y]?1:-1));
        }else{
            int lx,ly,rx,ry;cin>>lx>>ly>>rx>>ry;
            cout<<bx.range(lx,ly,rx,ry)<<'\n';
        }
    }
    return 0;
}