% ein Prolog-Programm, das das Taylor-Polynom vom Grad 2
% einer Funktion an der Stelle 0 angibt 

% Taylor aufruf:
taylor2(Y,X,E) :- tfunc(Y,X,O),s(O,E).
% baue function
tfunc(Y,X,G0+G1*X+G2*X^2/2) :- glied0(Y,X,G0),glied1(Y,X,G1),glied2(Y,X,G2).
glied0(Y,X,E) :- ein(Y,X,E).
glied1(Y,X,E) :- ds(Y,X,A),ein(A,X,E).
glied2(Y,X,E) :- ds(Y,X,D0),ds(D0,X,D1),ein(D1,X,E).
% einsetzen
ein(A,X,E) :- twr(A,X,O),tw0(O,X,O1),s(O1,E).
% setze werte recursiv (taylor wert recursiv)
twr(F+Y,X,EW1+EW2) :- twr(F, X, E1),tw0(E1,X,EW1),
    			      twr(Y, X, E2),tw0(E2,X,EW2).
twr(F*Y,X,EW1*EW2) :- twr(F, X, E1),tw0(E1,X,EW1),
    			      twr(Y, X, E2),tw0(E2,X,EW2).
twr(F-Y,X,EW1-EW2) :- twr(F, X, E1),tw0(E1,X,EW1),
    			      twr(Y, X, E2),tw0(E2,X,EW2).
twr(F/Y,X,EW1/EW2) :- twr(F, X, E1),tw0(E1,X,EW1),
    			      twr(Y, X, E2),tw0(E2,X,EW2).
twr(X,_,X).

% setze werte atomar X=0
tw0(-(IN*cos(X*Y)),Y,IN) :- number(X),number(IN).
tw0(-(IN*sin(X*Y)),Y,0) :- number(X),number(IN).
tw0(sin(X*Y)*A,Y,0) :- number(X),number(A).
tw0(-sin(X*Y)*A,Y,0) :- number(X),number(A).
tw0(cos(X*Y),Y,1) :- number(X).
tw0(sin(X*Y),Y,0) :- number(X).
tw0(-sin(X*Y),Y,0) :- number(X).
tw0(-cos(X*Y),Y,-1) :- number(X).
tw0(sin(X+Y),X,E) :- E is sin(Y).
tw0(-sin(X+Y),X,E) :- E is -sin(Y).
tw0(cos(X+Y),X,E) :- E is cos(Y).
tw0(-cos(X+Y),X,E) :- E is -cos(Y).
tw0(sin(X),X,0).
tw0(-sin(X),X,0).
tw0(cos(X),X,1).
tw0(-cos(X),X,-1).
tw0(X^N,X,0) :- number(N).
tw0(N*X^N,X,0) :- number(N).
tw0(N^X,X,1) :- number(N).
tw0(X,X,0).
tw0(X,X,0).
tw0(X,_,X).

% verkettete Funktionen : trig
diff(sin(Y),X,IN*cos(Y)) :- X\=Y, diff(Y,X,IN).
diff(cos(Y),X,-sin(Y)*IN) :- X\=Y, diff(Y,X,IN).
diff(tan(Y),X,IN*sin(Y)/cos(Y)) :- X\=Y, diff(Y,X,IN).
% Produktregel
diff(X1*X,X,X1) :- number(X1),not(number(X)).
diff(X1*X2,X,Y1*X1) :- diff(X2,X,Y1),
    number(X1),not(number(X2)).
diff(X1*X2,X,Y1*X1) :- diff(X1,X,Y1),
    not(number(X1)),number(X2).
diff(X1*X2,X,X1*Y2+X2*Y1) :- diff(X1,X,Y1),diff(X2,X,Y2),
    not(number(X1)),not(number(X2)).
%  Haupt-Differensations-regeln
diff(X,X,1).
diff(C,X,0) :- number(C), X\==C.
diff(C*X,X, C) :- number(C), X\==C.
diff(-F,X,-DF) :- diff(F,X,DF).
% Potenz
diff(X^N,X,N*X^Z):- Z is N-1, number(N).
diff(K*X^N,X,K*N*X^Z):- Z is N-1, number(N), number(K).
diff(e^X,X,e^X).
diff(e^N*X,X,N*e^N*X):- number(N).
% verkettet: polynom mit potenz
diff(P^N, X, DP*(P^Z)*N) :- P\=X, Z is N-1, diff(P,X,DP).
% sum and dif
diff(A+B,X,DFX+DFY) :- diff(A,X,DFX),diff(B,X,DFY).
diff(A-B,X,DFX-DFY) :- diff(A,X,DFX),diff(B,X,DFY).
% trigon
diff(sin(X),X,cos(X)).
diff(cos(X),X,-sin(X)).
diff(tan(X),X,sin(X)/cos(X)).
% vereinfachung
s0(1*X,X).
s0(X*1,X).
s0(X/1,X).
s0(0+X,X).
s0(X+0,X).
s0(0*_,0).
s0(X*Y,E) :- E == (X*Y), number(X), number(Y).
s0(_*0,0).
s0(0/_,0).
% zahlen kuerzen
s0(N+V,X) :- number(N),number(V), X is N+V.
s0(N*X*V,E) :- number(N),number(V), Z is N*V, s0(Z*X,E).
s0(N*X/V,E) :- number(N),number(V), Z is N/V, s0(Z*X,E).
s0(N*X^1,N*X) :- number(N).
% end
s0(X,X).
% recursive vereinfachung
s(A+B,X) :- s(A,E1),s(B,E2),s0(E1+E2,X).
s(A-B,X) :- s(A,E1),s(B,E2),s0(E1-E2,X).
s(A*B,X) :- s(A,E1),s(B,E2),s0(E1*E2,X).
s(A/B,X) :- s(A,E1),s(B,E2),s0(E1/E2,X).
s(X,X).

% abfrage fuer ableitung
ds(F,X,DF) :- diff(F,X,S),s(S,REC),s0(REC,DF).