class Pila:
    def __init__(self):
        self.cantidad = 0
        self.datos = []
    
    def __str__(self):
        return str(self.datos)
    
    def __len__(self):
        return len(self.datos)
        
    def esta_vacia(self):
        return len(self.datos) == 0
    
    def apilar(self,dato):
        self.datos.append(dato)
        self.cantidad += 1
        
    def desapilar(self):
        if self.esta_vacia(): return None
        self.cantidad -= 1
        return self.datos.pop(-1)
    
    def ver_tope(self):
        if self.esta_vacia(): return None
        return self.datos[-1]