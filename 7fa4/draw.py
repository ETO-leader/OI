import math
import matplotlib.pyplot as pl

PI=math.pi

N=int(input())

R=int(input())

pl.figure(figsize=(10.0,10.0),dpi=200)

pl.xlim(-30,30)
pl.ylim(-30,30)

def drawcir(cx,cy,r):
    x=[]
    y=[]
    for i in range(10001):
        x.append(cx+math.cos(PI*2/10000*i)*R)
        y.append(cy+math.sin(PI*2/10000*i)*R)
    pl.plot(x,y)

for i in range(N):
    x,y=map(float,input().split())
    drawcir(x,y,R)

pl.savefig('export.png')
