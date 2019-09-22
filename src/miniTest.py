#GRACIAS PYTHON FOR BEGINNERS
import sys #para leer los argumentos
import random as rd #para generar datos random

maxBeneficio = 100


def crearMiniTest():
	capacidad = sys.argv[2]		
	# Elijo capacidad*2 para tener un poco de todo
	maxPeso = int(capacidad)*2 	
	elems = sys.argv[1]
	
	mochila = '{} {}'.format(elems, capacidad)
	print mochila
	for i in range(int(elems)):
		peso = str(rd.randint(0, maxPeso)) 
		beneficio = str(rd.randint(0, maxBeneficio))
		pedido = '{} {}'.format(peso, beneficio)
		print pedido
			
archivo=sys.argv[0]
ayuda='##Para generar test correr: python '+ archivo +' [cantidadElems] [capacidad]'

#Imprimo help
if len(sys.argv) < 2:
	print ayuda
	 
if len(sys.argv) == 3:
	#print sys.argv[0]
	crearMiniTest()
	
	
