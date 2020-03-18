# ASOC2 Procesos

Equipo: mASOCas

Coordinador: Jose Alvarez

Prefacio:
	Disponemos de una máquina acorde a la especificación del 
	intel assembly manual que ya conocéis.

	Nuestro objetivo es diseñar las estructuras que empleará
	nuestro kernel para manejar sus procesos, los algoritmos
	y el contexto de ejecución. Es importante
	tener en cuenta que el propio kernel es un proceso
	que se carga sobre cada proceso de usuario.

Preguntas:
	Que compondrá un proceso en vuestro sistema?

	Implementaréis COW (Copy on write) ? Si es así ,como? 

    Si, se implementará Copy on write. La implementación aun está por decidir.

	Usaréis concurrencia? Si es así, cooperativa o preemtive?
	
	Si, usaremos concurrencia del tipo preemptive, ya que presenta varias ventajas frente al preemptive.

	Que algoritmo seguiréis para decidir que proceso se ejecutará
	en cada momento?
	
	Lo más probable es que se use un algoritmo que implemente colas por prioridad, aunque se contempla una mezcla de varios algoritmos.

	Que condiciones pueden derivar en cambio de proceso?
	
	Que se le agote el tiempo de reloj o una interrupción.

	Implementaréis interrupciones? Como trataréis los errores del sistema?
	
	Si, implementaremos interrupciones.
	
-------
	
	El cambio de contexto lo haréis por software o por hardware via TSS? (pros y cons de cada una)
	NOTA: Esta pregunta parece muy molona, es una trampa. No le dediqueis mucho tiempo, es solo para modo Legacy, 
	que en un principio no vamos a usar!