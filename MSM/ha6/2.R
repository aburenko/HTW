##################################################
##   Differentialgleichungen numerisch loesen   ##
##################################################
library(deSolve)

# Richtungsfeld Funktion (fuer 2d)
rf <- function(f,x,y,l=0.2){
  plot(0,0,col="white",xlim=c(min(x),max(x)),ylim=c(min(y),max(y)),xlab="x",ylab="y")
  for (i in 1:length(x)){
    for (j in 1:length(y)){
      w<-l/(2*sqrt(1+f(x[i],y[j])^2))
      lines(c(x[i]-w,x[i]+w),c(y[j]-w*f(x[i],y[j]),y[j]+w*f(x[i],y[j])) ) 
    }
  }
}

# Raeuber Beute #######################################
K1 <- 3.5
K2 <- 1.5
Alpha <- 1
Beta <- 0.1
f<-function(x,y){(1-(x+Alpha*y)/K1)/(1-(y+Beta*x)/K2)}
x<- seq(0,3, by = 0.1)
y<- seq(0,3, by = 0.11)
rf(f,x,y,0.1)



parameters <- c(K1=K1,K2=K2,Alpha=Alpha,Beta=Beta)
state <- c(X = 1, Y = 0.5)

RB<-function(t, state, parameters) {
  with(as.list(c(state, parameters)),{
    # rate of change
    dX <- (1-(X+Alpha*Y)/K1)
    dY <- (1-(Y+Beta*X)/K2)
    
    # return the rate of change
    list(c(dX, dY))
  })   # end with(as.list ...
}


# Zeitspanne fuer Loesung vorgeben
times <- seq(0, 20, by = 0.01)

# DGL Loesen
out <- ode(y = state, times = times, func = RB, parms = parameters)

# Wie sieht die Loesung aus...
head(out)

# Plotten
par(oma = c(0, 0, 3, 0))
plot(out[, "X"], xlab = "time", ylab = "-", type="l")
lines(out[, "Y"], xlab = "time", ylab = "-", type="l", col="red")
plot(out[, "X"], out[, "Y"], pch = ".", type="l")
mtext(outer = TRUE, side = 3, "Raeuber Beute Modell", cex = 1.5)

# Plot in Richtungsfeld
rf(f,x,y,0.1)
lines(out[, "X"], out[, "Y"], pch = ".", type="l" ,col="red")