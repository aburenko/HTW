% In dem Satz [der, kater, sieht, die, maus] ist das Subjekt kater, das Pradikat sieht und das Objekt maus.

satz(In, Rest, Art, S,  P, Art1, O) :- nominal_phrase(In, R, S, Art), verbal_phrase(R, Rest, P, O, Art1).
%Beispiele für Aufrufe
%frage([wer,jagt,die,maus],[eine,katze,jagt,die,maus] , Antwort)
%frage([wen,jagt,eine,katze],[eine,katze,jagt,die,maus] , Antwort)
frage(Frage, Satz, Antwort) :- (  baue_frage_subject(Frage, Fragewort, Art, S, P); baue_frage_object(Frage, Fragewort, Art1, O, P) ),
    satz(Satz, [], Art, S,  P, Art1, O), baue_antwort(Antwort, Fragewort, Art, S, Art1, O).

baue_antwort([Art,O], wen, _, _, Art, O).
baue_antwort([Art,S], wer, Art, S, _, _).

baue_frage_object(Frage, wer, Art, S, P) :- match(wer,Frage,E),match(P,E,E1),match(Art,E1,E2),match(S,E2,[]).
baue_frage_subject(Frage, wen, Art, S, P) :- match(wen,Frage,E),match(P,E,E1),match(Art,E1,E2),match(S,E2,[]).

nominal_phrase(In, Rest, S, Art) :- artikel(In, R, Art), nomen(R, Rest, S). % S ist subject, Art is Atrikel

verbal_phrase(In, Rest, P, O, Art) :- verb(In, R, P), nominal_phrase(R, Rest, O, Art).

artikel(In, Rest, Art) :- match(Art, In, Rest), member(Art, [eine,die,der]).

verb(In, Rest, P) :- match(P, In, Rest), member(P, [jagt,sieht]).

nomen(In, Rest, S) :-  match(S, In, Rest), member(S, [katze,kater,maus]).

match(X, [X|Rest], Rest).