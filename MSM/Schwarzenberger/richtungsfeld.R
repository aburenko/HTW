
# funktion zum plot des richtungsfelds
rf <- function(f,t,x,l=0.2){
  plot(0,0,col="white",xlim=c(min(t),max(t)),ylim=c(min(x),max(x)),xlab="t",ylab="x")
  for (i in 1:length(t)){
    for (j in 1:length(x)){
      w<-l/(2*sqrt(1+f(t[i],x[j])^2))
      lines(c(t[i]-w,t[i]+w),c(x[j]-w*f(t[i],x[j]),x[j]+w*f(t[i],x[j])) ) 
    }
  }
}


# nicht-autonome DGL  #####################
f<-function(t,x){t*x}                                  #funktion f definieren
t<- seq(-5,5, by = 0.5)                                #gitter fuer
x<- seq(-5,5, by = 0.5)                                # das richtunsfeld waehlen
rf(f,t,x,0.4)                                          #richtungsfeld plotten
t1<- seq(-4,4, by = 0.1); C<- -0.3                         #argumente fuer loesung und konstante festlegen
lines(t1,C*exp(0.5*t1^2),col="red")                    #loesung plotten


# exponentielles Wachstum  ################
r<-0.4                                                 #parameter festlegen
f<-function(t,x){r*x}                                  #funktion f defnieren
t<- seq(-10,10, by = 0.5)                              #gitter fuer
x<- seq(-10,10, by = 0.5)                              # das richtungsfeld waehlen
rf(f,t,x,0.4)                                          #richtungsfeld plotten
t1<- seq(-10,10, by = 0.1); C<-0.3                       #argumente fuer loesung und konstante festlegen
lines(t1,C*exp(r*t1),col="red")                        #loesung plotten


# logistisches Wachstum  ##################
r<-0.9; K<-8                                           #parameter festlegen
f<-function(t,x){r*(1-x/K)*x}                          #funktion f definieren
t<- seq(-10,10, by = 0.5)                              #gitter fuer
x<- seq(-1,10, by = 0.5)                               # das richtungsfeld waehlen
rf(f,t,x,0.4)                                          #richtungsfeld plotten
# loesungen plotten:
t1<- seq(-10,10, by = 0.1);                            #argumente fuer loesung 
lines(t1,rep(K,length(t1)),col="red")                  #stationaere Loesung
lines(t1,rep(0,length(t1)),col="red")                  #stationaere Loesung
C<- 1                                                  #Konstante waehlen
lines(t1,K*C*exp(r*t1)/(1+C*exp(r*t1)),col="blue")     #loesung plotten








