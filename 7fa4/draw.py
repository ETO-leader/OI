import math
import matplotlib.pyplot as pl

class Painter:
    PI=math.pi

    def __init__(self,liml=-30,limr=30,limu=-30,limd=30):
        pl.figure(figsize=(10.0,10.0),dpi=200)
        pl.xlim(liml,limr)
        pl.ylim(limu,limd)

    def drawcir(self,cx,cy,R,label=''):
        if label != '':
            pl.text(cx+math.cos(self.PI/4)*(R-0.5),cy+math.sin(self.PI/4)*(R-0.5),label)
        pl.plot([cx+math.cos(self.PI*2/10000*i)*R for i in range(10001)],[cy+math.sin(self.PI*2/10000*i)*R for i in range(10001)],label=label)

    def drawseg(self,x1,y1,x2,y2,label=''):
        if label != '':
            pl.text((x1+x2)/2,(y1+y2)/2,label)
        pl.plot([x1,x2],[y1,y2],label=label)

    def export(self,file='export.png'):
        pl.savefig(file)

if __name__=='__main__':
    read = lambda : list(map(int,input().split()))

    board=Painter(-1000,2000,-1000,2000)

    n = read()[0]

    for i in range(n):
        x, y, r = read()
        board.drawcir(x,y,r,f'circle {i+1}')
    
    board.export()

