""" def string_sum(x,y):
    a=int(x)+int(y)
    if a>9:
        return[str(a)[0],str(a)[1]]
    else:
        return ["0",str(a)[0]]
def string_op(x,y):
    # let's say x="7" and y="93"
    if len(x)==1:
        x="".join(["0",x])
    if len(y)==1:
        y="".join(["0",y])
    # purpose of these conditionals is to make initial numbers two digits so the code below will work
    # x="7" becomes x="07" but y="93" stays as y="93"
    ones_sum=string_sum(x[1],y[1])
    # adds ones digits together: ones_sum[0] will be reminder and ones_sum[1] will be their sum in mod 10
    # string_sum("7","3") will return ["1","0"]
    # ones_sum[0] will be "1" (tens digit) and ones_sum[1] will be "0" (ones digit)
    tens_sum=string_sum(x[0],y[0])
    # adds tens digits together: tens_sum[0] will be reminder and tens_sum[1] will be their sum in mod 10
    # string_sum("0","9") will return ["0","9"]
    # tens_sum[0] will be "0" (hundreds digit) and tens_sum[1] will be "9" (tens digit)
    c=string_sum(ones_sum[0],tens_sum[1])
    # adds reminder from addition of ones to the tens digit
    # string_sum("1","9") will return ["1","0"]
    # c[0] will be "1" (hundreds digit) and c[1] will be "0" (tens digit)
    d=string_sum(c[0],tens_sum[0])
    # adds reminder from the above equation to hundreds digit
    # string sum("1","0") will return ["0","1"]
    # d[0] will be "0" (thousands digit, irrelevant, will always be zero) and d[1] will be "1" (hundreds digit)
    answer="".join([d[1],c[1],ones_sum[1]])
    # this will join final hundreds, tens and ones digits together
    # (we could not uses plus sign so this was to only way i could think of)
    # d[1] is "1", c[1] is "0" and tens_sum[1] is "0" at this stage, so answer will be "100"
    if answer[0]=="0":
        answer=answer[1:]
    if answer[0]=="0":
        answer=answer[1:]
    # purpose of these two is to remove zeroes at the beginning
    # for example string_op("4","2") would return "006" without this but we want it to return "6"
    return answer """

def string_op(s1,s2):
    a = len(s1)
    b = len(s2)
    if a == 1 and b == 1:
        lst = string_sum(s1,s2)
        if lst[0] == "0":
            return lst[1]
        else:
            return "".join([lst[0],lst[1]])
    if a == 2 and b == 1:
        lst = string_sum(s1[1],s2)
        lst2 = string_sum(lst[0],s1[0])
        if lst2[0] == "0":
            if lst2[1] == "0":
                return lst[1]
            else:
                return "".join([lst2[1],lst[1]])
        else:
            return "".join([lst2[0],lst2[1],lst[1]])
    if a == 1 and b == 2:
        lst = string_sum(s2[1],s1)
        lst2 = string_sum(lst[0],s2[0])
        if lst2[0] == "0":
            if lst2[1] == "0":
                return lst[1]
            else:
                return "".join([lst2[1],lst[1]])
        else:
            return "".join([lst2[0],lst2[1],lst[1]])
    else:
        lst = string_sum(s1[1],s2[1])
        lst2 = string_sum(s1[0],s2[0])
        lst3 = string_sum(lst[0],lst2[1])
        if lst2[0] == "0":
            return "".join([lst3[1],lst[1]])
        else:
            return "".join([lst2[0],lst3[1],lst[1]])
