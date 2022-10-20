import random

hexchars = ["0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"]

key = ""
text = ""
for i in range(16):
    key += random.choice(hexchars)

with open ("key.txt", "w") as f:
    for i in range(2 * 1024 * 1024 * 200):
        f.write(random.choice(hexchars))

print(key)
# print(text)

# for i in range(2 * 1024 * 10):
#     text += random.choice(hexchars)

# print(key)
# print(text)