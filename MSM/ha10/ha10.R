library(deSolve)

parameters <- c(a =  0.21, b = 0.001)
state <- c(S = 499, I = 1)

RB<-function(t, state, parameters) {
  with(as.list(c(state, parameters)),{
    # rate of change
    dS <- -b*S*I
    dI <- b*S*I*-a*I
    
    # return the rate of change
    list(c(dS, dI))
  })   # end with(as.list ...
# Zeitspanne fuer Loesung vor
}

geben
times <- seq(0, 60, by = 1)

# DGL Loesen
out <- ode(y = state, times = times, func = RB, parms = parameters)
out