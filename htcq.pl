goal([0,0,0]).
en([X,Y,_]):-
    X>Y,
    Y>0.
en([X,Y,_]):-
    Y<3,
    Y>X.

f10([X,Y,1],[A,Y,0]):-
    X>=1,
    A is X-1.
f20([X,Y,1],[A,Y,0]):-
    X>=2,
    A is X-2.
f11([X,Y,1],[A,B,0]):-
    X>0,
    Y>0,
    A is X-1,
    B is Y-1.
f01([X,Y,1],[X,B,0]):-
    Y>=1,
    B is Y-1.
f02([X,Y,1],[X,B,0]):-
    Y>=2,
    B is Y-2.
b10([X,Y,0],[A,Y,1]):-
    X<3,
    A is X+1.
b20([X,Y,0],[A,Y,1]):-
    X<2,
    A is X+2.
b11([X,Y,0],[A,B,1]):-
    X<3,
    Y<3,
    A is X+1,
    B is Y+1.
b01([X,Y,0],[X,B,1]):-
    Y<3,
    B is Y+1.
b02([X,Y,0],[X,B,1]):-
    Y=<1,
    B is Y+2.

ts(X,Y):- f10(X,Y),\+ en(Y).
ts(X,Y):- f20(X,Y),\+ en(Y).
ts(X,Y):- f11(X,Y),\+ en(Y).
ts(X,Y):- f01(X,Y),\+ en(Y).
ts(X,Y):- f02(X,Y),\+ en(Y).
ts(X,Y):- b10(X,Y),\+ en(Y).
ts(X,Y):- b20(X,Y),\+ en(Y).
ts(X,Y):- b11(X,Y),\+ en(Y).
ts(X,Y):- b01(X,Y),\+ en(Y).
ts(X,Y):- b02(X,Y),\+ en(Y).

dfs(X,P,[X|P]):- goal(X).
dfs(X,P,Path):- ts(X,Y),X\=Y,\+ member(Y,P),dfs(Y,[X|P],Path).
