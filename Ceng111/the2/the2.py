#
# WRITE YOUR CODE HERE AND SEND ONLY THIS FILE TO US.
#
# DO NOT DEFINE get_data() here. Check before submitting

import math
import random
from evaluator import *    # get_data() will come from this import

data = get_data()
M = data[0]
N = data[1]
D = data[2]
K = data[3]
LAMBDA = data[4]
MU = data[5]
state = data[6]
size = len(state)

def new_move():
	global data
	global M #vertical
	global N #horizontal
	global D
	global K
	global LAMBDA
	global MU
	global state
	global size

	for i in range(size):
		direction = random.choices(["Forward","Forward Right","Right","Backward Right","Backward","Backward Left","Left","Forward Left"], weights = [(1/2)*MU,(1/8)*MU,(1/2)*(1-MU-(MU**2)),(2/5)*(MU**2),(1/5)*(MU**2),(2/5)*(MU**2),(1/2)*(1-MU-(MU**2)),(1/8)*MU], k = 1)
		if state[i][1] == 0:

			if direction[0] == "Forward":
				check = 1
				new_coordinate = (state[i][0][0],state[i][0][1]+1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] <= M:
					state[i][1] = 0
					state[i][0] = new_coordinate

			elif direction[0] == "Forward Right":
				check = 1
				new_coordinate = (state[i][0][0]-1,state[i][0][1]+1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] <= M and new_coordinate[0] >= 0:
					state[i][1] = 1
					state[i][0] = new_coordinate

			elif direction[0] == "Right":
				check = 1
				new_coordinate = (state[i][0][0]-1,state[i][0][1])
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[0] >= 0:
					state[i][1] = 2
					state[i][0] = new_coordinate

			elif direction[0] == "Backward Right":
				check = 1
				new_coordinate = (state[i][0][0]-1,state[i][0][1]-1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] >= 0 and new_coordinate[0] >= 0:
					state[i][1] = 3
					state[i][0] = new_coordinate

			elif direction[0] == "Backward":
				check = 1
				new_coordinate = (state[i][0][0],state[i][0][1]-1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] >= 0:
					state[i][1] = 4
					state[i][0] = new_coordinate

			elif direction[0] == "Backward Left":
				check = 1
				new_coordinate = (state[i][0][0]+1,state[i][0][1]-1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] >= 0 and new_coordinate[0] <= N:
					state[i][1] = 5
					state[i][0] = new_coordinate

			elif direction[0] == "Left":
				check = 1
				new_coordinate = (state[i][0][0]+1,state[i][0][1])
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[0] <= N:
					state[i][1] = 6
					state[i][0] = new_coordinate

			elif direction[0] == "Forward Left":
				check = 1
				new_coordinate = (state[i][0][0]+1,state[i][0][1]+1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] <= M and new_coordinate[0] <= N:
					state[i][1] = 7
					state[i][0] = new_coordinate
#---------------------------------------------------------
		elif state[i][1] == 1:

			if direction[0] == "Forward":
				check = 1
				new_coordinate = (state[i][0][0]-1,state[i][0][1]+1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] <= M and new_coordinate[0] >= 0:
					state[i][1] = 1
					state[i][0] = new_coordinate

			elif direction[0] == "Forward Right":
				check = 1
				new_coordinate = (state[i][0][0]-1,state[i][0][1])
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[0] >= 0:
					state[i][1] = 2
					state[i][0] = new_coordinate

			elif direction[0] == "Right":
				check = 1
				new_coordinate = (state[i][0][0]-1,state[i][0][1]-1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] >= 0 and new_coordinate[0] >= 0:
					state[i][1] = 3
					state[i][0] = new_coordinate

			elif direction[0] == "Backward Right":
				check = 1
				new_coordinate = (state[i][0][0],state[i][0][1]-1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] >= 0:
					state[i][1] = 4
					state[i][0] = new_coordinate

			elif direction[0] == "Backward":
				check = 1
				new_coordinate = (state[i][0][0]+1,state[i][0][1]-1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] >= 0 and new_coordinate[0] <= N:
					state[i][1] = 5
					state[i][0] = new_coordinate

			elif direction[0] == "Backward Left":
				check = 1
				new_coordinate = (state[i][0][0]+1,state[i][0][1])
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[0] <= N:
					state[i][1] = 6
					state[i][0] = new_coordinate

			elif direction[0] == "Left":
				check = 1
				new_coordinate = (state[i][0][0]+1,state[i][0][1]+1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] <= M and new_coordinate[0] <= N:
					state[i][1] = 7
					state[i][0] = new_coordinate

			elif direction[0] == "Forward Left":
				check = 1
				new_coordinate = (state[i][0][0],state[i][0][1]+1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] <= M:
					state[i][1] = 0
					state[i][0] = new_coordinate
