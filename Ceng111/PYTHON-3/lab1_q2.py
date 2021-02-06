def decode_and_execute(memory,ins):
    if ins == "CLRMEM":
        return "NO ERROR"
    elif ins[:3] == "SUB":
        lst = ins.split(",")
        if int(lst[0][4:]) > 9 or int(lst[0][4:]) < 0:
            return "INVALID ADRESS"
        elif int(lst[1]) > 9 or int(lst[1]) < 0:
            return "INVALID ADRESS"
        else:
            return "NO ERROR"
    elif ins[:4] == "LOAD":
        lst = ins.split(",")
        if int(lst[0][5:]) > 9 or int(lst[0][4:]) < 0:
            return "INVALID ADRESS"
        elif lst[1].isdigit() == False:
            return "NOT A NUMBER"
        else:
            return "NO ERROR"
    elif ins[:4] == "SUBI":
        lst = ins.split(",")
        if int(lst[0][5:]) > 9 or int(lst[0][4:]) < 0:
            return "INVALID ADRESS"
        elif lst[1].isdigit() == False:
            return "NOT A NUMBER"
        else:
            return "NO ERROR"
    elif ins[:4] == "DIVI":
        lst = ins.split(",")
        if int(lst[0][5:]) > 9 or int(lst[0][4:]) < 0:
            return "INVALID ADRESS"
        elif lst[1].isdigit() == False:
            return "NOT A NUMBER"
        elif lst[1] == "0":
            return "DIVISION BY ZERO"
        else:
            return "NO ERROR"
    else:
        return "UNKNOWN INSTRUCTION"
