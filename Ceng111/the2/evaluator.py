# 
# MODIFY get_data() AS YOU LIKE.
# DO NOT SEND THIS FILE TO US

import random
random.seed(111)




def get_data():
	"""Get the initial state of the individuals & the environment"""
	#	    [M, N,   D,   K, LAMBDA, MU,    universal_state]
	return [50, 100, 5, 80, 30, 0.55, [[(22, 14), 0, 'notmasked', 'notinfected'], [(19, 15), 7, 'notmasked', 'notinfected'], [(17, 16), 7, 'notmasked', 'notinfected'], [(26, 20), 3, 'notmasked', 'infected'], [(22, 21), 5, 'masked', 'infected'], [(25, 21), 3, 'notmasked', 'infected']]]