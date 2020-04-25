
// compile GCC:  gcc main.c -O3 -o main -lm -lpthread
// run:          time ./main

#include "outs.c"

int main(int argc, char **argv){
	srand(time(NULL));
	InputFile();
	CalculateCost();
	// PrintData();
	// PrintCost(20);
	// PrintNNlist(20);

	int max_x = GetMaxX();
	int max_y = GetMaxY();

	pthread_t threads[NUM_THREADS];
	for(int i=0; i<NUM_THREADS; i++){ threads[i] = i; }
	struct INDEXS indexs[NUM_THREADS];
	for(int i=0; i<NUM_THREADS; i++){ seed[i] = rand(); }

	for(int i=0; i<NUM_THREADS; i++){
		indexs[i].start = i * POPULATION / NUM_THREADS;
		indexs[i].end = (i + 1) * POPULATION / NUM_THREADS - 1;
		indexs[i].thread = threads[i];
	}

	for(int i=0; i<NUM_THREADS; i++){
		pthread_create(&threads[i], NULL, &InitTwoOptPSX, &indexs[i]);
	}
	// sync threads
	for(int i=0; i<NUM_THREADS; i++){
		pthread_join(threads[i], NULL);
	}

	int best_indiv_id = GetBestIndividualID();
	int worst_indv_id = GetWorstIndividualID();
	int best_fitness = popul[best_indiv_id][DIMENSION];
	int best_fit_cnt = 0;

	printf("AG POSIX ...\n");
	printf("GEN\tMIN\tMAX\tPROM\tERROR\n");
	printf("---------------------------------------\n");

	int avg = 0;
	for(int i=0; i<POPULATION; i++) avg += popul[i][DIMENSION];
	float error = ((float)popul[best_indiv_id][DIMENSION] - (float)BEST_OLIB) / (float)BEST_OLIB * 100;
	printf("%d\t%d\t%d\t%d\t%.4f\n", 0, popul[best_indiv_id][DIMENSION], popul[worst_indv_id][DIMENSION], (avg)/POPULATION, error);


	for(int gener=0; gener<GENERATION; gener++){
		// run global crossing
		for(int i=0; i<NUM_THREADS; i++){
			pthread_create(&threads[i], NULL, &GlobalCrossing, &indexs[i]);
		}
		// sync threads
		for(int i=0; i<NUM_THREADS; i++){
			pthread_join(threads[i], NULL);
		}
		// run global crossing

		best_indiv_id = GetBestIndividualID();
		worst_indv_id = GetWorstIndividualID();
		avg = 0;
		for(int i=0; i<POPULATION; i++) avg += popul[i][DIMENSION];
		error = ((float)popul[best_indiv_id][DIMENSION] - (float)BEST_OLIB) / (float)BEST_OLIB * 100;
		printf("%d\t%d\t%d\t%d\t%.4f\n", gener+1, popul[best_indiv_id][DIMENSION], popul[worst_indv_id][DIMENSION], (avg)/POPULATION, error);

		if(error<ERROR || (popul[best_indiv_id][DIMENSION]==popul[worst_indv_id][DIMENSION] && popul[worst_indv_id][DIMENSION]==(avg)/POPULATION)) 
			break;
		ShufflePopulation();
	}

	printf("\nbest:\n");
	PrintRealTour(popul[best_indiv_id]);

	printf("\nworst:\n");
	PrintRealTour(popul[worst_indv_id]);

	//PlotIndividual(popul[best_indiv_id], "blue", "2", max_x, max_y);
	//PlotIndividual(popul[worst_indv_id], "red", "2", max_x, max_y);

	printf("\n");
	return 0;
}
