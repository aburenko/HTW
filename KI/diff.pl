diff(X,X,1).
diff(C,X,0) :- number(C), X\==C.
diff(C*X,X, C) :- number(C), X\==C.
diff(X^N,X,Z*X^Z):- Z is N-1, number(N).
diff(e^X,X,e^X).
diff(e^N*X,X,N*e^N*X):- number(N).
diff(A+B,X,DFX+DFY) :- diff(A,X,DFX),diff(B,X,DFY).
diff(A-B,X,DFX-DFY) :- diff(A,X,DFX),diff(B,X,DFY).
diff(-F,X,-DF) :- diff(F,X,DF).
%trigon
diff(sin(X),X,cos(X)).
diff(cos(X),X,-sin(X)).
diff(tan(X),X,sin(X)/cos(X)).

s0(X+X,X^2).
s0(1*X,X).
s0(X*1,X).
s0(X/1,X).
s0(0+X,X).
s0(X+0,X).
s0(X,X).

s(A+B,X) :- s(A,E1),s(B,E2),s0(E1+E2,X).
s(A-B,X) :- s(A,E1),s(B,E2),s0(E1-E2,X).
s(A*B,X) :- s(A,E1),s(B,E2),s0(E1*E2,X).
s(A/B,X) :- s(A,E1),s(B,E2),s0(E1/E2,X).
s(X,X).

%abfrage
ds(F,X,DF) :- diff(F,X,S),s(S,DF).
