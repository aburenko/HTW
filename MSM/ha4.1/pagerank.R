# include library
library(expm)

# init file
path <- "D:/edu/MSM/R/ha4.1/041_pagerank2.txt"
conn <- file(path, open="r")
lines <- readLines(conn)
close(conn)

# read lines out
label <- unlist(strsplit(lines[1], ";"))
links <- unlist(strsplit(lines[2], ";"))

# init variables, where N ist number of steps and n teleporting ratio
N <- 150
n <- 0.9

# create Uebergangsmatrix P
PSize <- length(label)
P <- matrix(0, nrow = PSize, ncol = PSize)
# fill it
for (i in 1:PSize) {
    linksForLabel <- unlist(strsplit(links[i], ","))
    labelsNumber <- length(linksForLabel)
    if (labelsNumber <= 0) {
	  # eine Seite, die zu keiner anderen Seite verlinkt, verlinkt auf sich selbst 
        P[i, i] = 1
        next
    }
    for (linkIndex in 1:labelsNumber ) {
        link <- as.numeric(linksForLabel[linkIndex])
        P[i, link] = 1/labelsNumber
    }
}

# nehme gleichverteilung als startverteilung
p0<- matrix(1/PSize, nrow = 1, ncol = PSize)

# function to make verteilung human readable
# where P ist Uebergangsmatrix
humanReadable <- function(P) {
    PtoN<- P %^% N
    randomWalk <- as.vector(p0 %*% PtoN)
    # random walk
    dataRW <- data.frame(label, randomWalk)
    # sort it
    dataRW <- dataRW[order(-randomWalk),]
    verteilung <- as.vector(dataRW[['label']])
    verteilung
}

# verteilung berechnen
# random walk
humanReadable(P)
# random walk with teleport
P <- n * P + (1 - n) * matrix(1, nrow = PSize, ncol = PSize) / PSize
humanReadable(P)

# eof