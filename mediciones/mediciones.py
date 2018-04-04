# -*- coding: utf-8 -*-

import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from random import randrange


##------------Configuracion------------------------------------------------------##
path_dir_de_trabajo = ''
nombre_archivo_entrada = path_dir_de_trabajo + 'entradas/entrada'
path_entradas = path_dir_de_trabajo + 'entradas/'
nombre_page_rank = './tp1'
probabilidad_de_salto = '0.2'
nombre_archivo_mediciones = path_dir_de_trabajo + 'mediciones.csv'
nombre_archivo_grafico_medicion = path_dir_de_trabajo + 'mediciones.png'
##------------Configuracion------------------------------------------------------##



##------------Generamos archivos de entrada--------------------------------------##



# devuelve si hay link entre dos nodos con la probabilidad de entrada
def hay_link(probabilidad_de_link):
    p = np.zeros_like([0,1], dtype=float)
    p[0] = 1 - probabilidad_de_link
    p[1] = probabilidad_de_link
    return np.random.choice([0,1], 1, p=p)[0]

# genera un grafo aleatorio de la cantidad de nodos indicada como parametro
# y la probabilidad de agregar links entre dos páginas dadas = p
def generar_grafo_aleatorio(cantidad_nodos, probabilidad_de_link):
    grafo = np.zeros((cantidad_nodos, cantidad_nodos))  # Matriz de ceros\n"
    
    for i in range(0, cantidad_nodos-1):
        for j in range(0, cantidad_nodos-1):
            if (i==j):
                grafo[i][j] = 0
            else:
                grafo[i][j] = hay_link(probabilidad_de_link)
    return grafo

# genera los archivos de entrada con matrices de 2 páginas hasta 'cantidad_maxima_de_paginas', 
# la probabilidad que haya un link entre dos nodos es 'probabilidad_de_link'
# 'nombre_archivo_entrada' es el path y el prefijo con el que va a generar los nombres de los 
# archivos de entrada, a esos prefijos les va a concatenar la cantidad de páginas que tiene
# el grafo de páginas.
def generar_entradas(nombre_archivo_entrada, cantidad_maxima_de_paginas, probabilidad_de_link):
    grafo = generar_grafo_aleatorio(cantidad_maxima_de_paginas, probabilidad_de_link)
    
    for i in range(2, cantidad_maxima_de_paginas):
        cantidad_maxima_de_paginas, probabilidad_de_link
        subgrafo = grafo[0:i, 0:i]
        f =open(nombre_archivo_entrada + str(i).zfill(5), 'w')
        salida = generar_salida_matriz(subgrafo);
        f.write(salida.encode('utf8'))
        f.close()

# transforma la matriz al formato de entrada pedido por la catedra
def generar_salida_matriz(matriz):
    ret = ''
    cant_paginas = matriz.shape[0]
    total_links = 0
    for i in range(0, cant_paginas):
        for j in range(0, cant_paginas):
            if (matriz[i][j]!=0):
                total_links += 1;
                ret = ret + str(i) + ' ' + str(j) + '\n'
    ret = str(cant_paginas) + '\n' + str(total_links) + '\n' + ret
    return ret

#escribe la salida cumpliendo el formato pedido por la catedra
def escribir_salidas(nombre_archivo_entrada, nombre_archivo_salida):
    f =open(nombre_archivo_entrada + str(i) + '.out', 'r')
    


generar_entradas(nombre_archivo_entrada, 20, 0.3)

##------------Generamos archivos de entrada--------------------------------------##

##---------Tomamos mediciones utilizando la entrada generada previamente y las guardamos---------##
    
o=os.popen('ls ' + path_entradas).read()
nombres = o.splitlines()
print(path_dir_de_trabajo + nombre_page_rank + ' ' +  path_entradas + 'entrada0001' + ' ' + probabilidad_de_salto)
f =open(nombre_archivo_mediciones, 'w')
f.write('cantidad de páginas,mediciones \n')
a = [len(nombres)]
i = 1
for nombre in nombres:
    i = i + 1
    f.write(str(i) + ',' + os.popen(path_dir_de_trabajo + nombre_page_rank + ' ' +  path_entradas + nombre + ' ' + probabilidad_de_salto).read() + '\n')
f.close()

df = pd.read_csv(nombre_archivo_mediciones)

df.head()
    
    
##---------Tomamos mediciones utilizando la entrada generada previamente---------##

##---------Generamos el grafico a partir de las mediciones-----------------------##
grafico_mediciones = df.plot(kind='line')
plt.show()
fig = grafico_mediciones.get_figure()
fig.savefig(nombre_archivo_grafico_medicion)
##---------Generamos el grafico a partir de las mediciones-----------------------##
