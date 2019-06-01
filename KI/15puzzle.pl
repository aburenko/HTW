solution(Puzzle,ReturnPath) :- goal(Goal),idas(Puzzle,Goal,ReturnPath),printPath(ReturnPath),!.

test(ReturnPath) :- testPuzzle(P),solution(P,ReturnPath).

printBox(Box) :- maplist(writeln,Box),write('\n').
printPath(Path) :- maplist(printBox,Path).

testPuzzle2([[1,2,3,4],[5,6,7,8],[16,15,14,13],[9,10,11,12]]).
testPuzzle3([[1,2,3,6],[9,11,4,12],[16,10,7,3],[13,8,5,2]]).
testPuzzle4([[1,2,3,4],[5,6,7,8],[16,10,11,12],[9,13,14,15]]).
testPuzzle5([[1,2,3,16],[5,6,7,4],[9,10,11,8],[13,14,15,12]]).
testPuzzle6([[1,2,3,4],[5,6,7,8],[15,16,12,11],[9,14,10,13]]).
testPuzzleS([[1,2,3,4],[5,7,8,11],[9,6,16,12],[13,15,14,10]]).


adj0([A,B,C,D],[L,B,C,D]) :- member(16,A),adjLine(A,L). 
adj0([A,B,C,D],[A,L,C,D]) :- member(16,B),adjLine(B,L). 
adj0([A,B,C,D],[A,B,L,D]) :- member(16,C),adjLine(C,L).
adj0([A,B,C,D],[A,B,C,L]) :- member(16,D),adjLine(D,L).

adj(X,Y) :- adj0(X,Y);(rotateR(X,S),adj0(S,R),rotateR(Y,R)).

rotateR([
    	[E00,E01,E02,E03],
    	[E10,E11,E12,E13],
    	[E20,E21,E22,E23],
    	[E30,E31,E32,E33]
    ],
    [
     	[E30,E20,E10,E00],
      	[E31,E21,E11,E01],
      	[E32,E22,E12,E02],
      	[E33,E23,E13,E03]
    ]
).

% horizontale Bewegungen
adjLine0([E0,E1,E2,16],[E0,E1,16,E2]).
adjLine0([E0,E1,16,E2],[E0,16,E1,E2]).
adjLine0([E0,16,E1,E2],[16,E0,E1,E2]).

adjLine(X,Y) :-
	adjLine0(X,Y) ;
	adjLine0(Y,X).


goal([[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]]).
goalF([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]).

% IDA*-Suche

% f: Heuristische Bewertungsfunktion
% h: Heuristische KostenschÃ¤tzfunktion
% [Head|Tail]: Aktueller Pfad, Head: aktueller Knoten 
f([Head|Tail], F) :- 
	length(Tail, G),
	h(Head, H),
	F is G+H,!.

h(Head,H) :- hm(Head,Hm),hc(Head,Hc), H is Hm+Hc.

% % Manhattan-Distanz
hm(Head,G) :- flatten(Head,Flatt),goalF(GF),maplist(elemDistance,Flatt,GF,Y),sumlist(Y,G).
elemDistance(Elem,Pos,Distance) :- RealX is (Pos-1)  mod 4, RealY is (Pos-1)  div 4,
    							   EndX  is (Elem-1) mod 4, EndY  is (Elem-1) div 4,
    XDiff is RealX-EndX, YDiff is RealY-EndY, abs(XDiff,XDabs), abs(YDiff,YDabs), Distance is XDabs + YDabs.

% Kostenschaetzfunktion
% =====================
% checkQPPos takes 0 for q and 1 for p
% checks for every SubList
hc(X,2) :- nth0(N,X,SubList), checkQPPos(N,SubList,0,1).
hc(_,0).
% p must be on the right side of q
% p,q must have end positions in List
% end position of p must be on the left side of q
% checks for every q and p
checkQPPos(N,List,IdxQ,IdxP) :- nth0(IdxQ,List,Q),nth0(IdxP,List,P),checkQPEnd(N,Q,P);
    							nextQS(IdxQ,IdxP,IdxQN,IdxPN),checkQPPos(N,List,IdxQN,IdxPN).
% get new index for q and p
nextQS(IQ,IP,IQ,IPN) :- IQ < 2, IP < 3, IPN is IP+1.
nextQS(IQ,IP,IQN,IPN) :- IQ < 2, IP is 3, IQN is IQ+1, IPN is IQN+1.
% checks positions
checkQPEnd(N,Q,P) :- (N*4)+1<Q,Q=<(N+1)*4,(N*4)+1<P,P=<(N+1)*4,P<Q.

% Node: aktueller Knoten
% Goal: Zielknoten
% Path: Liste der Knoten auf dem Pfad bis Node
% ReturnPath: RÃ¼ckgabe, wenn ein Pfad zum Ziel gefunden wurde
% adj: Adjazenz eines Knotens
flDfs(Node, Goal, Path, FLimit, ReturnPath) :-
	Node == Goal, reverse(Path, ReturnPath);
	adj(Node,NewNeighbor), not(member(NewNeighbor,Path)),
	f([NewNeighbor|Path], F),
  	%writeln(Node), 
    F =< FLimit,
	flDfs(NewNeighbor, Goal, [NewNeighbor|Path], FLimit, ReturnPath).

idasLoop(Start, Goal, FLimit, ReturnPath) :-
	flDfs(Start, Goal, [Start], FLimit, ReturnPath);
	% Schranke fÃ¼r f wird um feste Schrittweite erhÃ¶ht (einfach zu programmieren)
	FL is FLimit+1,
	idasLoop(Start, Goal, FL, ReturnPath).

idas(Start, Goal, ReturnPath) :-
	% Da f zulÃ¤ssig ist, sind die Kosten bis zum Ziel mindestens FL
	f([Start], FLimit),
	idasLoop(Start, Goal, FLimit, ReturnPath).
	 

% schema fuer p,q
% 0 1 2 3
% q p
% q   p
% q     p
%   q p
%   q   p
%     q p