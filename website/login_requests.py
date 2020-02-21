import requests

with requests.Session() as s:
    # make intial request to fetch csrf_token
    r1 = s.get("http://127.0.0.1:5000/login")

    # extract the token and craft the payload
    csrf_begin = r1.text.find('value="') + 7
    csrf_end = r1.text.find('"', csrf_begin)
    csrf_token = r1.text[csrf_begin:csrf_end]
    login_payload = {'csrf_token': csrf_token, 'username': 'nisha', 'password': 'nisha'}

    # make request to login, allowing redirects
    r2 = s.post("http://127.0.0.1:5000/login", data=login_payload, allow_redirects=True)
    # print(r2.text)

    # submit a post
    data_payload = {'csrf_token': csrf_token, 'post': 'testing data upload'}
    r3 = s.post("http://127.0.0.1:5000/index", data=data_payload, allow_redirects=True)