#---------------------------------------------------------
		elif state[i][1] == 2:
			if direction[0] == "Forward":
				check = 1
				new_coordinate = (state[i][0][0]-1,state[i][0][1])
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[0] >= 0:
					state[i][1] = 2
					state[i][0] = new_coordinate

			elif direction[0] == "Forward Right":
				check = 1
				new_coordinate = (state[i][0][0]-1,state[i][0][1]-1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] >= 0 and new_coordinate[0] >= 0:
					state[i][1] = 3
					state[i][0] = new_coordinate

			elif direction[0] == "Right":
				check = 1
				new_coordinate = (state[i][0][0],state[i][0][1]-1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] >= 0:
					state[i][1] = 4
					state[i][0] = new_coordinate

			elif direction[0] == "Backward Right":
				check = 1
				new_coordinate = (state[i][0][0]+1,state[i][0][1]-1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] >= 0 and new_coordinate[0] <= N:
					state[i][1] = 5
					state[i][0] = new_coordinate

			elif direction[0] == "Backward":
				check = 1
				new_coordinate = (state[i][0][0]+1,state[i][0][1])
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[0] <= N:
					state[i][1] = 6
					state[i][0] = new_coordinate

			elif direction[0] == "Backward Left":
				check = 1
				new_coordinate = (state[i][0][0]+1,state[i][0][1]+1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] <= M and new_coordinate[0] <= N:
					state[i][1] = 7
					state[i][0] = new_coordinate

			elif direction[0] == "Left":
				check = 1
				new_coordinate = (state[i][0][0],state[i][0][1]+1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] <= M:
					state[i][1] = 0
					state[i][0] = new_coordinate

			elif direction[0] == "Forward Left":
				check = 1
				new_coordinate = (state[i][0][0]-1,state[i][0][1]+1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] <= M and new_coordinate[0] >= 0:
					state[i][1] = 1
					state[i][0] = new_coordinate
#---------------------------------------------------------
		elif state[i][1] == 3:

			if direction[0] == "Forward":
				check = 1
				new_coordinate = (state[i][0][0]-1,state[i][0][1]-1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] >= 0 and new_coordinate[0] >= 0:
					state[i][1] = 3
					state[i][0] = new_coordinate

			elif direction[0] == "Forward Right":
				check = 1
				new_coordinate = (state[i][0][0],state[i][0][1]-1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] >= 0:
					state[i][1] = 4
					state[i][0] = new_coordinate

			elif direction[0] == "Right":
				check = 1
				new_coordinate = (state[i][0][0]+1,state[i][0][1]-1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] >= 0 and new_coordinate[0] <= N:
					state[i][1] = 5
					state[i][0] = new_coordinate

			elif direction[0] == "Backward Right":
				check = 1
				new_coordinate = (state[i][0][0]+1,state[i][0][1])
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[0] <= N:
					state[i][1] = 6
					state[i][0] = new_coordinate

			elif direction[0] == "Backward":
				check = 1
				new_coordinate = (state[i][0][0]+1,state[i][0][1]+1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] <= M and new_coordinate[0] <= N:
					state[i][1] = 7
					state[i][0] = new_coordinate

			elif direction[0] == "Backward Left":
				check = 1
				new_coordinate = (state[i][0][0],state[i][0][1]+1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] <= M:
					state[i][1] = 0
					state[i][0] = new_coordinate

			elif direction[0] == "Left":
				check = 1
				new_coordinate = (state[i][0][0]-1,state[i][0][1]+1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] <= M and new_coordinate[0] >= 0:
					state[i][1] = 1
					state[i][0] = new_coordinate

			elif direction[0] == "Forward Left":
				check = 1
				new_coordinate = (state[i][0][0]-1,state[i][0][1])
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[0] >= 0:
					state[i][1] = 2
					state[i][0] = new_coordinate
