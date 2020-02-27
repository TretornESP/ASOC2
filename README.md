# ASOC2 Modulo de ficheros

Coordinador del grupo: Daniel Sergio Vega
Equipo de desarrollo de ficheros : Round Robins

Prefacio:
	Tenemos un sistema acorde a las especificaciones
	del Intel assembly manual, el sistema soportará 
	multiples discos y permitirá su administración

Preguntas:
    1. Vais a hacer un nuevo sistema de ficheros o usar uno existente?
       
       En un principio existentes.
       Vamos a implementar uno (o más en un caso ideal) de los siguientes sistemas de ficheros:
          UFS
          Ext2 (Estudiar el caso de ext3 o ext4 y ver si son viables para este proyecto)
          FAT
          (Estamos estudiando la posibilidad de implementar alguna otra familia de FS)
	
	2. Que sistemas de ficheros vais a soportar?
    
       Vamos a soportar los que podamos implementar, es decir, la respuesta es la misma a la primera
       pregunta.
       (El concepto de soportar implica la creación y correcta modificación del formato de esos sistemas)

	3. Que tipos de dispositivos de almacenamiento vais a soportar?
    
       A nuestros ojos esta pregunta debe ser respondida en conjunto con el equipo de device drivers.
       Al fin de al cabo suponemos que nuestra implementación es abstracta al espacio físico de almacenamiento (en principio),
       por tanto una interfaz de programación debe ser acordada entre ficheros/device-drivers.

	4. Que métodos de acceso a disco vais a soportar? (bloque, bit a bit, 
	fichero, etc)
    
       El caso mas sensato (en principio) es el uso de bloques cuyo tamaño está aun por determinar.
