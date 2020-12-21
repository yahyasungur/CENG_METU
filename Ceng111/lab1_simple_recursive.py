def f(N):
    return N if N == 0 or N == 1 else (True if not f(N-1) else False)

print(f(1))
