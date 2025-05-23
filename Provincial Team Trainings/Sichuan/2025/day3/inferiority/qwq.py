import math
import matplotlib.pyplot as plt

def init():
    plt.figure(figsize=(10.0, 10.0), dpi = 80.0)
    plt.xlim(-100, 100)
    plt.ylim(-100, 100)

def drawCircle(x, y, r, pointsCount = 20000):
    xArr = [x + r]
    yArr = [y]
    for arg in range(1, pointsCount + 1):
        xArr.append(x + r * math.cos(math.pi * 2 * arg / pointsCount))
        yArr.append(y + r * math.sin(math.pi * 2 * arg / pointsCount))
    plt.plot(xArr, yArr)

def main():
    init()
    drawCircle(0,0,66,200000)
    plt.show()

if __name__ == '__main__':
    main()

