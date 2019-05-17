% Labyrinth
% [top,right,bot,left] 1 closed 0 open
%   0    1    2   3

lab(L) :- L = [ 
         	[[1,0,1,1],[1,0,0,0],[1,1,1,0],[1,0,0,1],[1,1,0,0]],
           	[[1,0,1,1],[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,1,0,1]],
           	[[1,1,0,1],[0,1,0,1],[1,0,1,1],[1,0,0,0],[0,1,0,0]],
           	[[0,1,0,1],[0,0,1,1],[1,0,1,0],[0,1,0,0],[0,1,1,1]],
           	[[0,0,1,1],[1,0,1,0],[1,0,1,0],[0,0,1,0],[1,0,1,0]]
         ].

%   reihe,spalte,richtung,ergebnis   
way(Idx1,Idx2,Direction,Result) :-  lab(L),nth0(Idx1,L,L1),
    nth0(Idx2,L1,L2),nth0(Direction,L2,Result).
    
adj(A,B) :-move(A,B), check(B).

move([Y,X],[Y1,X]) :- way(Y,X,0,R),R is 0,Y1 is Y-1. % top
move([Y,X],[Y,X1]) :- way(Y,X,1,R),R is 0,X1 is X+1. % right
move([Y,X],[Y1,X]) :- way(Y,X,2,R),R is 0,Y1 is Y+1. % bot
move([Y,X],[Y,X1]) :- way(Y,X,3,R),R is 0,X1 is X-1. % left

check([Y,X]) :- not(bombe([Y,X])), X >= 0, Y >= 0.
bombe(A) :- A == [3,2].
goal([4,4]).


solution(ReturnPath) :- dlDfs([1,1],[[1,1]], 20, ReturnPath).

%solution(Path) :- idDfs([1,1],Path).


% % Iterative Tiefensuche (Iterative deepening depth-first search)

% Node: aktueller Knoten
% Path: Liste der Knoten auf dem Pfad bis Node
% ReturnPath: Rueckgabe, wenn ein Pfad zum Ziel gefunden wurde
dlDfs(Node, Path, DepthLimit, ReturnPath) :-
	goal(Node), reverse(Path, ReturnPath);
	DepthLimit > 0,
	adj(Node,NewNeighbor), not(member(NewNeighbor,Path)),
  L is DepthLimit-1,
	dlDfs(NewNeighbor, [NewNeighbor|Path], L, ReturnPath).

idDfsLoop(Start, D, ReturnPath) :-
	dlDfs(Start, [Start], D, ReturnPath);
	% Wenn die Tiefensuche mit Schranke D nicht erfolgreich war, wird mit Schranke D+1 weitergesucht.
  L is D+1,
	idDfsLoop(Start, L, ReturnPath).

idDfs(Start, ReturnPath) :- idDfsLoop(Start, 5, ReturnPath).