#---------------------------------------------------------
		elif state[i][1] == 4:

			if direction[0] == "Forward":
				check = 1
				new_coordinate = (state[i][0][0],state[i][0][1]-1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] >= 0:
					state[i][1] = 4
					state[i][0] = new_coordinate

			elif direction[0] == "Forward Right":
				check = 1
				new_coordinate = (state[i][0][0]+1,state[i][0][1]-1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] >= 0 and new_coordinate[0] <= N:
					state[i][1] = 5
					state[i][0] = new_coordinate

			elif direction[0] == "Right":
				check = 1
				new_coordinate = (state[i][0][0]+1,state[i][0][1])
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[0] <= N:
					state[i][1] = 6
					state[i][0] = new_coordinate

			elif direction[0] == "Backward Right":
				check = 1
				new_coordinate = (state[i][0][0]+1,state[i][0][1]+1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] <= M and new_coordinate[0] <= N:
					state[i][1] = 7
					state[i][0] = new_coordinate

			elif direction[0] == "Backward":
				check = 1
				new_coordinate = (state[i][0][0],state[i][0][1]+1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] <= M:
					state[i][1] = 0
					state[i][0] = new_coordinate

			elif direction[0] == "Backward Left":
				check = 1
				new_coordinate = (state[i][0][0]-1,state[i][0][1]+1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] <= M and new_coordinate[0] >= 0:
					state[i][1] = 1
					state[i][0] = new_coordinate

			elif direction[0] == "Left":
				check = 1
				new_coordinate = (state[i][0][0]-1,state[i][0][1])
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[0] >= 0:
					state[i][1] = 2
					state[i][0] = new_coordinate

			elif direction[0] == "Forward Left":
				check = 1
				new_coordinate = (state[i][0][0]-1,state[i][0][1]-1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] >= 0 and new_coordinate[0] >= 0:
					state[i][1] = 3
					state[i][0] = new_coordinate
#---------------------------------------------------------
		elif state[i][1] == 5:

			if direction[0] == "Forward":
				check = 1
				new_coordinate = (state[i][0][0]+1,state[i][0][1]-1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] >= 0 and new_coordinate[0] <= N:
					state[i][1] = 5
					state[i][0] = new_coordinate

			elif direction[0] == "Forward Right":
				check = 1
				new_coordinate = (state[i][0][0]+1,state[i][0][1])
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[0] <= N:
					state[i][1] = 6
					state[i][0] = new_coordinate

			elif direction[0] == "Right":
				check = 1
				new_coordinate = (state[i][0][0]+1,state[i][0][1]+1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] <= M and new_coordinate[0] <= N:
					state[i][1] = 7
					state[i][0] = new_coordinate

			elif direction[0] == "Backward Right":
				check = 1
				new_coordinate = (state[i][0][0],state[i][0][1]+1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] <= M:
					state[i][1] = 0
					state[i][0] = new_coordinate

			elif direction[0] == "Backward":
				check = 1
				new_coordinate = (state[i][0][0]-1,state[i][0][1]+1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] <= M and new_coordinate[0] >= 0:
					state[i][1] = 1
					state[i][0] = new_coordinate

			elif direction[0] == "Backward Left":
				check = 1
				new_coordinate = (state[i][0][0]-1,state[i][0][1])
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[0] >= 0:
					state[i][1] = 2
					state[i][0] = new_coordinate

			elif direction[0] == "Left":
				check = 1
				new_coordinate = (state[i][0][0]-1,state[i][0][1]-1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] >= 0 and new_coordinate[0] >= 0:
					state[i][1] = 3
					state[i][0] = new_coordinate

			elif direction[0] == "Forward Left":
				check = 1
				new_coordinate = (state[i][0][0],state[i][0][1]-1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] >= 0:
					state[i][1] = 4
					state[i][0] = new_coordinate
