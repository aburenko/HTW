path <- "D:/edu/MSM/R/ha2.1/test2.txt"
conn <- file(path,open="r")
lines <- readLines(conn)
# read lines out
namen <- unlist(strsplit(lines[1], ";"))
richtungen <- unlist(strsplit(lines[2], ";"))
widerstaende <- unlist(strsplit(lines[3], ";"))
# spannungsquellen
q <- as.numeric(unlist(strsplit(lines[4], ";")))
close(conn)

# B ... Inzidenzmatrix des Netzwerkes
B = matrix(0:0, nrow = length(richtungen), ncol = length(namen))
# fill die Matrix B
for (i in 1:length(richtungen)) {
	richtung = unlist(strsplit(richtungen[i], ","))
	a = richtung[1]
	b = richtung[2]
	B[i, match(a, namen)] = -1
	B[i, match(b, namen)] = 1
}
B <- B[,1:length(namen)-1]

# C ... Diagonalmatrix fuer Wiederstaende
C = diag(widerstaende, length(widerstaende))

# leftpart 
l = t(B) %*% C %*% B
# rightpart 
r = t(B) %*% q

x = solve(l, r)
e = -B %*% x
y = e + q

# potentiale, wobei letztes auf 0 gesetzt ist
x
# spannung
e
# strom
y