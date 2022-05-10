from grafo import Grafo
from cola import Cola
from pila import Pila


# Recibe el grafo, un vertice origen y destino, mas el diccionario de padres calculado por bfs
# Reconstruye el camino y devuelve una lista con un camino minimo posible
def reconstruir_camino(destino,padres):
    camino = []
    camino.append(destino)
    w = destino
    v = padres[w]
    while v is not None:
        camino.append(v)
        w = v
        v = padres[w]
    camino.reverse()
    return camino

# Por cada vertice calcula todos sus caminos minimos, devuelve un diccionario
# con cada vertice como clave y su valor es otro diccionario cuyas claves son los
# los vertices a los que puede llegar y su valor es la distancia.
def caminos_minimos_bfs(grafo, origen):
    cola = Cola()
    visitados = set()
    distancia = {}
    padres = {}
    distancia[origen] = 0
    padres[origen] = None
    visitados.add(origen)
    cola.encolar(origen)

    while not cola.esta_vacia():
        v = cola.desencolar()
        for w in grafo.obtener_adyacentes(v):
            if w not in visitados:
                padres[w] = v
                distancia[w] = distancia[v] + 1
                cola.encolar(w)
                visitados.add(w)
    return distancia,padres

# Calcula el camino minimo desde el origen hasta el destino
# devuelve la cantidad de saltos necesarios y unas lista de los vertices recorridos
# En caso de que no haya ningun camino posible devuelve None
def camino_minimo_origen_destino(grafo,origen,destino):
    orden,padres = caminos_minimos_bfs(grafo,origen)
    if destino not in orden: return None,None
    else:
        distancia = orden[destino]
        camino = reconstruir_camino(destino,padres)
        return camino,distancia

# Calcula el diametro del grafo, es decir, el maximo caminimo minimo
# Devuelve el diametro y un camino asociado
def calcular_diametro(grafo):
    diametro = 0
    camino = []
    camino_diametro = {}
    camino_padres = {}
    for v in grafo.obtener_vertices():
        distancias,padres = caminos_minimos_bfs(grafo, v)
        for d in distancias:
            if distancias[d] > diametro:
                camino_diametro = distancias
                camino_padres = padres
                diametro = distancias[d]
    claves = list(camino_diametro.keys())
    camino = reconstruir_camino(claves[-1],camino_padres)
    return diametro,camino

# Calcula las CFCs de un grafo dirigido
def calcular_cfc(grafo,pagina):
    visitados = set()
    apilados = set()
    orden = dict()
    mb = dict()
    pila = Pila()
    todas_cfc = []
    orden[pagina] = 0
        
    tarjan(pagina,visitados,mb,orden,pila,apilados,grafo,todas_cfc)
    
    return todas_cfc 
    
# Algoritmo de Tarjan para calcular cfc
def tarjan(v,visitados,mb,orden,pila,apilados,grafo,todas_cfc):
    visitados.add(v)
    pila.apilar(v)
    apilados.add(v)
    mb[v] = orden[v]

    for w in grafo.obtener_adyacentes(v):
        if w not in visitados:
            orden[w] = orden[v] + 1
            tarjan(w,visitados,mb,orden,pila,apilados,grafo,todas_cfc)
            
        if w in apilados:
            mb[v] = min(mb[v], mb[w])
    
    if len(pila) > 0 and orden[v] == mb[v]:
        cfc = []
        bandera = True
        while bandera:
            w = pila.desapilar()
            cfc.append(w)
            apilados.remove(w)
            if w == v: bandera = False
        todas_cfc.append(cfc)

    
# Algoritmo de Tarjan para calcular cfc
# def tarjan(v,visitados,mb,orden,pila,apilados,grafo,todas_cfc,indice):
#     orden[v] = indice
#     mb[v] = indice
#     indice = indice + 1
#     visitados.add(v)
#     pila.apilar(v)
#     apilados.add(v)
    

#     for w in grafo.obtener_adyacentes(v):
#         if w not in visitados:
#             tarjan(w,visitados,mb,orden,pila,apilados,grafo,todas_cfc,indice)
#             mb[v] = min(mb[v], mb[w])
#         elif w in apilados:
#             mb[v] = min(mb[v], orden[w])
    
#     if len(pila) > 0 and orden[v] == mb[v]:
#         cfc = []
#         bandera = True
#         while bandera:
#             w = pila.desapilar()
#             cfc.append(w)
#             apilados.remove(w)
#             if w == v: bandera = False
#         todas_cfc.append(cfc)

        
# Recibe un grafo,  si existe una relacion de precedencia entre los vertices
# devuelve una lista ordenada de estos, en caso de que se encuentren ciclos devuelve None
# Este algoritmo utiliza un recorrido similar a BFS
def orden_topologico(grafo):
    grados = {}
    resultados = []
    vertices = grafo.obtener_vertices()
    for v in vertices: grados[v] = 0
    for v in vertices:
        for w in grafo.obtener_adyacentes(v):
            grados[w] += 1
    cola = Cola()
    for v in vertices:
        if grados[v] == 0: cola.encolar(v)
    while not cola.esta_vacia():
        v = cola.desencolar()
        resultados.append(v)
        for w in grafo.obtener_adyacentes(v):
            grados[w] -= 1
            if grados[w] == 0: cola.encolar(w)
    if len(resultados) == len(grafo): return resultados
    return None


# Calcula la cantidad de vertices que se encuentran exactamente a n saltos del origen
def distancia_exacta(grafo,origen,n):
    if not grafo.existe_vertice(origen): return -1
    if n > len(grafo): return 0
    cola = Cola()
    cola.encolar(origen)
    distancia = {}
    distancia[origen] = 0
    lista = []
    while not cola.esta_vacia():
        v = cola.desencolar()
        for w in grafo.obtener_adyacentes(v):
            if w not in distancia:
                distancia[w] = distancia[v] + 1
                cola.encolar(w)
                if distancia[w] == n: lista.append(w)
                if distancia[w] > n: return len(lista)
    return len(lista)

# Funcion recursiva 
def _ciclo_largo_n(grafo,v,origen,n,visitados,camino_actual,solucion):
    visitados.add(v)
    if len(camino_actual) == n:
        if origen in grafo.obtener_adyacentes(v): return camino_actual
        else:
            visitados.remove(v)
            return None
    for w in grafo.obtener_adyacentes(v):
        if w in visitados: continue
        solucion = _ciclo_largo_n(grafo,w,origen,n,visitados,camino_actual+[w],solucion)
        if solucion is not None: return solucion
    visitados.remove(v)
    return None

# Busca en el grafo si existen ciclos de largo n partiendo desde el origen,
# en caso de que se encuentre devuelve una lista de los vertices que lo forman
# devuelve None si no halla ninguno 
def ciclo_largo_n(grafo,origen,n):
    camino_actual = [origen]
    visitados = set()
    solucion = None
    return _ciclo_largo_n(grafo,origen,origen,n,visitados,camino_actual,solucion)


def obtener_n_primeros_adyacentes(grafo,origen,n):
    n_primeros = [origen]
    vertice_actual = origen
    while len(n_primeros) < (n+1):
        adyacentes = grafo.obtener_adyacentes(vertice_actual)
        if len(adyacentes) > 0:
            n_primeros.append(adyacentes[0])
            vertice_actual = adyacentes[0]
        else:
            return n_primeros
    return n_primeros
        
    