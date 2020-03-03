# ASOC2 - Módulo de memoria

Coordinador del grupo: Suso

Grupo: Aquellas Personas Cuyo Conocimiento Es Limitado

Prefacio:

Contamos con un sistema pensado para arquitecturas de 64 bits
acorde al manual de ensamblador de intel. 
64-ia-32 arch software developer's manual.
	
	Recordad que podemos direccionar 2^64 bits de memoria.

Preguntas:

1. Vamos a emplear el espacio de direcciones completo?

    1.1. Los procesadores actuales permiten direccionar toda esa memoria?
    	No soporta Intel 64: 2^36-1 (64GB)
	Intel 64 (Implementación empleada): 2^48-1
	Intel 64 (Implementación ideal): 2^64-1
    
    1.2. En caso negativo a la pregunta 1: Cuantos bits vamos a usar?
	Si usamos 48 bits, podríamos permitir que cualquier dirección fuera del rango fuese transformada %2^48 para mirrorear memoria 65536 veces. De estos 48 bits 9\*n se dedicarán al árbol de páginas (siendo n el número de capas del árbol) y el resto al offset dentro de cada página.
		
2. Por qué es importante la memoria virtual? Como la vamos a implementar?
	Para poder mapear direcciones físicas de memoria (tanto de la ram como del disco) a direcciones virtuales, implementando así una interfaz estándar, con un espacio de memoria continuo y un nivel de abstracción superior (que a su vez permite asignar la memoria de una forma independiente entre procesos). Dividiendo el espacio de direccionamiento en páginas (x64 soporta páginas de 4kB, 2MB o 1GB dependiendo de cómo se dividan los bits de la dirección virtual).
	
3. Si se usa paginación, usaréis la MMU o lo haréis a mano?
	Usar la MMU nos permitiría transformar direcciones físicas ↔ virtuales de forma más cómoda y eficiente.
	
--------

4. Usaréis un fichero de swap?
	Un fichero de swap permite intercambiar datos entre memoria real (RAM) y virtual (mapeada al almacenamiento). Puesto que la RAM es más rápida, es recomendable mantener los datos usados actualmente en ella, swappeando los innecesarios al disco.
	
5. De ser así, definid un algoritmo de swapping apropiado. Puede ser vuestro o preexistente.
