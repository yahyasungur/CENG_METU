from stacknqueue import *

def tournament(totalLife, teams, matches):
	for team in teams:
		team.append(totalLife)
	changes = CreateStack()	# this will be used as stack
	for i in (matches):
		if type(i) == list:
			if i[0] == 'disqualify':
				for team in teams:
					if team[0] == i[1]:
						team[1] = -1
			else:
				loser = i[0] if i[2] == 1 else i[1]
				for team in teams:
					if team[0] == loser:
						Push(team[:], changes)
						team[1] -= 1
		elif i == 'cancelMatch':
			lastMatch = Pop(changes)
			for team in teams:
				if team[0] == lastMatch[0]:
					team[1] = lastMatch[1]
	return teams

#lives = 2
#teams = [['Team1'], ['Team2']]
#matches = [['Team1','Team2', 0], ['Team2','Team1', 1], ['Team2','Team1', 0]]
#print(tournament(lives,teams,matches))
#[['Team1', 1], ['Team2', 0]]


#lives = 2
#teams = [['Team1'], ['Team2']]
#matches = [['Team1','Team2', 0], ['Team2','Team1', 1],'cancelMatch', ['Team2','Team1', 0]]
#print(tournament(lives,teams,matches))
#[['Team1', 1], ['Team2', 1]])


#lives = 2
#teams = [['Team1'],['Team2'],['Team3']]
#matches = [['Team1','Team2', 0], ['Team2','Team1', 1],'cancelMatch',['Team2','Team1', 0], ['disqualify','Team3']]
#print(tournament(lives,teams,matches))
#[['Team1', 1], ['Team2', 1], ['Team3', -1]]


#lives = 2
#teams = [['Team1'],['Team2'],['Team3']]
#matches = [['Team1','Team2', 0], ['Team2','Team1', 1], ['Team2','Team1', 0],'cancelMatch','cancelMatch','cancelMatch', ['disqualify','Team3']]
#print(tournament(lives,teams,matches))
#[['Team1', 2], ['Team2', 2], ['Team3', -1]]


#lives = 3
#teams = [['Team1'], ['Team2'], ['Team3'], ['Team4'], ['Team5']]
#matches = [['Team1','Team2', 0], ['Team2','Team1', 1],'cancelMatch', ['Team2','Team1', 0], ['Team2','Team1', 1], ['disqualify','Team3'], ['Team2','Team4', 1], ['Team1','Team4',0], ['Team1','Team4', 0],'cancelMatch', ['disqualify','Team5']]
#print(tournament(lives,teams,matches))
#[['Team1', 2], ['Team2', 0], ['Team3', -1], ['Team4', 2], ['Team5', -1]]