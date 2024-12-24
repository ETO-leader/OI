from os import system
from random import randint

if __name__ == '__main__':
    while True:
        system(f'sl -{"a" if randint(0, 1) else ""}{"l" if randint(0, 1) else ""}{"F" if randint(0, 1) else ""}')
