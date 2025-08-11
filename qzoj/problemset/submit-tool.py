import http.client
http.client._strip_ipv6_iface = lambda name: name

import requests
import select
from bs4 import BeautifulSoup
from sys import argv, stderr, stdin
import os, time

def fail(message : str):
    stderr.write(f'Failed: {message}')
    exit()

def getUserInfo(needId = True):
    with open(os.path.expanduser('~/.uoj-submit-tool'), 'r') as info:
        URL = info.readline().strip()
        usrName = info.readline().strip()
        suffix = info.readline().strip()
        info.close()
    return URL, usrName, suffix

def record(info : str):
    with open('uoj-submit-tool.log', 'a') as records:
        print(info)
        records.write(info)
        records.close()

def makeSession(Id : int):
    with open('uoj-submit-tool.time-session', 'w') as current:
        current.write(f'{time.time()}\n')
        current.close()
    URL, usrName, suffix = getUserInfo()
    os.system(f'cp default{suffix} {Id}{suffix}')
    os.system(f'code {Id}{suffix}')
    os.system('code inf ans')
    record(f'Start session, problem id: {Id}\n')

def checkFinishSession(pid : int):
    URL, usrName, suffix = getUserInfo()
    session = requests.Session()
    resp = session.get(f'{URL}/user/profile/{usrName}')
    if not f'"/problem/{pid}"' in resp.text:
        return False
    with open('uoj-submit-tool.time-session', 'r') as startTime:
        stime = float(startTime.readline().strip())
        startTime.close()
    utime = time.time() - stime;
    record(f'Session finished, used time = {utime} seconds\n')
    return True

def stopSession():
    record('Session Stopped\n');
    return True

def Init(URL, usrName, suffix):
    with open(os.path.expanduser('~/.uoj-submit-tool'), 'w') as storage:
        storage.write(f'{URL}\n{usrName}\n{suffix}\n')
        storage.close()

def ensureArgv(rlen):
    if len(argv) < rlen:
        fail('too few arguments.\n')

def checkFiles():
    os.system('touch uoj-submit-tool.log')
    os.system('touch uoj-submit-tool.time-session')

def main():
    checkFiles()
    op = argv[1]
    if op == 'config':
        ensureArgv(5)
        Init(argv[2], argv[3], argv[4])
    elif op == 'start':
        ensureArgv(3)
        pid = int(argv[2])
        makeSession(pid)
        while True:
            ready, _, _ = select.select([stdin], [], [], 0)
            if len(ready) > 0:
                user_input = stdin.readline()
                if user_input == 'stop\n':
                    stopSession()
                    break
                elif user_input == 'test\n':
                    URL, usrName, suffix = getUserInfo()
                    print('Running...')
                    if os.system(f'g++ {pid}{suffix} -Wall -Wextra -Wshadow -Wconversion -W -fsanitize=address,undefined -g -O2 -std=c++26'):
                        print('Compile Error')
                    elif os.system('timeout 10 time ./a.out < inf > ouf'):
                        print('Runtime Error')
                    elif os.system('diff -w ouf ans'):
                        print('Wrong Answer')
                    else:
                        print('Accepted')
                elif user_input == 'testlog\n':
                    URL, usrName, suffix = getUserInfo()
                    print('Running...')
                    if os.system(f'g++ {pid}{suffix} -Wall -Wextra -Wshadow -Wconversion -W -fsanitize=address,undefined -g -O2 -std=c++26'):
                        print('Compile Error')
                    elif os.system('timeout 10 time ./a.out < inf > ouf 2> log'):
                        print('Runtime Error')
                    elif os.system('diff -w ouf ans'):
                        print('Wrong Answer')
                    else:
                        print('Accepted')
                else:
                    print('No such command')
            else:
                if checkFinishSession(pid):
                    break
            time.sleep(2)
    else:
        stderr.write('No such opinion')

if __name__ == '__main__':
    main()


