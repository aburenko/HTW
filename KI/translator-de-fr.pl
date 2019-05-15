% de <-> fr übersetzer

satz(DE,FR) :- nominal_phrase(DE,FR,RestED,RestEFR,Einzahl),verbal_phrase(RestED,RestEFR,Einzahl).

nominal_phrase(DE,FR,RestED,RestEFR,Einzahl) :- artikel_n(DE,FR,RestD,RestF,ArtD,ArtF,Einzahl),
    adj_n(RestD,RestF,ArtD,ArtF,R1D,R1F,Einzahl),
    obj(R1D,R1F,ArtD,ArtF,RestED,RestEFR,Einzahl).

artikel_n(DE,FR,RD,RF,ArtD,ArtF,s) :- match(ArtD, DE, RD), memberN([die,der],ArtD, N),
    					  match(ArtF, FR, RF), memberN([la,le],ArtF,N),not(errNF(N)).
artikel_n(DE,FR,RD,RF,ArtD,ArtF,p) :- match(ArtD, DE, RD), memberN([die],ArtD, N),
    					  match(ArtF, FR, RF), memberN([les],ArtF,N),not(errNF(N)).

adj_n(RD,RF,die,la,R1D,R1F,s) :- match(AdjD, RD, R1D), memberN([grosse, schoene],AdjD,N),
    					match(AdjF, RF, R1F), memberN([grande, belle],AdjF,N),not(errNF(N)).
adj_n(RD,RF,der,le,R1D,R1F,s) :- match(AdjD, RD, R1D), memberN([grosse, schoene],AdjD,N),
    					match(AdjF, RF, R1F), memberN([grand, bel],AdjF,N),not(errNF(N)).
adj_n(RD,RF,die,les,R1D,R1F,p) :- match(AdjD, RD, R1D), memberN([grossen, schoenen],AdjD,N),
    					match(AdjF, RF, R1F), memberN([grandes, belles],AdjF,N),not(errNF(N)).
adj_n(RD,RF,_,_,RD,RF,_).

% maskulin
obj(R1D,R1F,der,le,R2D,R2F,s) :- match(ObjD, R1D, R2D), memberN([kater,mann],ObjD,N),
    					match(ObjF, R1F, R2F), memberN([chat,homme],ObjF,N),not(errNF(N)).
% femenin
obj(R1D,R1F,die,la,R2D,R2F,s) :- match(ObjD, R1D, R2D), memberN([frau],ObjD,N),
    					match(ObjF, R1F, R2F), memberN([femme],ObjF,N),not(errNF(N)).
%plural
obj(R1D,R1F,die,les,R2D,R2F,p) :- match(ObjD, R1D, R2D), memberN([frauen],ObjD,N),
    					match(ObjF, R1F, R2F), memberN([femmes],ObjF,N),not(errNF(N)).

verbal_phrase(RestD,RestFR,Einzahl) :- verb_trans(RestD,RestFR,Einzahl);
    verb(RestD,RestFR,[],[],Einzahl).

verb(DE,FR,RestD,RestFR,s) :- match(VD, DE, RestD), memberN([schlaeft,sieht],VD,N),
    					match(VF, FR, RestFR), memberN([dort,voit],VF,N),not(errNF(N)).
verb(DE,FR,RestD,RestFR,p) :- match(VD, DE, RestD), memberN([schlafen,sehen],VD,N),
    					match(VF, FR, RestFR), memberN([dort,voient],VF,N),not(errNF(N)).

verb_trans(RestD,RestFR,Einzahl) :- verb(RestD,RestFR,Rest1D,Rest1FR,Einzahl),
    artikel_a(Rest1D,Rest1FR,Rest2D,Rest2FR,ArtD,ArtF,EinzahlV),
    adj_a(Rest2D,Rest2FR,ArtD,ArtF,R3D,R3F,EinzahlV),
    obj_a(ArtD,ArtF,R3D,R3F,RED,REF,EinzahlV),leer(RED,REF).

leer(RD,RF) :- RD = [], RF = [].

% *_a fuer Akkusativ
%singular
artikel_a(DE,FR,RestD,RestFR,ArtD,ArtF,s) :- match(ArtD, DE, RestD), memberN([die,den],ArtD,N),
    					match(ArtF, FR, RestFR), memberN([la,le],ArtF,N),not(errNF(N)).
%plural
artikel_a(DE,FR,RestD,RestFR,ArtD,ArtF,p) :- match(ArtD, DE, RestD), memberN([die],ArtD,N),
    					match(ArtF, FR, RestFR), memberN([les],ArtF,N),not(errNF(N)).
% adjektiv unteschiedlich nach Artikel
adj_a(DE,FR,den,le,RD,RF,s) :- match(VD, DE, RD), memberN([schoenen, grossen],VD,N),
    					match(VF, FR, RF), memberN([belle, grande],VF,N),not(errNF(N)).
adj_a(DE,FR,die,la,RD,RF,s) :- match(VD, DE, RD), memberN([schoene, grosse],VD,N),
    					match(VF, FR, RF), memberN([belle, grande],VF,N),not(errNF(N)).
adj_a(DE,FR,die,les,RD,RF,p) :- match(VD, DE, RD), memberN([schoenen, grossen],VD,N),
    					match(VF, FR, RF), memberN([belles, grandes],VF,N),not(errNF(N)).
adj_a(RD,RF,_,_,RD,RF,_).

% maskulin
obj_a(den,le,R2D,R2F,RED,REF,s) :- match(ObjD,R2D,RED),
    					match(ObjF,R2F,REF),obj_a_s_m(ObjD,ObjF).
% femenin
obj_a(die,la,R2D,R2F,RED,REF,s) :- match(ObjD,R2D,RED),match(ObjF,R2F,REF), 
    					obj_a_s_f(ObjD,ObjF).
%plural
obj_a(die,les,R2D,R2F,RED,REF,p) :- match(ObjD,R2D,RED),
    					match(ObjF,R2F,REF), obj_a_p(ObjD,ObjF).
obj_a_s_m(mann,homme).
obj_a_s_f(frau,femme).
obj_a_p(frauen,maenner).
obj_a_p(maenner,hommes).

match(X, [X|Rest], Rest).

% 2nd parameter is member of 1st on place of 3rd parametr
memberN([],_,-1).
memberN([A|_],B,1) :- A=B.
memberN([_|Tail],X,N) :- memberN(Tail, X, N1), N1>=1, (N is N1 + 1 ; errNF(N)).
errNF(-1). % by not found returns -1

