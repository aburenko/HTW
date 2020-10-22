library(optimization)
library(iemisc)

# aufgabe 1
func <- function(p){
  (8.2-p[1])^2+(7.9-p[1])^2+(5.3-p[2])^2+((76-asind(sqrt(4*(p[1])^2-(p[2])^2)/(2*p[1])))^2)/16+(7.4-0.5*sqrt(4*(p[1])^2-(p[2])^2))^2
}

erg <- optim_nm(fun=func, k = 2);
erg$par


# aufgabe 2
x0 <- 17

# messung 1
m_x1 <- 11.2 
m_y1 <- 4.1
m_z1 <- 2.5
t <- 5


func <- function(k){
     (m_x1-x0*exp(-k[1]*t))^2
   + (m_y1-(x0*k[1])*((exp(-k[1]*t)-exp(-k[2]*t))/(k[2]-k[1])))^2
   + (m_z1-x0*(1+( (k[1]*exp(-k[2]*t)-k[2]*exp(-k[1]*t))/(k[2]-k[1]))))^2 
}

erg <- optim_nm(fun=func, start=(1,2));
erg$par

# messung 2
m_x1 = 4.5 
m_y1 = 3.1
m_z1 = 8.5
t = 12

erg <- optim_nm(fun=func, start=(1,2));
erg$par
s

k1 = erg$par[0]
k2 = erg$par[1]

k1 = 0.088275
k2 = 0.184189
xfunc <- function(t) {x0*exp(-k1*t)}
yfunc <- function(t) {(x0*k1)*((exp(-k1*t)-exp(-k2*t))/(k2-k1))}
zfunc <- function(t) {x0*(1+( (k1*exp(-k2*t)-k2*exp(-k1*t))/(k2-k1)))}
t<-seq(0,100)
matplot(t,cbind(xfunc(t),yfunc(t),zfunc(t)),type="l",col=c("blue","red","black"))
points (5, 11.2)
points (5, 4.1)
points (5, 2.5)
points (12, 3.5)
points (12, 6.1)
points (12, 8.5)

