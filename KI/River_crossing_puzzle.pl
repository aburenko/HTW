ort(X) :- member(X, [start, pilinitz]).
adj(A,B) :- move(A,B), check(B).
% Bedeutung der Listen [Ziege, Kohlkopf, Wolf, Fahrer]
move([A,K,W,A],[B,K,W,B]) :- ort(A),ort(B), A\=B. % bringt ziege rüber
move([Z,A,W,A],[Z,B,W,B]) :- ort(A),ort(B), A\=B. % bringt kohlkopf rüber
move([Z,K,A,A],[Z,K,B,B]) :- ort(A),ort(B), A\=B. % bringt wolf rüber
move([Z,K,W,A],[Z,K,W,B]) :- ort(A),ort(B), A\=B. % fahrer fährt rüber
check([Z,K,W,F]) :- (Z\==W;Z==F),(Z\==K;Z==F).
goal([pilinitz,pilinitz,pilinitz,pilinitz]).


solution(Path) :- idDfs([start,start,start,start],Path).



% Iterative Tiefensuche (Iterative deepening depth-first search)

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

idDfs(Start, ReturnPath) :- idDfsLoop(Start, 1, ReturnPath).