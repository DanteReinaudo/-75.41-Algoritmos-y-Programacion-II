# Tercer Parcial Algoritmos II 07/08/2020
# Dante Reinaudo, padrón 102848
# Ejercicios: 2, 4 y 5

import grafo
import cola 

# Ejercicio 1: Numero 2
# Grafo no dirigido, modela la batalla de dos bandos. Cada vertice es una nacion y la arista (v,w) indica que hay batalla entre esas naciones
# Implementar algoritmo que permita identificar si una nacion traiciono a su bando. Cada nacion mantienen en secreto su bando

# Devuelve true si hubo traicion
def hayTraicion(grafo):
    bando = {}
    HORDA = 1
    ALIANZA = 2
    for v in grafo.vertices:
        bando[v] = None
    nodo_random = grafo.obtener_vertice_random(grafo)
    bando[nodo_random] = HORDA # Eligo un bando al azar para este vertice
    cola = cola_crear()
    cola.encolar(nodo_random)
    while not cola.esta_vacia():
        nodo = cola.desencolar
        for v in grafo.obtener_adyacentes(nodo)
            if (bando[v] == bando[nodo]):
                return True
            if (bando[v] == None):
                if (bando[nodo] == HORDA) bando[v] = ALIANZA
                else: bando[v] == HORDA
                cola.encolar(v)
    return False

# Para resolver este ejercicio, iterprete que para que no haya traiciones, el grafo deberia ser bipartito,
# ya que en dicho caso los vertices de un mismo bando (subconjunto) no comparten aristas, es decir, no habria
# batallas entre paises de un mismo bando
# Complejidad: Por cada vertice recorro todos sus adyacentes, es decir, recorro todos los vertices,
# además, como el grafo es no dirigido, recorro todas las aristas dos veces, por lo tanto el orden es O(V+E).
# siendo V la cantidad total de paises involucrados y E la cantidad de batallas totales entre estos.
# El orden obtenido es logico si tenemos en cuenta que el recorrido que hace el algoritmo es muy similar al de BFS.

# Ejercicio 2 : Numero 4
# Compañia desea renovar cañerias minimizando los costos. Tienen un mapa con todas las cañerias y cuanto dinero
# cuesta arreglarla (existen ciclos). No se especifica que se arreglen todas, sino porlomenos las necesarias para que se conecten todos los puntos de la ciudad

# Para modelizar este problema, yo interpretaria al mapa de la ciudad como un grafo pesado y no dirigido,
# donde los vertices serian los puntos de la ciudad que desean conectarse, y las aristas serian las tuberias,
# cuyo peso vendria dado por su costo de reparacion
# Bajo estas condiciones, el objetivo seria reparar una cierta cantidad de tuberias tal que el costo sea minimo y los vertices sigan conectados.
# Por lo tanto necesitamos que la suma de los pesos de las aristas sea minima de tal manera que el grafo siga siendo conexo,
# esto se puede lograr obteniendo el arbol de tendido minimo del grafo.
# Justamente un arbol de tendido minimo (MST) es un grafo con la mismos vertices que el orignal,
# con la minima cantidad de aristas para que este se mantenga conexo, y en el que la suma de todas las aristas es minima.
# Al obtener el MST del grafo, entonces, obtendria cual cañerias deben arreglarse, cabe aclarar
# que no necesariamente existe un unico arbol de tendido minimo.
# Para obtener el arbol de tendido minimo tenemos dos algoritmos posibles a utilizar: Algortimo de Prim o Algoritmo de Kruskal
# ambos algoritmos tienen un costo de orden O(E*log(V)), siendo V la cantidad total de puntos a conectar y E la cantidad total de tuberias.
# El costo total de realizar esta operacion sería:
# El costo de cargar el mapa en el grafo: Si cargo el grafo en una lista de adyacencia, el costo es de O(V+E), 
# + 
# El costo de obtener el arbol de tendido minimo: O(E*log(V))
#
# Entonces el costo total de realizar esta operacion se puede aproximar por O(E*log(v))
# El seguimiento lo adjunto en una imagen. 

# Ejercicio 3: Numero 5

# a) Falso, existe algunos casos en los cuales al obtener el camino de aumento se utilizan arista que no existen en el grafo original,
# esto no quiere decir que no se pueda usar dicho camino, tal es el caso mostrado al final del video de la catedra en el cual se realiza
# un seguimiento del algoritmo de Ford-Fulkenson, donde el camino de aumento contiene una arista opuesta a la
# que se encontraba en el grafo original, lo cual no indicaba que el camino no pudiera utilizarse, sino que habia cierto flujo que volvia.

# b) Verdadero, a diferencia que con Dijkstra, al usar el algoritmo de Bellman-Ford, podemos calcular el camino minimo
# para grafos no dirigidos con pesos negativos desde un vertice hacia todos los demas, dado que nos permite identificar
# si el grafo contiene ciclos negativos. El algoritmo de Dijsktra no funcion en estos casos, puede quedarse ciclando infinitamente,
# por lo que en caso de que haya un grafo no dirigido con pesos negativos se debe utilizar el algoritmo de Bellman-Ford.
# Si bien presenta esta ventaja sobre Dijsktra, el orden de este algoritmo es O(V*E) el cual es un orden peor al de Dijsktra.

# c) Verdadero, los algoritmos para hallar arboles de tendido minimo no tienen ninguna restriccion en cuanto al peso de las aristas
# el hecho que haya pesos negativos solo afecta en que estos seran mas probables a formar parte del arbol de tendido minimo.
# Tampoco existe ninguna restriccion en cuanto aque el grafo sea no dirigido. 
