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
a<-2; c<-1;
f<-function(x,y){(-c*y*(1-x))/(a*x*(1-y))}
x<- seq(0,3, by = 0.1)
y<- seq(0,3, by = 0.11)
rf(f,x,y,0.1)



parameters <- c(a = a, c =  c)
state <- c(X = 1, Y = 0.5)

RB<-function(t, state, parameters) {
  with(as.list(c(state, parameters)),{
    # rate of change
    dX <- a*X - a*X*Y
    dY <- -c*Y + c*X*Y
    
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


# Raueber Beute beschraenkte Ressourcen ######################################
m<-2;  K<-2.5; b<-0.7; mt<-1; d<-1.6;

f<-function(x,y){ (-mt*y  + d*x*y)/(m*x -(m/K)*x^2 - b*x*y)}
x<- seq(0,3, by = 0.1)
y<- seq(0,4, by = 0.1)
rf(f,x,y,0.1)


parameters <- c(m = m, K=K , b=b, mt=mt, d=d)
state <- c(X = 3, Y = 0.5)
#stateGG <- c(X=0,Y=0)
#stateGG <- c(X=K,Y=0)
#stateGG <- c(X=mt/d,Y=(m-m*mt/(K*d))/b)


RB<-function(t, state, parameters) {
  with(as.list(c(state, parameters)),{
    # rate of change
    dX <- m*X -(m/K)*X^2 - b*X*Y
    dY <- -mt*Y  + d*X*Y
    
    # return the rate of ch$v=0$ange
    list(c(dX, dY))
  })   # end with(as.list ...
}


times <- seq(0, 20, by = 0.01)
out <- ode(y = state, times = times, func = RB, parms = parameters)
head(out)


#par(oma = c(0, 0, 1, 0))
plot(out[, "X"], xlab = "time", ylab = "-", type="l")
lines(out[, "Y"], xlab = "time", ylab = "-", type="l", col="red")
plot(out[, "Y"], xlab = "time", ylab = "-", type="l")
lines(out[, "X"], xlab = "time", ylab = "-", type="l", col="red")
plot(out[, "X"], out[, "Y"], pch = ".", type="l")
#mtext(outer = TRUE, side = 3, "Raeuber Beute Modell", cex = 1.5)

rf(f,x,y,0.1)
lines(out[, "X"], out[, "Y"], pch = ".", type="l" ,col="red")


# Mechanischer Oszillator, konstante Krafteinwirkung #############################
c<-1;  m<-1; k<-3; g<-9.80665; F0<-0

f<-function(y,v){ ( (-c*v-k*y-m*g-F0)/m)/(v)}
y<- seq(-7,-1, by = 0.2)
v<- seq(-2,5, by = 0.2)
rf(f,y,v,0.15)


parameters <- c(c = c, m=m , k=k, F0=F0, g=g)
state <- c(Y = -7, V = 0)


MO<-function(t, state, parameters) {
  with(as.list(c(state, parameters)),{
    # rate of change
    dY <- V
    dV <- (-c*V-k*Y-m*g-F0)/m
    # return the rate of ch$v=0$ange
    list(c(dY, dV))
  })   # end with(as.list ...
}


times <- seq(0, 20, by = 0.01)
out <- ode(y = state, times = times, func = MO, parms = parameters)
head(out)


#par(oma = c(0, 0, 1, 0))
plot(out[, "Y"], xlab = "time", ylab = "y", type="l")
lines(out[, "V"], xlab = "time", ylab = "v", type="l", col="red")
plot(out[, "V"], xlab = "time", ylab = "v", type="l")
lines(out[, "Y"], xlab = "time", ylab = "y", type="l", col="red")
plot(out[, "Y"], out[, "V"], xlab="y", ylab="v", pch = ".", type="l")
#mtext(outer = TRUE, side = 3, "Raeuber Beute Modell", cex = 1.5)

rf(f,y,v,0.1)
lines(out[, "Y"], out[, "V"], pch = ".", type="l" ,col="red")


# Mechanischer Oszillator mit variabler Krafteinwirkung #####################
Fext<-function(t){4*sin(t*sqrt(k/m))}
c<-0;  m<-1; k<-1; g<-9.80665;  g<-0;


parameters <- c(c = c, m=m , k=k, g=g)
state <- c(Y = -7, V = 0)


MO<-function(t, state, parameters,force) {
  with(as.list(c(state, parameters)),{
    # rate of change
    Fe  <- force(t)
    dY <- V
    dV <- (-c*V-k*Y-m*g-Fe)/m
    
    # return the rate of ch$v=0$ange
    list(c(dY, dV))
  })   # end with(as.list ...
}


times <- seq(0, 80, by = 0.11)
out <- ode(y = state, times = times, func = MO, parms = parameters,force=Fext)
head(out)


#par(oma = c(0, 0, 1, 0))
plot(out[, "Y"], xlab = "time", ylab = "y", type="l")
lines(out[, "V"], xlab = "time", ylab = "v", type="l", col="red")
plot(out[, "V"], xlab = "time", ylab = "v", type="l")
lines(out[, "Y"], xlab = "time", ylab = "y", type="l", col="red")
#mtext(outer = TRUE, side = 3, "Raeuber Beute Modell", cex = 1.5)
plot(out[, "Y"], out[, "V"], xlab="y", ylab="v", pch = ".", type="l")



