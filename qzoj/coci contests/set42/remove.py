try:
    while True:
        s = input()
        if len(s) > 0 and s[0] != '#':
            print(s)
except EOFError:
    pass