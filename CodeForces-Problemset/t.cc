#include<bits/stdc++.h> 
using namespace std;
const int N=81;
int a[N][N];
vector<pair<int,int>> e;
void add(int x,int y){
    e.push_back({x,y});
}
void make_matrix(int n){
    for(int i=2;i<n;++i) a[i][i]=1;
    a[n][1]=1;
    for(auto [x,y]:e) a[x][y]=-1;
}
int main(){
    int _; scanf("%d",&_); //cin>>_;
    int max_bit=15;
    while(_--){
        memset(a,0,sizeof(a)); e.clear();
        int n=1;
        for(int i=0;i<max_bit;++i){
            add(n,n+1); add(n+1,n+2); add(n+2,n+3); add(n+3,n+4);
            add(n+1,n+3); add(n+2,n+4);
            n+=4;
        }
        int x,bit_1=1,bit_2=4; scanf("%d",&x); ++n;
        for(int i=0;i<max_bit;++i){
            if (x%3==1) add(bit_1,n),add(n,n+1),++n;
            if (x%3==2) add(bit_2,n),add(n,n+1),++n;
            bit_1+=4; bit_2+=4; x/=3;
        }
        make_matrix(n);
        cout << n <<'\n';
        for (int r = 1; r <= n; r++) {
            for (int c = 1; c <= n; c++) {
                printf("%d ",a[r][c]);
            }
            cout << '\n';
        }
    }
}
