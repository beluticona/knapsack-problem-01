# Ejemplo para correr el programa de C++ desde Python (para graficar luego)

from subprocess import run
entrada_ejemplo = ["5", "25", "10", "5", "15", "4", "5", "13", "10", "8", "5", "8"]
# entrada_ejemplo podría ser generada dinámicamente
run("./main bt", input=" ".join(entrada_ejemplo).encode("utf-8"), shell=True)

'''Idea para la experimentación:
El TP pide que la resolución de la mochila lea la entrada estándar con un formato predefinido y
escriba el máximo beneficio en la salida estándar. Teniendo en cuenta esto para la experimentación
creo conviene hacer lo siguiente:
1) Un archivo con las distintas implementaciones para resolver el problema de la mochila que actúe
como biblioteca de código.
2) Un main como el que ya tenemos que cumpla los requerimientos de entrada y salida estándar.
3) Otro main para medir tiempos que consuma las funciones del punto 1) pero les provea datos
autogenerados (no de la entrada estándar) para distintos casos (peor caso de cada algoritmo, por
ejemplo), haga mediciones de tiempo en base a 100 corridas o algo así y escriba las mediciones en la
salida estándar.
4) Un programa de Python que de una forma similar al código de este ejemplo ejecute el medidor de
tiempos leyendo la salida estándar y haciendo grafiquitos.
'''
