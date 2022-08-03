% CHANGES DONE TO THIS FILE WILL BE OVERWRITTEN. 
% IT WILL HAVE NO EFFECT ON YOUR GRADE.

:- module(kb, [vegan/1, vegetarian/1, omnivorous/1, base/1, protein/1, topping/1, condiment/1, sauce/1, not_vegetarian/1, not_vegan/1]).

% vegan(Name), vegetarian(Name), and omnivorous(Name) predicates, 
% defining the diets of customers
vegan(chidi).
vegetarian(tahani).
omnivorous(eleanor).
omnivorous(jason).

% base(Name) predicate, options for salad base
base(lettuce).

% protein(Name) predicate, options for proteins
protein(smoked_turkey).
protein(hellim_cheese).
protein(smoked_tofu).

% topping(Name) predicate, options for toppings
topping(cucumber).
topping(tomato).
topping(pickled_onion).
topping(olive).

% condiment(Name) predicate, options for condiments
condiment(mustard).
condiment(mayonnaise).
condiment(ranch).

% sauce(Name) predicate, options for sauces
sauce(olive_oil).
sauce(lemon_juice).
sauce(balsamic_vinegar).

% not_vegan(Item) and not_vegetarian(Item) predicates, 
% defining dietary restrictions
not_vegetarian(Item) :- 
    member(Item, [smoked_turkey]), !.
not_vegan(Item) :- 
    not_vegetarian(Item), !;
    member(Item, [hellim_cheese,mayonaise,ranch]), !.



salad_type([],'vegan').
salad_type([H|T],Type) :- salad_type(T,Z),((not(not_vegan(H)), not(Z = 'vegetarian'),not(Z = 'omnivorous')) -> (Type = 'vegan';Type = 'vegetarian';Type = 'omnivorous',!) ; ((not(not_vegetarian(H)),not(Z = 'omnivorous')) -> (Type = 'vegetarian';Type = 'omnivorous',!); Type = 'omnivorous',!)).

person_can_eat(_,[],_) :- !.
person_can_eat(Person,[H|T],Salad) :- person_can_eat(Person,T,Z),salad_type(H,Type), (omnivorous(Person) -> (Salad = H;Salad = Z,!);((vegetarian(Person),not(Type = 'vegan')) -> (Salad = H;Salad = Z,!); (Type == 'vegan' -> (Salad = H;Salad = Z,!);Salad = Z,!))).


