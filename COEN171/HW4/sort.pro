quicksort([], []).
quicksort([H|T], X) :-
    partition(T, H, L, U),
    quicksort(L, S),
    quicksort(U, G),
    append(S, [H|G], X).

partition([], _, [], []).
partition([H|T], P, [H|L], U) :- H =< P,
    partition(T, P, L, U).
partition([H|T], P, L, [H|U]) :- H > P,
    partition(T, P, L, U).
