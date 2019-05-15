% Adjazenzrelation des ungerichteten Graphen (nicht effizient)
adj(X,Y) :- adj0(X,Y); adj0(Y,X).
adj0(X,Y) :- member((X,Y), [(1,2), (2,4), (2,5), (3,4), (3,6), (4,5)]).

goal(6).

% Breitensuche (Idee) - bereits besuchte Knoten werden nicht gespeichert
bfs1([H|T]) :-
	goal(H);
	findall(Node, adj(H, Node), Neighbors),
	append(T, Neighbors, Queue),
	write('Queue: '), writeln(Queue), % zur Illustration
	bfs1(Queue).

% Breitensuche
bfs([H|T], Discovered) :-
	goal(H);
	findall(Node, (adj(H, Node), not(member(Node, Discovered))), NewNeighbors),
	append(T, NewNeighbors, Queue),
	append(Discovered, NewNeighbors, Dc),
	write('Queue: '), writeln(Queue), % zur Illustration
	bfs(Queue, Dc).

% Tiefensuche
dfs2(Node) :-
	goal(Node);
	adj(Node, Neighbor),
	dfs2(Neighbor).

% Tiefensuche modifiziert
dfs(Node,Discovered,Ergebnis) :-
	(goal(Node),reverse(Discovered,Ergebnis));
	adj(Node, Neighbor),
    not(member(Neighbor,Discovered)),
	dfs(Neighbor,[Neighbor|Discovered],Ergebnis).    