#include"artclass.h"
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

auto sobel(int height,int width,const vector<vector<int>> R,const vector<vector<int>> G,const vector<vector<int>> B){
    vector gray(height,vector(width,0));
    cir(i,0,height) cir(j,0,width){
        const auto v=0.299*R[i][j]+0.587*G[i][j]+0.114*B[i][j];
        gray[i][j]=static_cast<int>(std::round(v));
    }
    static constexpr auto kx=array{
        array{-1,0,1},
        array{-2,0,2},
        array{-1,0,1}
    };
    static constexpr auto ky=array{
        array{-1,-2,-1},
        array{0,0,0},
        array{1,2,1}
    };
    vector edge(height,vector(width,0));
    cir(i,1,height-1)  cir(j,1,width-1){
        auto gx=0,gy=0;
        cir(u,-1,2) cir(v,-1,2){
            const auto p=gray[i+u][j+v];
            gx+=kx[u+1][v+1]*p;
            gy+=ky[u+1][v+1]*p;
        }
        const auto raw=sqrt(static_cast<double>(gx*gx+gy*gy));
        auto grad=static_cast<int>(round(raw));
        edge[i][j]=min(grad,255);
    }
    return edge;
}

int style(int H,int W,int R[500][500],int G[500][500],int B[500][500]){
    vector cR(H,vector<int>(W));
    vector cG(H,vector<int>(W));
    vector cB(H,vector<int>(W));
    cir(i,0,H) cir(j,0,W){
        cR[i][j]=R[i][j];
        cG[i][j]=G[i][j];
        cB[i][j]=B[i][j];
    }
    const auto data=sobel(H,W,cR,cG,cB);
    auto c220=0,c60=0,l10=0;
    for(auto&i:data){
        for(auto&j:i) c220+=j>239,c60+=j>59,l10+=j<11;
    }
    const auto p220=c220*1.0/(H*W);
    const auto p60=c60*1.0/(H*W);
    const auto p10=l10*1.0/(H*W);
    if(p220<0.017&&p60<0.1) return 4;
    if(p220>0.16) return 3;
    if(p60>0.25&&p10<0.12) return 2;
    return 1;
}

