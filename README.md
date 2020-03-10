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

	Usaréis concurrencia? Si es así, cooperativa o preemtive?

	Que algoritmo seguiréis para decidir que proceso se ejecutará
	en cada momento?

	Que condiciones pueden derivar en cambio de proceso?

	Implementaréis interrupciones? Como trataréis los errores del sistema?
	
-------
	
	El cambio de contexto lo haréis por software o por hardware via TSS? (pros y cons de cada una)
	NOTA: Esta pregunta parece muy molona, es una trampa. No le dediqueis mucho tiempo, es solo para modo Legacy, 
	que en un principio no vamos a usar!
