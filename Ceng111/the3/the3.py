# This function finds the root of the tree
def root_finder(lst):
    names = []
    for a in range(len(lst)):
        names.append(lst[a][0])

    for i in range(len(lst)):
        if len(lst[i]) == 2 and type(lst[i][1]) != tuple:
            continue
        
        for j in range(1,len(lst[i])):
            if lst[i][j][1] in names:
                names.remove(lst[i][j][1])

    for n in range(len(lst)):
        if names[0] == lst[n][0]:
            break

    return lst[n]

# This function arranges list to tree structure (parent-child)
def tree_builder(lst,tree,part):
    tree.append(part)
    if len(part) == 2 and type(part[1]) != tuple:
        return

    for i in range(1,len(part)):
        name = part[i][1]
        for j in range(len(lst)):
            if lst[j][0] == name:
                tree_builder(lst[:j]+lst[j+1:],tree,lst[j])

# This function builds a nested representation of tree from a list which is in the form (parent-child)
def nested_tree(lst):
    for i in range(1,len(lst)):
        name = lst[-i][0]
        for j in range(i+1,len(lst)+1):
            if len(lst[-j]) == 2 and type(lst[-j][1]) != tuple:
                continue
            for n in range(1,len(lst[-j])):
                if type(lst[-j][n]) == tuple and lst[-j][n][1] == name:
                    lst[-j][n] = (lst[-j][n][0],lst[-i])
                    break

# This function converts any list to tree structure by using above functions
def tree_converter(part_list):
    tree = []
    tree_builder(part_list,tree,root_finder(part_list))
    nested_tree(tree)
    return tree[0]

# This function calculates the price of composit object(root of tree) recursively
def price_helper(tree,multi):
    sm = 0.0
    if len(tree) == 2 and type(tree[1]) != tuple:
        return tree[1]*multi
    else:
        for i in range(1,len(tree)):
            sm += price_helper(tree[i][1],multi*tree[i][0])
        return sm

def calculate_price(part_list):
    tree = tree_converter(part_list)
    return price_helper(tree,1.0)

# This function finds the required parts to construct composit object(root of tree) recursively
def required_parts_helper(tree,multi,lst):
    if len(tree) == 2 and type(tree[1]) != tuple:
        lst.append((multi,tree[0]))
        return 
    else:
        for i in range(1,len(tree)):
            required_parts_helper(tree[i][1],multi*tree[i][0],lst)
        return

def required_parts(part_list):
    tree =  tree_converter(part_list)
    lst = []
    required_parts_helper(tree,1,lst)
    return lst

# This function computes the quantity of basic parts which are short in stock iteratively
def stock_check(part_list, stock_list):
    required = required_parts(part_list)
    short = []

    for i in range(len(required)):
        name = required[i][1]
        check = 1
        for j in range(len(stock_list)):
            if stock_list[j][1] == name:
                check = 0
                if required[i][0] > stock_list[j][0]:
                    short.append((name,required[i][0]-stock_list[j][0]))
        if check == 1:
            short.append((name,required[i][0]))
    return short