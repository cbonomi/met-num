# -*- coding: utf-8 -*-

import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from random import randrange


##------------Configuracion------------------------------------------------------##
path_dir_de_trabajo = '/home/christian/'
path_entradas = path_dir_de_trabajo + 'entradas/'
path_salidas = path_dir_de_trabajo + 'salidas/'
nombre_page_rank = 'tp1'
probabilidad_de_salto = '0.2'
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

#A = generar_grafo_aleatorio(20, 0.3)
#print(A)

#print(type(A))
#print(A.shape[0])

# genera los archivos de entrada con matrices de 2 páginas hasta 'cantidad_maxima_de_paginas', 
# la probabilidad que haya un link entre dos nodos es 'probabilidad_de_link'
# 'nombre_archivo_entrada' es el path y el prefijo con el que va a generar los nombres de los 
# archivos de entrada, a esos prefijos les va a concatenar la cantidad de páginas que tiene
# el grafo de páginas. Agregue el parametro paso que indica la cantidad de nodos en que crece el grafo.
def generar_entradas(nombre_archivo_entrada, grafo, paso):       
    cantidad_maxima_de_paginas = grafo.shape[0]
    for i in range(paso, cantidad_maxima_de_paginas, paso):
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
    




##------------Generamos archivos de entrada--------------------------------------##

##---------Tomamos mediciones utilizando la entrada generada previamente y las guardamos---------##



def tomarMediciones(nombre_archivo_entrada, grafo, paso, nombre_archivo_mediciones):    
    o=os.popen('rm ' + path_entradas + '*.out')
    generar_entradas(nombre_archivo_entrada, grafo, paso)    
    o=os.popen('ls ' + path_entradas).read()
    
    nombres = o.splitlines()

    f =open(nombre_archivo_mediciones, 'w')
    f.write('cantidad de nodos, ciclos de reloj \n')
    a = [len(nombres)]
    i = 1
    for nombre in nombres:
        i = i + 1
        f.write(str(i*paso) + ',' + os.popen(path_dir_de_trabajo + nombre_page_rank + ' ' +  path_entradas + nombre + ' ' + probabilidad_de_salto).read() + '\n')
    f.close()

    df = pd.read_csv(nombre_archivo_mediciones)

    df.head()
    
    
##---------Tomamos mediciones utilizando la entrada generada previamente---------##

##---------Generamos el grafico a partir de las mediciones-----------------------##
def graficar(nombre_archivo_mediciones, nombre_grafico_medicion, titulo, tipo_de_grafico):
    df = pd.read_csv(nombre_archivo_mediciones)
    grafico_mediciones = df.plot(kind=tipo_de_grafico)
    fig = grafico_mediciones.get_figure()
    plt.title(titulo)
    plt.xlabel(df.columns[0])
    plt.ylabel(df.columns[1])
    plt.grid(True)

    plt.show()
    fig.savefig(nombre_archivo_grafico_medicion)
##---------Generamos el grafico a partir de las mediciones-----------------------##

##--------------Procedimiento general para cualquier grafo-----------------------##
# 1.- Consta de tres partes creamos un grafo de cualquier forma.
# 2.- Tomamos las mediciones de este grafo y las guardamos en un archivo.
# 3.- Creamos un grafico con estas mediciones.

# 1.- generamos un grafo de con cantidad maxima de paginas = 20 y probabilidad de link entre los nodos i, j 0.3
grafo = generar_grafo_aleatorio(100, 0.3)
# 2.- tomamos mediciones con la entrada pasada en el primer parametro, el grafo en el segundo y con un paso de 10
#     y guardamos estas mediciones en el archivo de salida indicado en el ultimo parametro.
tomarMediciones(path_dir_de_trabajo + 'entradas/entrada', grafo, 10, path_dir_de_trabajo + 'mediciones2.csv')
# 3.- graficamos las mediciones del archivo pasado como parametro, y la guardamos en el archivo pasado como segundo
#     parametro, el tipo de grafico que queremos se lo indicamos con el tercer parameto.
graficar(path_dir_de_trabajo + 'mediciones2.csv', path_dir_de_trabajo + 'mediciones.png', 'Medicion en ciclos de reloj', 'line')



