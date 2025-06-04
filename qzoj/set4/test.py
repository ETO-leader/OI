from os import system

print("Test Dataset A")

for i in range(1, 17):
    system(f'cp ~/Downloads/contest3_testdata/domino/domino.in.{i}a ~/Documents/OI/qzoj/set4/inf')
    system(f'time ~/Documents/OI/qzoj/set4/c-11 < ~/Documents/OI/qzoj/set4/inf > ~/Documents/OI/qzoj/set4/ouf')
    system(f'diff -w ~/Documents/OI/qzoj/set4/ouf ~/Downloads/contest3_testdata/domino/domino.out.{i}a')

print("Test Dataset B")

for i in range(1, 17):
    system(f'cp ~/Downloads/contest3_testdata/domino/domino.in.{i}b ~/Documents/OI/qzoj/set4/inf')
    system(f'time ~/Documents/OI/qzoj/set4/c-11 < ~/Documents/OI/qzoj/set4/inf > ~/Documents/OI/qzoj/set4/ouf')
    system(f'diff -w ~/Documents/OI/qzoj/set4/ouf ~/Downloads/contest3_testdata/domino/domino.out.{i}b')

