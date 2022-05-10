class Cola():
    def __init__(self):
        self.cantidad = 0
        self.datos = []
    
    def __str__(self):
        return str(self.datos)
        
    def __len__(self):
        return len(self.datos)
    
    def esta_vacia(self):
        return len(self.datos) == 0
    
    def encolar(self,dato):
        self.datos.append(dato)
        self.cantidad += 1
        
    def desencolar(self):
        if self.esta_vacia(): return None
        self.cantidad -= 1
        return self.datos.pop(0)
    
    def ver_primero(self):
        if self.esta_vacia(): return None
        return self.datos[0]