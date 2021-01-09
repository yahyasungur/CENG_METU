def  decode_and_execute(mem,ins):
    lst = []
    ad = "0129356874"
    if ins == "CLRMEM":
        lst.append("NO ERROR")
    elif ins[:4] == "SUB ":
        index = ins.find(",")
        adress1 = ins[4:index]
        adress2 = ins[index+2:]
        if ad.find(adress1) == -1 and ad.find(adress2) == -1:
            lst.append("INVALID ADRESS")
            lst.append("INVALID ADRESS")
        elif ad.find(adress1) == -1:
            lst.append("INVALID ADRESS")
        elif ad.find(adress2) == -1:
            lst.append("INVALID ADRESS")
        else:
            lst.append("NO ERROR")
    elif ins[:4] == "LOAD":
        a = 1
        index = ins.find(",")
        adress1 = ins[5:index]
        num = ins[index+2:]
        if ad.find(adress1) == -1:
            lst.append("INVALID ADRESS")
            a = 0
        if num.isdecimal() == False:
            lst.append("NOT A NUMBER")
            a = 0
        if a:
            lst.append("NO ERROR")
    elif ins[:4] == "SUBI":
        a = 1
        index = ins.find(",")
        adress1 = ins[5:index]
        num = ins[index+2:]
        if ad.find(adress1) == -1:
            lst.append("INVALID ADRESS")
            a = 0
        if num.isdecimal() == False:
            lst.append("NOT A NUMBER")
            a = 0
        if a:
            lst.append("NO ERROR")
    elif ins[:4] == "DIVI":
        a = 1
        index = ins.find(",")
        adress1 = ins[5:index]
        num = ins[index+2:]
        if ad.find(adress1) == -1:
            lst.append("INVALID ADRESS")
            a = 0
        if num.isdecimal() == False:
            lst.append("NOT A NUMBER")
            a = 0
        if num == "0":
            lst.append("DIVISION BY ZERO")
            a = 0
        if a:
            lst.append("NO ERROR")
    else:
        lst.append("UNKNOWN INSTRUCTION")
    return lst