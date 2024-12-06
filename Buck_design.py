import numpy
from matplotlib.pyplot import *

# Parameters
L= 33.0e-6      # Inductance 
C= 220.0e-6     # capacitor 
Rc = 360.0e-3   # ESR capacitor
R= 8          # Load resistor
Rsw = 0.1       # average resistance RON of diode ans P-MOS
Vin =  30       # input voltage 
Vout = 12        # output voltage


# LC filter transfer function
def HLC(f):
    w=2*numpy.pi*f
    return (Vin*(1.0+ Rc*C*1j*w))/(1+1j*L*w*(1j*C*w+1.0/R))


f = numpy.logspace(2,6,1000)
GdB = 20*numpy.log10(numpy.absolute(HLC(f)))
phase_coef = 180/numpy.pi
phi = numpy.angle(HLC(f))*phase_coef

figure(1)
subplot(211)
plot(f,GdB)
xlabel("f (Hz)")
ylabel("GdB")
xscale('log')
grid()
subplot(212)
plot(f,phi)
xlabel("f (Hz)")
ylabel("phase")
ylim(-180)
xscale('log')
grid()

#dB20k = 20*numpy.log10(numpy.absolute(HLC(20e3)))
#print(GdB20k)
#show()


# select the feedback parameters to have the disered pahse margin

# step 1 : determine the LC filter break frequency
fesr = 1/ (2*numpy.pi*Rc*C)

#step 2 : place the first zero fz1
fz1 = fesr/5
R8 = float(input("enter a value for R8: "))
C8 =  1/ (2*numpy.pi*R8*fz1)


#step 3 : choose the crossover frequency
fcr = float(input("Crossover frequency: "))
GdB_fcr =  63.88 - 20*numpy.log10(fcr/2e3)

#step 4 : place the scond pole fp2


fp2 = 2*fcr
C7  =  C8 / (2*numpy.pi*R8*C8*fp2 -1)

#step 5 : Calculate the gain elements

#Kfb    : output voltqge setting divider 
#Kea    : error amplifier feedback 
#Kpwm   : modulator gain 
#Xlc    : filter transfert function

#Tv = Kfb*Kea*Kpwm*Xlc  : total volatge gain feedback


# LC filter transfer function with RON resistance 
def Zout(f):
    w=2*numpy.pi*f
    #return (1 + Rc*C*1j*w)/(1 + (C +Rc*C)*1j*w) # (1 + Rc*C*R*1j*w)/(1 + (C +Rc*C/R)*1j*w)
    return (1 + Rc*C*R*1j*w)/(1 + (C +Rc*C/R)*1j*w) 

def Xlc(f):
    w=2*numpy.pi*f
    return Zout(f)/( Zout(f) + 1j*L*w + Rsw)

R10 = 100e3
R6 = (0.696*R10)/(Vout - 0.696)

Kfb = 20*numpy.log10(R10/R6)
Kpwm = 20       # in decibels



print("C8: ",C8)
print("fp2: ",fp2)
print("C7: ", C7)
print("GdB_fcr", GdB_fcr)

f = numpy.logspace(2,6,1000)
GdB = 20*numpy.log10(numpy.absolute(Xlc(f)))
coef = 180/numpy.pi
phi = numpy.angle(Xlc(f))*coef

Xlc_fcr = 20*numpy.log10(numpy.absolute(Xlc(fcr)))

Amp_Feed_Gain  = numpy.float_power(10,(20 + Xlc_fcr )/20)       # in decibels

print(Amp_Feed_Gain)
print(Xlc_fcr)

Coef = (GdB_fcr - Amp_Feed_Gain) / (Amp_Feed_Gain*(1+ GdB_fcr)*R10)

print(coef)

# Check if it fits with R8 C8 and C7 values 
def zfs(f):
    w = 2*numpy.pi*f
    return (1+ R8*C8*1j*w) / (1j*w*( C7 + C8 + C7*C8*R8*1j*w)) 

Amp_Feed_Gain_real = numpy.absolute(1/R8 + 1/zfs(fcr))

print(" test pour savoir si c'est égale à zero", Amp_Feed_Gain_real)


print("Valeurs finales: ")
print("fp2: ",fp2)
print("fz1: ",fz1)
print("C8: ",C8)
print("R8: ",R8)
print("C7: ",C7)
print("R10: ",R10)
print("R6: ",R6)
print("crosssover frequency: ", fcr)

