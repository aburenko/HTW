# include libraries
library(deSolve)
library(rootSolve)

r   <- 1/3
K   <- 25
B <- 0.1
V0 <- 3

# G ist wachstum der vegetation
G <- function (x) r*x*(1-x/K)
# c ist verzehr einer Kuh
cvonv <- function (x) (B*x*x)/(V0*V0 + x*x)
# r Entwicklung der (Menge der) Vegetation V auf einer Kuhweide
VnachT10 <- function (x) G(x) - 10*c(x)
VnachT20 <- function (x) G(x) - 20*c(x)
VnachT30 <- function (x) G(x) - 30*c(x)

abstand <- 30
xvalues <- seq(0, 25, 0.1)

plot(xvalues, VnachT10(xvalues), type="l", col="green")
AAV10 <- uniroot.all(VnachT10,lower = 0, upper = 100)
points(AAV10, VnachT10(AAV10), col = "green", pch = 16)

par(new=TRUE)

plot(xvalues,VnachT20(xvalues), type="l")
AAV20 <- uniroot.all(VnachT20,lower = 0, upper = 100)
points(AAV20, VnachT20(AAV20), col = "black", pch = 16)

par(new=TRUE)

plot(xvalues,VnachT30(xvalues), type="l", col="red")
AAV30 <- uniroot.all(VnachT30,lower = 0, upper = 100)
points(AAV30, VnachT30(AAV30), col = "red", pch = 16)



# eof
