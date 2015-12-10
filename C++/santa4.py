import hashlib

hash = hashlib.md5()
start = "yzbqklnj"
at = 0

while (hash.hexdigest()[0:6] != "000000"):
    at += 1
    hash = hashlib.md5((start + str(at)).encode())

print(at)
