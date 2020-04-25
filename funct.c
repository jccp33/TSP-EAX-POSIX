
#include "param.c"

int GetMaxX(){
    int x = 0;
    for(int i=0; i<DIMENSION; i++){
        if(data[i][1] > x){
            x = data[i][1];
        }
    }
    return x;
}

int GetMaxY(){
    int y = 0;
    for(int i=0; i<DIMENSION; i++){
        if(data[i][2] > y){
            y = data[i][1];
        }
    }
    return y;
}

int Euclidean2D(float x1, float y1, float x2, float y2){
    float x = x2 - x1;
    float y = y2 - y1;
    return round(sqrt(x*x + y*y));
}

float RealEuclidean2D(float x1, float y1, float x2, float y2){
    float x = x2 - x1;
    float y = y2 - y1;
    return sqrt(x*x + y*y);
}

int ExistInRange(int *array, int data, int from, int to){
    for(int i=from; i<to; i++){
        if(array[i] == data) return 1;
    }
    return 0;
}

int EvaluateFitness(int *indiv){
    int fitness = 0;
    for(int i=0; i<DIMENSION-1; i++){
        fitness = fitness + cost[ indiv[i] ][ indiv[i+1] ];
    }
    fitness = fitness + cost[ indiv[DIMENSION-1] ][ indiv[0] ];
    return fitness;
}

int InputFile(){
    FILE *file = fopen(INPUT_FILE, "rb");
    char buffer[255];
    int fscanf_r = 0;
	if(file == NULL){
		printf("*** FILE DONT FOUND ***\n");
	}else{
		int cont = 0;
        printf("\n");
		while(fgets(buffer, 255, (FILE*) file)){
            if(cont>=5 && cont<6+DIMENSION){
                fscanf_r = fscanf(file, "%d %d %d", &data[cont-5][0], &data[cont-5][1], &data[cont-5][2]);
                data[cont-5][0] = data[cont-5][0] - 1;
            }
            cont++;
        }
	}
	fclose(file);
    return fscanf_r;
}

void CalculateCost(){
    int dist;
    struct PAIR tmp;
    for(int i=0; i<DIMENSION; i++){
        for(int j=0; j<DIMENSION; j++){
            dist = Euclidean2D(
                (float)data[i][1],
                (float)data[i][2],
                (float)data[j][1],
                (float)data[j][2]
            );
            NNlist[i][j].id = j;
            NNlist[i][j].dist = dist;
            NNlist[j][i].id = i;
            NNlist[j][i].dist = dist;
            cost[i][j] = dist;
        }
    }
    for(int i=0; i<DIMENSION; i++){
        for(int j=0; j<DIMENSION-1; j++){
            for(int k=0; k<DIMENSION-1; k++){
                if(NNlist[i][k].dist > NNlist[i][k+1].dist){
                    tmp.id = NNlist[i][k].id;
                    tmp.dist = NNlist[i][k].dist;
                    NNlist[i][k].id = NNlist[i][k+1].id;
                    NNlist[i][k].dist = NNlist[i][k+1].dist;
                    NNlist[i][k+1].id = tmp.id;
                    NNlist[i][k+1].dist = tmp.dist;
                }
            }
        }
    }
}

int ShufflePopulation(){
    int aux[DIMENSION+1];
    int ind1, ind2;
    for(int i=0; i<POPULATION; i++){
        do{
            ind1 = rand() % POPULATION;
            ind2 = rand() % POPULATION;
        }while(ind1 == ind2);

        for(int j=0; j<DIMENSION+1; j++){
            aux[j] = popul[ind1][j];
        }

        for(int j=0; j<DIMENSION+1; j++){
            popul[ind1][j] = popul[ind2][j];
        }

        for(int j=0; j<DIMENSION+1; j++){
            popul[ind2][j] = aux[j];
        }
    }
}

int GetBestIndividualID(){
    int id_min, min;
    id_min = 0;
    min = 1000000;
    for(int i=0; i<POPULATION; i++){
        if(popul[i][DIMENSION] < min){
            id_min = i;
            min = popul[i][DIMENSION];
        }
    }
    return id_min;
}

int GetWorstIndividualID(){
    int id_max, max;
    id_max = 0;
    max = 0;
    for(int i=0; i<POPULATION; i++){
        if(popul[i][DIMENSION] > max){
            id_max = i;
            max = popul[i][DIMENSION];
        }
    }
    return id_max;
}
