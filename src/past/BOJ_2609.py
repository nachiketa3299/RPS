a,b = map(int,input().split())
result_a = []
result_b = []

i=2
while True:
    if a==1:
        break
    elif a%i ==0:
        result_a.append(i)
        a=a/i
        i=2
    else:
        i+=1
        
i=2
while True:
    if b==1:
        break
    elif b%i == 0:
        result_b.append(i)
        b = b/i
        i=2
    else:
        i +=1


result_max = list(set(result_a) & set(result_b))
result_max_val = 1

for i in result_max:
    result_max_val *= i

print(result_max_val)

result_a.extend(result_b)
for i in result_max:
    result_a.remove(i)
result_a_val=1
for i in result_a:
    result_a_val = result_a_val*i
print(result_a_val)
