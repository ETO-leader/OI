with open('data') as inf:
    n = 0
    for l in inf:
        if n == 0:
            print('    vector<vector<int>>{')
            n = int(l)
            continue
        else:
            n -= 1
        s = l.replace(' ', ',').strip(',\n')
        print(f'        vector<int>{'{'}{s}{'}'},')
        if n == 0:
            print('    },')

