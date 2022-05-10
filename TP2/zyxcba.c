
#include "mensajes.h"
#include "clinica.h"
#include "funciones_tp2.h"

/* ******************************************************************
 *                       PROGRAMA PRINCIPAL
 * *****************************************************************/

// Programa principal: se interpreta que el primer nombre recibido
// corresponde al archivo de doctores y el segundo al de pacientes
int main(int argc, char** argv) {
	if (argc != 3){ // Recibe el nombre del promgrama y el nombre de 2 archivos
		printf(ENOENT_CANT_PARAMS);
		return 1;
	}
	clinica_t* clinica = crear_clinica(argv);
	if(!clinica){
		return 1;
	}
	procesar_entrada(clinica);
	destruir_clinica(clinica);
	return 0;
}