#---------------------------------------------------------
		elif state[i][1] == 6:

			if direction[0] == "Forward":
				check = 1
				new_coordinate = (state[i][0][0]+1,state[i][0][1])
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[0] <= N:
					state[i][1] = 6
					state[i][0] = new_coordinate

			elif direction[0] == "Forward Right":
				check = 1
				new_coordinate = (state[i][0][0]+1,state[i][0][1]+1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] <= M and new_coordinate[0] <= N:
					state[i][1] = 7
					state[i][0] = new_coordinate

			elif direction[0] == "Right":
				check = 1
				new_coordinate = (state[i][0][0],state[i][0][1]+1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] <= M:
					state[i][1] = 0
					state[i][0] = new_coordinate

			elif direction[0] == "Backward Right":
				check = 1
				new_coordinate = (state[i][0][0]-1,state[i][0][1]+1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] <= M and new_coordinate[0] >= 0:
					state[i][1] = 1
					state[i][0] = new_coordinate

			elif direction[0] == "Backward":
				check = 1
				new_coordinate = (state[i][0][0]-1,state[i][0][1])
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[0] >= 0:
					state[i][1] = 2
					state[i][0] = new_coordinate

			elif direction[0] == "Backward Left":
				check = 1
				new_coordinate = (state[i][0][0]-1,state[i][0][1]-1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] >= 0 and new_coordinate[0] >= 0:
					state[i][1] = 3
					state[i][0] = new_coordinate

			elif direction[0] == "Left":
				check = 1
				new_coordinate = (state[i][0][0],state[i][0][1]-1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] >= 0:
					state[i][1] = 4
					state[i][0] = new_coordinate

			elif direction[0] == "Forward Left":
				check = 1
				new_coordinate = (state[i][0][0]+1,state[i][0][1]-1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] >= 0 and new_coordinate[0] <= N:
					state[i][1] = 5
					state[i][0] = new_coordinate
#---------------------------------------------------------
		elif state[i][1] == 7:

			if direction[0] == "Forward":
				check = 1
				new_coordinate = (state[i][0][0]+1,state[i][0][1]+1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] <= M and new_coordinate[0] <= N:
					state[i][1] = 7
					state[i][0] = new_coordinate

			elif direction[0] == "Forward Right":
				check = 1
				new_coordinate = (state[i][0][0],state[i][0][1]+1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] <= M:
					state[i][1] = 0
					state[i][0] = new_coordinate

			elif direction[0] == "Right":
				check = 1
				new_coordinate = (state[i][0][0]-1,state[i][0][1]+1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] <= M and new_coordinate[0] >= 0:
					state[i][1] = 1
					state[i][0] = new_coordinate

			elif direction[0] == "Backward Right":
				check = 1
				new_coordinate = (state[i][0][0]-1,state[i][0][1])
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[0] >= 0:
					state[i][1] = 2
					state[i][0] = new_coordinate

			elif direction[0] == "Backward":
				check = 1
				new_coordinate = (state[i][0][0]-1,state[i][0][1]-1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] >= 0 and new_coordinate[0] >= 0:
					state[i][1] = 3
					state[i][0] = new_coordinate

			elif direction[0] == "Backward Left":
				check = 1
				new_coordinate = (state[i][0][0],state[i][0][1]-1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] >= 0:
					state[i][1] = 4
					state[i][0] = new_coordinate

			elif direction[0] == "Left":
				check = 1
				new_coordinate = (state[i][0][0]+1,state[i][0][1]-1)
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[1] >= 0 and new_coordinate[0] <= N:
					state[i][1] = 5
					state[i][0] = new_coordinate

			elif direction[0] == "Forward Left":
				check = 1
				new_coordinate = (state[i][0][0]+1,state[i][0][1])
				for j in range(i):
					if state[j][0] == new_coordinate:
						check = 0
				if check != 0 and new_coordinate[0] <= N:
					state[i][1] = 6
					state[i][0] = new_coordinate
#----------------infection part--------------------------
	passed = []
	for i in range(size):
		for j in range(i+1,size):
			if state[i][3] != state[j][3]:
				distance = math.sqrt(pow((state[i][0][0]-state[j][0][0]),2) + pow((state[i][0][1]-state[j][0][1]),2))
				if distance <= D:
					if state[i][2] == "masked" and state[j][2] == "masked":
						mini = min(1,(K/((distance)**2)))/(LAMBDA**2)
					elif state[i][2] == "masked" or state[j][2] == "masked":
						mini = min(1,(K/((distance)**2)))/(LAMBDA)
					else:
						mini = min(1,(K/((distance)**2)))
					
					infection = random.choices(["infected","notinfected"],weights=[mini,1-mini])

					if infection[0] == "infected":
						if state[i][3] == "notinfected":
							passed.append(i)
						elif state[j][3] == "notinfected":
							passed.append(j)
	
	for i in range(size):
		if i in passed:
			state[i][3] = "infected"
	
	return state
