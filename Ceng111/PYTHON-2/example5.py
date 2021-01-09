
#  EXAMPLE-5

#  Write a function named "tictactoe" that determines the outcome of the game in a given tic-tac-toe board.
#
#    The dimensions of the board is fixed and equal to three
#    The board is given as a list of strings
#    Each element of the list is a string containing three characters: 'X', 'O' or '-'
#    For instance the following board is represented as ['XOX', 'OOX', 'XXO']
#
#    XOX
#    OOX
#    XXO
#
#    The function should return 'X', 'O' or 'tie' depending on the outcome of the game
#    If there are three consecutive 'X's vertically or horizontally 'X' wins the game
#    If there are three consecutive 'O's vertically or horizontally 'O' wins the game
#    Otherwise the result is a 'tie'
#    Note that there will be no case where both players win

def tictactoe(lst):
    if lst[0] == "XXX" or lst[1] == "XXX" or lst[2] == "XXX":
        return "X"
    elif lst[0][0] == lst[1][0] == lst[2][0] == "X" or lst[0][1] == lst[1][1] == lst[2][1] == "X" or lst[0][2] == lst[1][2] == lst[2][2] == "X":
        return "X"
    elif lst[0] == "OOO" or lst[1] == "OOO" or lst[2] == "OOO":
        return "O"
    elif lst[0][0] == lst[1][0] == lst[2][0] == "O" or lst[0][1] == lst[1][1] == lst[2][1] == "O" or lst[0][2] == lst[1][2] == lst[2][2] == "O":
        return "O"
    else:
        return "tie"

# SAMPLE INPUT/OUTPUTs:
# == Input ==
print( tictactoe(['XOX', 'OOX', 'XXO']) )
# == Output ==
# 'tie'

# == Input ==
print( tictactoe(['XXO', 'OOX', 'XXX']) )
# == Output ==
# 'X'

# == Input ==
print( tictactoe(['XOO', 'XOX', 'XXO']) )
# == Output ==
# 'X'

# == Input ==
print( tictactoe(['XOO', 'XOO', 'OXO']) )
# == Output ==
# 'O'

# SOLUTION:
""" def tictactoe(board):
    # check horizontals
    if board[0] == 'XXX' or board[1] == 'XXX' or board[2] == 'XXX':
        return 'X'
    if board[0] == 'OOO' or board[1] == 'OOO' or board[2] == 'OOO':
        return 'O'
    # check verticals
    if check_verticals(board, 'X'):
        return 'X'
    elif check_verticals(board, 'O'):
        return 'O'
    else:
        return 'tie'

def check_verticals(board, ch):
    return ((board[0][0] == ch and board[1][0] == ch and board[2][0] == ch) or \
        (board[0][1] == ch and board[1][1] == ch and board[2][1] == ch) or \
        (board[0][2] == ch and board[1][2] == ch and board[2][2] == ch)) """