from sys import argv
from PIL import Image
import numpy as np

def Type(x):
    a, b, c = map(int, x)
    return a + b + c > 254 * 3

img = np.array(Image.open(argv[1]).convert('RGB'))

for i in range(len(img)):
    for j in range(len(img[i])):
        print('.' if Type(img[i][j]) else '#', end = '')
    print()

