mann(robert).
mann(thomas).
mann(jan).
mann(jens).
mann(tim).
mann(hans).
mann(winfried).
mann(wilhelm).
mann(kurt).
frau(paula).
frau(elke).
frau(frieda).
frau(heike).
frau(sandra).
frau(anke).
frau(christine).
frau(eva).
frau(julia).
frau(jutta).
frau(anne).
eltern(wilhelm, frieda, robert).
eltern(kurt, lisa, sandra).
eltern(winfried, elke, thomas).
eltern(hans, paula, chistine).
eltern(thomas, christine, eva).
eltern(robert, sandra, jan).
eltern(robert, sandra, jens).
eltern(robert, sandra, julia).
eltern(robert, sandra, jutta).
eltern(jan, eva, anne).
eltern(jan, eva, anke).
eltern(jens, heike, tim).
% X ist Bruder von Y
bruder(X,Y) :- mann(X), eltern(PAPA,MAMA,X),eltern(PAPA,MAMA,Y), X\=Y.
% X ist Schwester von Y
schwester(X,Y) :- frau(X), eltern(PAPA,MAMA,X),eltern(PAPA,MAMA,Y), X\=Y.
% Z ist Enkel von X und Y
enkel(X,Y,Z) :- eltern(X,Y,Kind), eltern(Kind,F,Z), frau(F), mann(Kind).
enkel(X,Y,Z) :- eltern(X,Y,Kind), eltern(M,Kind,Z), mann(M), frau(Kind).
% X ist kind von Y
kind(X,Y) :- eltern(Y,_,X);eltern(_,Y,X).
% enkel zweistellig
% X ist enkel von Y
enkel(X,Y) :- kind(X,Z),kind(Z,Y).
% X ist Onkel von Y
onkel(X,Y) :- eltern(P,M,Y), bruder(M,X), mann(P), mann(X).
onkel(X,Y) :- eltern(P,M,Y), bruder(P,X), frau(M), mann(X).
% X ist Tante von Y
tante(X,Y) :- eltern(P,M,Y), bruder(M,X), mann(P), frau(X).
tante(X,Y) :- eltern(P,M,Y), bruder(P,X), frau(M), frau(X).  
% Vorfahr
% X ist Vorfahr von Y
vorfahr(X,Y) :- kind(Y,X).
vorfahr(X,Y) :- kind(Y,Z), vorfahr(X,Z).
