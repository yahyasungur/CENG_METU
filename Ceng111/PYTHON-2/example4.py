
# EXAMPLE-4

# Write a function named "process_vector" which performs the following operations on 3-d vectors:
#
#    scalar multiplication
#    magnitude
#    normalization
#
# The first argument is a string specifying the operation: "SM", "M" or "N"
#
#    SM: returns the scalar multiplication of two vectors
#    M: returns magnitude of a vector
#    N: returns the normalized version of a vector
#
# The second argument is a list containing one or two vector(s) depending on the type of the operation. A vector is represented a tuple: (x, y, z). E.g. (2.0, 3.0, 7.0).

def process_vector(command,lst):
    if command == "SM":
        result = lst[0][0]*lst[1][0]+lst[0][1]*lst[1][1]+lst[0][2]*lst[1][2]
    elif command == "M":
        result = (lst[0][0]**2+lst[0][1]**2+lst[0][2]**2)**(1/2)
    elif command == "N":
        magnitude = (lst[0][0]**2+lst[0][1]**2+lst[0][2]**2)**(1/2)
        result = (lst[0][0]/magnitude,lst[0][1]/magnitude,lst[0][2]/magnitude)
    return result


# SAMPLE INPUT/OUTPUTs:
# == Input ==
print( process_vector("SM", [(3.0, 4.0, 5.0), (2.0, 4.0, 6.0)]) )
# == Output ==
# 52.0

# == Input ==
print( process_vector("M", [(2.0, 7.0, 8.0)]) )
# == Output ==
# 10.816653826391969

# SOLUTION:
""" def process_vector(operation, vectors):
    if operation == "SM":
        return scalarMult(vectors[0], vectors[1])
    elif operation == "M":
        return magnitude(vectors[0])
    elif operation == "N":
        return normalize(vectors[0])
    else:
        return 'invalid'

def normalize(vec):
    magn = magnitude(vec)
    return (vec[0]/magn, vec[1]/magn, vec[2]/magn)

def magnitude(vec):
    import math
    return math.sqrt(scalarMult(vec, vec))

def scalarMult(v1, v2):
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2] """