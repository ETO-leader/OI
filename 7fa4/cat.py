
if __name__ == '__main__':

    with open('inf') as inf:
        for ln in inf:
            if ln.split()[0] == 'A': print(ln.split()[1],ln.split()[2])