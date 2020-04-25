
Repository: TSP-EAX-PSX-V2
Project:    Parallel Genetic Algorithm for TSP
Author:     Jesús Carlos Cárdenas Piñuelas
OS:         Ubuntu 18.04
Language:   C (std)
Compile:    gcc main.c -o main -lpthread -lm
Run:        time ./main
-------------------------------------------------- -------------------
Edge Assembly Crossover: EAX
EAX is a crossover operator for genetic algorithms that solve the Travelling Salesman Problem (TSP).
EAX author:
Nagata Y. (2006)
New EAX Crossover for Large TSP Instances.
In: Runarsson T.P., Beyer HG., Burke E., Merelo-Guervós J.J., Whitley L.D., Yao X. (eds) Parallel Problem Solving from Nature - PPSN IX. Lecture Notes in Computer Science, vol 4193. Springer, Berlin, Heidelberg
-------------------------------------------------- -------------------
This source code is based on the work done by TEAPOT british-sense, whose original code can be accessed from its repository:
	https://github.com/british-sense/Edge-Assembly-Crossover
The original source code is developed with C ++ with the object-oriented programming paradigm, while the present implementation was developed with standard C and was parallelized with POSIX threads.
To plot results, the "Plot ... ()" functions are used, which are used by the GNUPLOT software:
	http://www.gnuplot.info
The test problems that were used for the development of this software are found in:
	http://www.math.uwaterloo.ca/tsp/vlsi/index.html
This code works only with instances of the symmetric TSP and some of the parameters that can be edited are the following:
INPUT_FILE: Data file (coordinates of the points that make up the problem, start on line 7).
DIMENSION:  Total cities that comprise the problem.
BEST_OLIB:  Best reported solution to the problem.
GENERATION: Number of generations for the genetic algorithm.
POPULATION: Number of individuals for the genetic algorithm.
CHILDREN:   Number of children for the genetic algorithm.
DEPTH:      Depth of search for close neighbors.
ERROR:      Desired Error Percentage
TRIAL:      Attempts to execute.
* To edit the mentioned parameters you must edit the file "param.c"

------------------------------ ESPAÑOL ------------------------------

Repositorio: TSP-EAX-PSX-V2
Proyecto:    Algoritmo genetico para el TSP
Autor:       Jesús Carlos Cárdenas Piñuelas
SO:          Ubuntu 18.04
Lenguaje:    C (std)
Compilar:    gcc main.c -o main -lpthread -lm
Ejecutar:    time ./main
---------------------------------------------------------------------
Cruce de ensamblaje de bordes: EAX
EAX es un operador de cruce para algoritmos geneticos que resuelven el problema del vendedor ambulante (TSP).
Autor del EAX:
	Nagata Y. (2006) 
	New EAX Crossover for Large TSP Instances. 
	In: Runarsson T.P., Beyer HG., Burke E., Merelo-Guervós J.J., Whitley L.D., Yao X. (eds) Parallel Problem Solving from Nature - PPSN IX. Lecture Notes in Computer Science, vol 4193. Springer, Berlin, Heidelberg
---------------------------------------------------------------------
Este código fuente esta basado en el trabajo realizado por TEAPOT british-sense, cuyo código original se puede acceder desde su repositorio:
	https://github.com/british-sense/Edge-Assembly-Crossover
El código fuente original esta desarrollado con C++ con el paradigma de programación orientada a objetos, mientras que la presente implementación se desarrollo con C estándar y se paralelizo con hilos POSIX.
Para gráficar resultados se utilizan las funciones "Plot...()" las cuales utilizan el software GNUPLOT:
	http://www.gnuplot.info
Los problemas de prueba que se utilizaron para el desarrollo de este software se encuentran en:
	http://www.math.uwaterloo.ca/tsp/vlsi/index.html
Este código funciona únicamente con instancias del TSP simétrico y algunos de los parámetros que se pueden editar son los siguientes:
INPUT_FILE: Archivo de datos (coordenadas de los puntos que conforman el problema, iniciar en la línea 7).
DIMENSION:  Total de ciudades que comprende el problema.
BEST_OLIB:  Mejor solución reportada del problema.
GENERATION: Cantidad de generaciones para el algoritmo genético.
POPULATION: Cantidad de individuos para el algoritmo genético.
CHILDREN:   Cantidad de hijos para el algoritmo genético.
DEPTH:      Profundiad de búsqueda de vecinos cercanos.
ERROR:      Porcentaje de error deseado
TRIAL:      Intentos de ejecución.
*  Para editar los parámetros mencionados se debe editar el archivo "param.c"
