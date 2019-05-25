solution(Puzzle,ReturnPath) :- goal(Goal),idas(Puzzle,Goal,ReturnPath).

test(ReturnPath) :- testPuzzle(P),solution(P,ReturnPath).

testPuzzle([[9,1,3],[4,2,5],[7,8,6]]).

adj([A,B,C],[L,B,C]) :- member(9,A),adjLine(A,L). 
adj([A,B,C],[A,L,C]) :- member(9,B),adjLine(B,L). 
adj([A,B,C],[A,B,L]) :- member(9,C),adjLine(C,L).

adj([AIN,BIN,CIN],[Ar,Br,Cr]) :- rotateR([AIN,BIN,CIN],[A,B,C]),member(9,A),adjLine(A,L),rotateL([L,B,C],[Ar,Br,Cr]). 
adj([AIN,BIN,CIN],[Ar,Br,Cr]) :- rotateR([AIN,BIN,CIN],[A,B,C]),member(9,B),adjLine(B,L),rotateL([A,L,C],[Ar,Br,Cr]). 
adj([AIN,BIN,CIN],[Ar,Br,Cr]) :- rotateR([AIN,BIN,CIN],[A,B,C]),member(9,C),adjLine(C,L),rotateL([A,B,L],[Ar,Br,Cr]). 

rotateR([
    	[E00,E01,E02],
    	[E10,E11,E12],
    	[E20,E21,E22]
    ],
    [
     	[E20,E10,E00],
      	[E21,E11,E01],
      	[E22,E12,E02]
    ]
).
rotateL([
     	[E20,E10,E00],
      	[E21,E11,E01],
      	[E22,E12,E02]
    ],
    [
    	[E00,E01,E02],
    	[E10,E11,E12],
    	[E20,E21,E22]
    ]
).

% horizontale Bewegungen
% middle
adjLine([E0,9,E2], [E0,E2,9]).
adjLine([E0,9,E2], [9,E0,E2]).
% corners
adjLine([9,E1,E2], [E1,9,E2]).
adjLine([E0,E1,9], [E0,9,E1]).


goal([[1,2,3],[4,5,6],[7,8,9]]).
goalF( [1, 2, 3, 4, 5, 6, 7, 8, 9]).

% IDA*-Suche

% f: Heuristische Bewertungsfunktion
% h: Heuristische KostenschÃ¤tzfunktion
% [Head|Tail]: Aktueller Pfad, Head: aktueller Knoten 
f([Head|Tail], F) :- 
	length(Tail, G),
	h(Head, H),
	F is G+H. 

% Kostenschaetzfunktion
h(X,Hamming) :- flatten(X,Flatt),goalF(GF),maplist(diff,Flatt,GF,Y),sumlist(Y,Hamming).
diff(X,Y,0) :- X == Y.
diff(_,_,1).	 

% Node: aktueller Knoten
% Goal: Zielknoten
% Path: Liste der Knoten auf dem Pfad bis Node
% ReturnPath: Rueckgabe, wenn ein Pfad zum Ziel gefunden wurde
% adj: Adjazenz eines Knotens
flDfs(Node, Goal, Path, FLimit, ReturnPath) :-
	Node == Goal, reverse(Path, ReturnPath);
	adj(Node,NewNeighbor), not(member(NewNeighbor,Path)),
	f([NewNeighbor|Path], F), F =< FLimit,
	flDfs(NewNeighbor, Goal, [NewNeighbor|Path], FLimit, ReturnPath).

idasLoop(Start, Goal, FLimit, ReturnPath) :-
	flDfs(Start, Goal, [Start], FLimit, ReturnPath);
	% Schranke fuer f wird um feste Schrittweite erhaeht (einfach zu programmieren)
	FL is FLimit+1,
	idasLoop(Start, Goal, FL, ReturnPath).

idas(Start, Goal, ReturnPath) :-
	% Da f zulaessig ist, sind die Kosten bis zum Ziel mindestens FL
	f([Start], FLimit),
	idasLoop(Start, Goal, FLimit, ReturnPath).
