import urllib.request
import os.path
import zipfile
import sys

secure_connection = False
if not secure_connection:
    import os, ssl
    if (not os.environ.get('PYTHONHTTPSVERIFY', '') and
            getattr(ssl, '_create_unverified_context', None)):
        ssl._create_default_https_context = ssl._create_unverified_context

if os.path.isfile('primes.txt'):
    print('File already exists')
    sys.exit(0)

preurl = 'https://primes.utm.edu/lists/small/millions/primes'
posturl = '.zip'
maxp = 50

for i in range (1, maxp + 1):
    txtname = 'primes' + str(i) + '.txt'
    if os.path.isfile(txtname):
        print(txtname + ' exists')
        continue
    zipname = 'primes' + str(i) + '.zip'
    if os.path.isfile(zipname):
        print(zipname + ' exists')
    else:
        url = preurl + str(i) + posturl
        print('Downloading from ' + url)
        urllib.request.urlretrieve(url, zipname)
        print('Saved to ' + zipname)
    with zipfile.ZipFile(zipname, 'r') as zip_ref:
        zip_ref.extractall('.')
        print('Extracted ' + zipname)

with open('primes.txt', 'w') as mainfile:
    for i in range (1, maxp + 1):
        txtname = 'primes' + str(i) + '.txt'
        with open(txtname, 'r') as txtfile:
            lines = txtfile.readlines()
            lines = [j for j in lines if j != '\n']
            mainfile.writelines(lines[1:len(lines)])
            mainfile.write('\n')
        print(txtname + ' is written to primes.txt, deleting it')
        os.remove(txtname)
