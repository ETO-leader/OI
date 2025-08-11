import requests

session = requests.Session()
resp = session.get('http://124.221.194.184/user/profile/ETO_leader')
print(resp.text)

