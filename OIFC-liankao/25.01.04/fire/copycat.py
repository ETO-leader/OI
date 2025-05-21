
def main():

    inf = open('fire.in','r')
    ans = open('fire.ans','r')

    T = int(inf.readline())

    for i in range(T):
        print("IN: ")
        print(inf.readline())
        print("OUT: ")
        line : str
        line = ans.readline()
        while line.split()[0] != '---':
            print(line)
            line = ans.readline()

if __name__ == '__main__':
    main()
