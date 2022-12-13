def cmp(l1, l2):
    if isinstance(l1, int) and isinstance(l2, int):
        if l1 < l2:
            return "Smaller"
        elif l1 == l2:
            return "Equal"
        else:
            return "Greater"
    if isinstance(l1, int):
        l1 = [l1]
    if isinstance(l2, int):
        l2 = [l2]
    for left, right in zip(l1, l2):
        if left == None:
            return "Smaller"
        if right == None:
            return "Greater"
        check = cmp(left, right)
        if check != "Equal":
            return check
    if len(l1) < len(l2):
        return "Smaller"
    elif len(l1) == len(l2):
        return "Equal"
    else:
        return "Greater"
    
def s_list(list, key):
    i = 0
    j = 0
    while i < len(list):
        j = i
        while j > 0 and key(list[j - 1], list[j]) == "Greater":
            list[j - 1], list[j] = list[j], list[j - 1]
            j -= 1
        i += 1
    return list

p1 = 0
ind = 1
lst = list()
with open('input.txt') as f:
    lines = f.read().splitlines()
    for i in range(0, len(lines), 3):
        left = eval(lines[i])
        right = eval(lines[i + 1])
        lst.append(left)
        lst.append(right)
        issorted = cmp(left, right) != "Greater"
        if issorted:
            #print(left, right)
            #print(ind)
            p1 += ind
        ind += 1
print("Part 1:", p1)
lst.append([[2]])
lst.append([[6]])
lst = s_list(lst, cmp)
print("Part 2:", (lst.index([[2]]) + 1) * (lst.index([[6]]) + 1))