
#include "eax.c"

void PrintData(){
    printf("\nDATA:\n");
    printf("ID\tX\tY\n");
    printf("-------------------\n");
    for(int i=0; i<DIMENSION; i++){
        printf("%d\t%d\t%d\n",
            data[i][0],
            data[i][1],
            data[i][2]
        );
    }
    printf("\n");
}

void PrintCost(int elements){
    printf("COSTS:\n   |");
    for(int i=0; i<elements; i++){
        if(i<10) printf("   %d", i);
        else if(i>9 && i<100) printf("  %d", i);
        else printf(" %d", i);
    }
    printf("\n");
    for(int i=0; i<(elements+1)*4; i++) printf("-");
    printf("\n");
    for(int i=0; i<elements; i++){
        if(i<10) printf("  %d|", i);
        else if(i>9 && i<100) printf(" %d|", i);
        else printf("%d|", i);

        for(int j=0; j<elements; j++){
            if(cost[i][j] == 0) printf("    ");
            else if(cost[i][j]>0 && cost[i][j]<10) printf("   %d", cost[i][j]);
            else if(cost[i][j]<100 && cost[i][j]>9) printf("  %d", cost[i][j]);
            else printf(" %d", cost[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void PrintNNlist(int elements){
    printf("NNlist [id,dist]:\n");
    for(int i=0; i<elements; i++){
        printf("%d:\t", i);
        for(int j=0; j<elements; j++){
            printf("[%d,%d]\t", NNlist[i][j].id, NNlist[i][j].dist);
        }
        printf("\n");
    }
    printf("\n");
}

void PrintRealTour(int *t){
    for(int i=0; i<DIMENSION; i++){
        printf(" %d ", t[i]);
    }
    printf("\n");
    printf("*** FITNESS: %d\n", t[DIMENSION]);
}

void PrintAllFitness(){
    for(int i=0; i<POPULATION; i++){
        printf("%d:\t\t%d\n", i, popul[i][DIMENSION]);
    }
}

void InitFilePlot(char f_name[], int max_x, int max_y){
    FILE *graf = fopen(f_name, "w");
	fprintf(graf, "set xrange [%d:%d]\nset yrange [%d:%d]\n\n", -1, max_x+1, -1, max_y+1);
    fclose(graf);
}
void AddChangesFile(int *t, char f_name[], char color[], char width[], int gener){
    FILE *graf = fopen(f_name, "a");
    int lines;
    for(int j=0; j<DIMENSION-1; j++){
		fprintf(graf, 
            "set arrow %d from %d,%d to %d,%d nohead filled back lw %s lc rgb \"%s\"\n", 
            (j+1), data[ t[j] ][1], data[ t[j] ][2], data[ t[j+1] ][1], data[ t[j+1] ][2], 
            width, color
        );
        lines = j;
	}
    // last line
    fprintf(graf, 
        "set arrow %d from %d,%d to %d,%d nohead filled back lw %s lc rgb \"%s\"\n", 
        (lines+2), data[ t[DIMENSION-1] ][1], data[ t[DIMENSION-1] ][2], data[ t[0] ][1], data[ t[0] ][2], 
        width, color
    );
    fprintf(graf, "plot '-'  w p ls 7 lc rgb \"red\" pointsize 0 title \"generacion: %d\"\n", gener);
	fprintf(graf, "%d %d\ne\n", data[ t[0] ][1], data[ t[0] ][2]);
    fprintf(graf, "\npause 0.5\nrefresh\n\n");
    fclose(graf);
}
void AddEndFile(char f_name[]){
    FILE *graf = fopen(f_name, "a");
	fprintf(graf, "\npause -1\n");
	fclose(graf);
}

void PlotIndividual(int *t, char color[], char width[], int max_x, int max_y){
    FILE *graf = fopen("indv.dat", "w");
    int lines;
	fprintf(graf, "set xrange [%d:%d]\nset yrange [%d:%d]\n\n", -1, max_x+1, -1, max_y+1);
	for(int j=0; j<DIMENSION-1; j++){
		fprintf(graf, 
            "set arrow %d from %d,%d to %d,%d nohead filled back lw %s lc rgb \"%s\"\n", 
            (j+1), data[ t[j] ][1], data[ t[j] ][2], data[ t[j+1] ][1], data[ t[j+1] ][2], 
            width, color
        );
		fprintf(graf, "plot '-'  w p ls 7 lc rgb \"#0B6138\" pointsize 0 notitle\n");
		fprintf(graf, "%d %d\ne\n", data[ t[0] ][1], data[ t[0] ][2]);
		fprintf(graf, "\npause 0.1\nrefresh\n\n");
        lines = j;
	}
    // last line
    fprintf(graf, 
        "set arrow %d from %d,%d to %d,%d nohead filled back lw %s lc rgb \"%s\"\n", 
        (lines+2), data[ t[DIMENSION-1] ][1], data[ t[DIMENSION-1] ][2], data[ t[0] ][1], data[ t[0] ][2], 
        width, color
    );
	fprintf(graf, "plot '-'  w p ls 7 lc rgb \"#0B6138\" pointsize 0 notitle\n");
	fprintf(graf, "%d %d\ne\n", data[ t[0] ][1], data[ t[0] ][2]);
    fprintf(graf, "\npause 0.1\nrefresh\n\n");
	fprintf(graf, "\npause -1\n");
	fclose(graf);
    system("gnuplot \"indv.dat\"");
}

void PlotParents(int *p1, int *p2, int max_x, int max_y){
    int init_p1, init_p2;
    FILE *graf = fopen("img/parents.dat", "w");
    init_p1 = 1;
    init_p2 = DIMENSION + 10;
    fprintf(graf, "set xrange [%d:%d]\nset yrange [%d:%d]\n\n", -1, max_x+1, -1, max_y+1);
    for(int j=0; j<DIMENSION-1; j++){
        fprintf(graf, 
            "set arrow %d from %d,%d to %d,%d nohead filled back lw 2 lc rgb \"gray\"\n", 
            (init_p1), data[ p1[j] ][1], data[ p1[j] ][2], data[ p1[j+1] ][1], data[ p1[j+1] ][2]
        );
        fprintf(graf, 
            "set arrow %d from %d,%d to %d,%d nohead filled back lw 1 lc rgb \"black\" dashtype 2\n", 
            (init_p2), data[ p2[j] ][1], data[ p2[j] ][2], data[ p2[j+1] ][1], data[ p2[j+1] ][2]
        );
        init_p1++;
        init_p2++;
    }
    // last lines
    fprintf(graf, 
        "set arrow %d from %d,%d to %d,%d nohead filled back lw 2 lc rgb \"gray\"\n", 
        (init_p1+1), 
        data[ p1[DIMENSION-1] ][1], data[ p1[DIMENSION-1] ][2], data[ p1[0] ][1], data[ p1[0] ][2]
    );
    fprintf(graf, 
        "set arrow %d from %d,%d to %d,%d nohead filled back lw 1 lc rgb \"black\" dashtype 2\n", 
        (init_p2+1), 
        data[ p2[DIMENSION-1] ][1], data[ p2[DIMENSION-1] ][2], data[ p2[0] ][1], data[ p2[0] ][2]
    );
    // flot points
    fprintf(graf, "\n");
	fprintf(graf, "plot '-'  w p ls 7 lc rgb \"red\" pointsize 0.5 notitle\n");
    for(int j=0; j<DIMENSION; j++){
        fprintf(graf, "%d %d\n", data[j][1], data[j][2]);
    }
    fprintf(graf, "e\n");
    fprintf(graf, "\npause -1\n");
	fclose(graf);
    system("gnuplot \"img/parents.dat\"");
}

void PlotCycleFromTo(int *tour, int from, int to, int max_x, int max_y){
    //printf("%d -> %d\n", tour[from], tour[to]);
    FILE *graf = fopen("img/cycleAB.dat", "w");
    fprintf(graf, "set xrange [%d:%d]\nset yrange [%d:%d]\n\n", -1, max_x+1, -1, max_y+1);
    int line = 1;
    for(int j=from; j<to; j++){
        if(line%2 == 0){
            fprintf(graf, 
                "set arrow %d from %d,%d to %d,%d nohead filled back lw 2 lc rgb \"black\" dashtype 2\n", 
                line, data[ tour[j] ][1], data[ tour[j] ][2], data[ tour[j+1] ][1], data[ tour[j+1] ][2]
            );
        }else{
            fprintf(graf, 
                "set arrow %d from %d,%d to %d,%d nohead filled back lw 2 lc rgb \"gray\"\n", 
                line, data[ tour[j] ][1], data[ tour[j] ][2], data[ tour[j+1] ][1], data[ tour[j+1] ][2]
            );
        }
        line++;
    }
    // last line
    if(line%2 == 0){
        fprintf(graf, 
            "set arrow %d from %d,%d to %d,%d nohead filled back lw 2 lc rgb \"black\" dashtype 2\n", 
            line, data[ tour[to] ][1], data[ tour[to] ][2], data[ tour[from] ][1], data[ tour[from] ][2]
        );
    }else{
        fprintf(graf, 
            "set arrow %d from %d,%d to %d,%d nohead filled back lw 2 lc rgb \"gray\"\n", 
            line, data[ tour[to] ][1], data[ tour[to] ][2], data[ tour[from] ][1], data[ tour[from] ][2]
        );
    }
    // flot points
    fprintf(graf, "\n");
	fprintf(graf, "plot '-'  w p ls 7 lc rgb \"red\" pointsize 0.5 notitle\n");
    for(int j=0; j<DIMENSION; j++){
        fprintf(graf, "%d %d\n", data[j][1], data[j][2]);
    }
    fprintf(graf, "e\n");
    fprintf(graf, "\npause -1\n");
	fclose(graf);
    system("gnuplot \"img/cycleAB.dat\"");
}

void PlotIntermediateSolution(int *p1, int p1_from, int p1_to, int *p2, int p2_from, int p2_to, int max_x, int max_y){
    int init_p1, init_p2;
    FILE *graf = fopen("img/intermediate.dat", "w");
    init_p1 = 1;
    init_p2 = DIMENSION + 10;
    fprintf(graf, "set xrange [%d:%d]\nset yrange [%d:%d]\n\n", -1, max_x+1, -1, max_y+1);

    // plot cycle AB
    for(int j=p1_from; j<p1_to; j++){
        fprintf(graf, 
            "set arrow %d from %d,%d to %d,%d nohead filled back lw 2 lc rgb \"black\"\n", 
            (init_p1), data[ p1[j] ][1], data[ p1[j] ][2], data[ p1[j+1] ][1], data[ p1[j+1] ][2]
        );
        init_p1++;
    }
    // last line
    fprintf(graf, 
        "set arrow %d from %d,%d to %d,%d nohead filled back lw 2 lc rgb \"black\"\n", 
        (init_p1+1), 
        data[ p1[p1_to-1] ][1], data[ p1[p1_to-1] ][2], data[ p1[0] ][1], data[ p1[0] ][2]
    );

    // plot intermediate
    for(int j=p2_from; j<p2_to; j++){
        fprintf(graf, 
            "set arrow %d from %d,%d to %d,%d nohead filled back lw 2 lc rgb \"gray\"\n", 
            (init_p2), data[ p2[j] ][1], data[ p2[j] ][2], data[ p2[j+1] ][1], data[ p2[j+1] ][2]
        );
        init_p2++;
    }
    // last line
    fprintf(graf, 
        "set arrow %d from %d,%d to %d,%d nohead filled back lw 2 lc rgb \"gray\"\n", 
        (init_p2+1), 
        data[ p2[p2_to-1] ][1], data[ p2[p2_to-1] ][2], data[ p2[0] ][1], data[ p2[0] ][2]
    );

    // flot points
    fprintf(graf, "\n");
	fprintf(graf, "plot '-'  w p ls 7 lc rgb \"black\" pointsize 0.5 notitle\n");
    for(int j=0; j<DIMENSION; j++){
        fprintf(graf, "%d %d\n", data[j][1], data[j][2]);
    }
    fprintf(graf, "e\n");
    fprintf(graf, "\npause -1\n");
	fclose(graf);
    system("gnuplot \"img/intermediate.dat\"");
}
