:- module(main, [is_movie_directed_by/2, total_awards_nominated/2, all_movies_directed_by/2, total_movies_released_in/3, all_movies_released_between/4]).
:- [kb].

% DO NOT CHANGE THE UPPER CONTENT, WRITE YOUR CODE AFTER THIS LINE

is_movie_directed_by(Title,Director) :- movie(Title,Director,_,_,_,_).

total_awards_nominated(Title,Nominations) :- movie(Title,_,_,X,Y,Z),Nominations is X + Y + Z.

all_movies_directed_by(Director,Movies) :- findall(X,movie(X,Director,_,_,_,_),Movies).


total_movies_released_in([],_,0).
total_movies_released_in([H|T],Year,Count) :- total_movies_released_in(T,Year,Z),(movie(H,_,Year,_,_,_) -> Count is Z+1 ; Count is Z).


all_movies_released_between([],MinYear,MaxYear,[]).
all_movies_released_between([H|T],MinYear,MaxYear,MoviesBetweenGivenYears) :- all_movies_released_between(T,MinYear,MaxYear,Z),movie(H,_,Year,_,_,_),(Year =< MaxYear,Year >= MinYear -> append([H],Z,MoviesBetweenGivenYears) ; append([],Z,MoviesBetweenGivenYears)).
