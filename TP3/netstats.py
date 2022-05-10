#!/usr/bin/python3
from grafo import Grafo
import biblioteca as bg
import os.path as path
import csv
import sys

def es_entero(n):
    try:
        int(n)
        return True
    except:
        return False


def cargar_grafo_archivo(archivo):
    grafo = Grafo(dirigido = True)
    lineas = []
    
    with open(archivo) as file:
        file_tsv = csv.reader(file,delimiter="\t")
        #file_tsv = csv.reader(file,delimiter=",")
        for linea in file_tsv:
            if len(linea) != 0:    
                grafo.agregar_vertice(linea[0])
                lineas.append(linea)
        
    for linea in lineas:
        for i in range(1,len(linea)):
            if len(linea) > 1: grafo.agregar_arista(linea[0],linea[i])
    
    return grafo 


def listar_operaciones(operaciones):
    #print("Las operaciones posibles son las siguientes:")
    for operacion in operaciones[1:]:
        print(operacion)
        


# Recibe un grafo y una lista de vertices, si existe una relacion de precedencia devuelve una lista ordenada de estos
# devuelve None en caso de que se encuentren ciclos o no existan dichos vertices.
def orden_topologico_subgrafo(grafo,lista):
    subgrafo = Grafo(dirigido = True)
    for vertice in lista:
        if not grafo.existe_vertice(vertice): return None
        subgrafo.agregar_vertice(vertice)
    for vertice in lista:
        for adyacente in grafo.obtener_adyacentes(vertice):
            subgrafo.agregar_arista(adyacente,vertice)
    
    return bg.orden_topologico(subgrafo)


def lectura_2am(grafo,lista):
    existen = True
    for vertice in lista:
        if not grafo.existe_vertice(vertice): existen = False
    if not existen: print("Uno de los vertices recibidos no pertenece al grafo")
    else:
        orden = orden_topologico_subgrafo(grafo,lista)
        if orden == None: print("No existe forma de leer las paginas en orden")
        else:
            salida = ", ".join(orden)
            print(salida)
 
 
def todos_en_rango(grafo,origen,str_n):
    if es_entero(str_n):
        n = int(str_n)
        cantidad = bg.distancia_exacta(grafo,origen,n)
        if cantidad == -1 : print("El vertice recibido no pertenece al grafo")
        else: print(cantidad)
    else:
        print("El parametro recibido no es un numero valido")


def ciclo_n_articulos(grafo,origen,str_n):
    if es_entero(str_n):
        n = int(str_n)
        if origen not in grafo.obtener_vertices(): print("El vertice recibido no pertenece al grafo")
        else:
            camino_ciclo = bg.ciclo_largo_n(grafo,origen,n)
            if camino_ciclo == None: print("No se encontro recorrido")
            else:
                camino_ciclo.append(camino_ciclo[0])
                salida = " -> ".join(camino_ciclo)
                print(salida)
    else:
        print("El parametro recibido no es un numero valido")


def camino_mas_corto(grafo,origen,destino):
    if not grafo.existe_vertice(origen) or not grafo.existe_vertice(destino): print("Uno de los vertices recibidos no pertenece al grafo")
    else:
        camino,costo = bg.camino_minimo_origen_destino(grafo,origen,destino)
        if camino == None and costo == None: print("No se encontro recorrido")
        else:
            salida = " -> ".join(camino)
            print(salida)
            print("Costo:",costo)

def buscar_y_mostrar_cfc(cfcs, vertice):
    for cfc in cfcs:
        if vertice in cfc:
            salida = ", ".join(cfc)
            print(salida)

def conectados(grafo,vertice):
    if not grafo.existe_vertice(vertice): print("El vertice recibido no pertenece al grafo")
    else:
        cfcs = bg.calcular_cfc(grafo,vertice)
        buscar_y_mostrar_cfc(cfcs,vertice)
        return cfcs
     
def navegacion_primer_link(grafo,origen):
    if not grafo.existe_vertice(origen): print("El vertice recibido no pertenece al grafo")
    else:
        n_primeros_links = bg.obtener_n_primeros_adyacentes(grafo,origen,20)
        salida = " -> ".join(n_primeros_links)
        print(salida)

def procesar_comandos(grafo):
    operaciones = ["listar_operaciones","conectados","lectura","navegacion","diametro","camino","ciclo"]
    diametro = -1
    cfc_calculada = -1
    
    for linea in sys.stdin:
        comando = linea.rstrip("\n")
        comandos = comando.split(" ",1)
        
        if comandos[0] not in operaciones: print("El comando ingresado no es válido!")
        
        elif comando == "listar_operaciones":
            listar_operaciones(operaciones)
        
        elif comando == "diametro":
            if diametro == - 1:
                diametro,camino = bg.calcular_diametro(grafo)
                camino_unido = " -> ".join(camino)
            print(camino_unido)
            print("Costo:", diametro)
            
        elif len(comandos) == 2:
            parametros = comandos[1].split(sep = ",")
            
            if comandos[0] == "lectura" :
                lectura_2am(grafo,parametros)
            
            elif len(parametros) == 1 and comandos[0] == "conectados" :
                if cfc_calculada == -1:
                    cfc_calculada = conectados(grafo,parametros[0])
                
                buscar_y_mostrar_cfc(cfc_calculada, parametros[0])
            
            elif len(parametros) == 1 and comandos[0] == "navegacion":
                navegacion_primer_link(grafo,parametros[0])
                
            elif len(parametros) == 2 and comandos[0] in operaciones[5:]:
                if comandos[0] == "camino":
                    camino_mas_corto(grafo,parametros[0],parametros[1])
                
                elif comandos[0] == "ciclo":
                    ciclo_n_articulos(grafo,parametros[0],parametros[1])
                
                elif comandos[0] == "rango":
                    todos_en_rango(grafo,parametros[0],parametros[1])
                    
            else:
                print("Error: Cantidad de parametros incorrecta!")
        else:
            print("Error: Cantidad de parametros incorrecta!")
        

def main():
    #print("~~~~~~~~~ Bienvenidx a nuestra red ~~~~~~~~~")
    if len(sys.argv) == 1 : print("No se recibio ningun archivo .tsv")
    elif not path.isfile(sys.argv[1]): print("No se ha encontrado el archivo:",sys.argv[1])
    else:
        grafo = cargar_grafo_archivo(sys.argv[1])
        if(len(grafo) > 1000): sys.setrecursionlimit(len(grafo))
        #print("La informacion ha sido cargada correctamente!")
        procesar_comandos(grafo)
    #print("Gracias por usar nuestro programa, hasta la próxima!")

main()