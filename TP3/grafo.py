import random

class Grafo():
    
    # Constructor del Grafo, recibe un booleano que especifica si el grafo sera dirigido (True) o no dirgido (False)
    # Se usa la lista de adyacencia sobre diccionario de diccionarios como representacion del Grafo
    def __init__(self,dirigido):
        self.vertices = {}
        self.dirigido = dirigido
    
    def __len__(self):
        return len(self.vertices)
    
    # Devuelve True si el vertice se encuentra en el Grafo, False en caso contrario
    def existe_vertice(self,v):
        return v in self.vertices.keys()
    
    # Devuelve True si el grafo esta vacio, False en caso contrario
    def esta_vacio(self):
        return len(self.obtener_vertices()) == 0
    
    # Agrega un nuevo vertice al grafo, si el vertice ya pertenece al grafo no lo agrega
    def agregar_vertice(self,v):
        if not self.existe_vertice(v):
            self.vertices[v] = {}
    
    # Agrega una arista al grafo, recibe primero su vertice de salida, su vertice de entrada y el peso
    # Si el grafo es no dirgido tambien se agrega la arista en sentido opuesto
    # Si no se especifica ningun peso se toma 1 como el valor predeterminado
    # En caso de que ya exista una arista entre los vertices, es reemplazada por una nueva
    def agregar_arista(self,inicio,fin,peso=1):
        if self.existe_vertice(inicio) and self.existe_vertice(fin):
            self.vertices[inicio][fin] = peso
            if self.dirigido == False:
                self.vertices[fin][inicio] = peso
    
    # Elimina del Grafo, si existe, el vertice recibido por parametro
    def sacar_vertice(self,v):
        if self.existe_vertice(v):
            self.vertices.pop(v)
        for k in self.vertices:
            if v in self.vertices[k].keys():
                self.vertices[k].pop(v)
    
    # Elimina del Grafo la arista recibida por parametro, si existen los vertices y dicha arista
    def sacar_arista(self,inicio,fin):
        if self.existe_vertice(inicio) and self.existe_vertice(fin):
            if fin in self.vertices[inicio].keys():
                self.vertices[inicio].pop(fin)
            if self.dirigido == False:
                if inicio in self.vertices[fin].keys():
                    self.vertices[fin].pop(inicio)
    
    # Devuelve un booleando indicando si existe una conexion entre el vertice inicio y el vertice fin
    def estan_unidos(self,inicio,fin):
        if self.existe_vertice(inicio) and self.existe_vertice(fin):
            if self.dirigido == True:
                return fin in self.vertices[inicio].keys()
            else:
                return (fin in self.vertices[inicio].keys()) and (inicio in self.vertices[fin].keys())
        return False
    
    # Devuelve un vertice aleatorio del Grafo o None si esta vacio
    def vertice_random(self):
        if self.esta_vacio(): return None
        longitud = len(self.vertices)
        numero_aleatorio = random.randrange(longitud)
        claves = list(self.vertices.keys())
        return claves[numero_aleatorio]
    
    # Devuelve una lista con todos los vertices del Grafo
    def obtener_vertices(self):
        return list(self.vertices.keys())
    
    # Devuelve una lista con todos los adyacentes de un vertice o None si el vertice no pertenece al Grafo
    def obtener_adyacentes(self,v):
        if self.existe_vertice(v):
            return list(self.vertices[v].keys())
        return None
