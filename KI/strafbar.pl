ausfuehr(mueller,nordkorea,merc).
ausfuehr(mueller,nordkorea,polo).

ausfuehr(meier,china,merc).
ausfuehr(meier,china,polo).

luxusgut(merc).
gut(polo).

strafbar(X) :- luxusgut(Z), ausfuehr(X,nordkorea,Z).
