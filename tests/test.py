import random
random_bi_list=[]
for i in range(0,6):
    # 随机生成l位bit数
    l=5
    random_binary=bin(random.getrandbits(l))[2:]
    print(random_binary)
    random_bi_list.append(random_binary)
print(random_bi_list)

bitnum = bin(random.getrandbits(5))
print(bitnum)
print(bitnum[2:])
