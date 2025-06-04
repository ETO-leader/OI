import numpy as np
from PIL import Image
from sys import argv

def main():

    input_path = argv[1]
    output_path = argv[2]

    with open(input_path, 'r') as img:
        data = img.read().split()

        cnt = 0

        def nextNums(c):
            nonlocal data, cnt
            res = []
            for i in range(c):
                res.append(data[cnt])
                cnt += 1
            return res

        H, W = map(int, nextNums(2))

        arr = [(0, 0, 0)] * H * W

        for i in range(H * W):
            ur, ug, ub = map(int, nextNums(3))
            arr[i] = (ur, ug, ub)

        arr = np.array(arr, dtype = np.uint8)
        arr = arr.reshape((H, W, 3))

        img = Image.fromarray(arr, mode="RGB")
        img.save(output_path)

if __name__ == "__main__":
    main()