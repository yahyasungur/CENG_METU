% person(Name, Age, Hobbies)
person(joseph, 27, reading).
person(jessica, 32, crafting).
person(michael, 22, reading).
person(william, 33, reading).
person(elizabeth, 30, television).
person(jennifer, 38, crafting).
person(patricia, 33, bird_watching).
person(charles, 39, bird_watching).
person(david, 31, bird_watching).
person(mary, 25, crafting).
person(barbara, 25, reading).
person(richard, 32, travelling).
person(james, 22, fishing).
person(susan, 32, reading).
person(karen, 40, bird_watching).
person(sarah, 25, crafting).
person(linda, 21, reading).
person(john, 28, reading).
person(thomas, 23, bird_watching).
person(robert, 22, television).

% example implementation for sum_age/2 predicate in sample PE.
% base case
sum_age([],0).
% recursive case
sum_age([Person|T], TotalAge) :-
    person(Person,Age,_),
    sum_age(T,TotalRest),
    TotalAge is Age + TotalRest.

% example implementation for max_age_of_hobby/3 predicate in sample PE.
% base case
max_age_of_hobby([],_,0).
% recursive case: 
% newly checked age is the new maximum
max_age_of_hobby([Person|T], Hobby, Age) :-
    person(Person, Age, Hobby),
    max_age_of_hobby(T,Hobby,RestMax),
    Age > RestMax.
% recursive case: 
% newly checked age is smaller than or equal to the current maximum
max_age_of_hobby([Person|T], Hobby, RestMax) :-
    person(Person, Age, Hobby),
    max_age_of_hobby(T,Hobby,RestMax),
    Age =< RestMax.
% recursive case:
% hobby of the person does not match the given hobby
max_age_of_hobby([Person|T], Hobby, RestMax) :-
    person(Person, _, AnotherHobby),
    Hobby \= AnotherHobby,
    max_age_of_hobby(T,Hobby,RestMax).
% here, comparing with \= instead of =\= is important!
% =\= compares the values of expressions
%%% since values of Hobby and AnotherHobby cannot be evaluated, the comparison gives an error.
%%% if instead we were comparing variables corresponding to numbers, using =\= would not be a problem.
% =\ checks if they match (in other words, if they unify)
%%% works for both cases.

% example implementation for person_in_range/4 predicate in sample PE.
% base case:
person_in_range([],_,_,[]).
% recursive case:
% age of the person is in the given interval
person_in_range([Person|T], A1, A2, [Person|Res]) :- 
    person(Person,Age,_),  
    Age =< A2, Age >= A1,
    person_in_range(T, A1, A2, Res).
% recursive case:
% age of the person is smaller than the minimum age
person_in_range([Person|T], A1, A2, Res):- 
    person(Person,Age,_), 
    Age < A1,
    person_in_range(T, A1, A2, Res).
% recursive case:
% age of the person is bigger than the maximum age
person_in_range([Person|T], A1, A2, Res):- 
    person(Person,Age,_), 
    Age > A2,
    person_in_range(T, A1, A2, Res).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% an example predicate: people_with_given_hobby/2
% people_with_given_hobby(Hobby, PeopleList)
% PeopleList: all people in the knowledge base that has the hobby "Hobby"

% sample query:
% ?- people_with_given_hobby(reading, PeopleList).
% PeopleList = [joseph, michael, william, barbara, susan, linda, john].

% we can use the base predicate findall/3:
people_with_given_hobby(Hobby, PeopleList) :- 
    findall(Name, person(Name, _, Hobby), PeopleList).


