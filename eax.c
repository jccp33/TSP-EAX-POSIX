
#include "init.c"

int GetNextID(int current, int stock, int side){
    for(int i=0; i<DIMENSION; i++){
        if(popul[stock][i] == current){
            if(side && i==DIMENSION-1){
                return popul[stock][0];
            }else if(side && i!=DIMENSION-1){
                return popul[stock][i+1];
            }else if(!side && i==0){
                return popul[stock][DIMENSION-1];
            }else if(!side && i!=0){
                return popul[stock][i-1];
            }
        }
    }
}

void EAX_PSX(int pA, int pB){
    int next, side, full_up;
    int min_fitness = 1000000;
    int H[DIMENSION+1];
    int stock[DIMENSION];
    int new_pA[DIMENSION+1];
    for(int child=0; child<CHILDREN; child++){
        for(int i=0; i<DIMENSION; i++){
            stock[i] = i; H[i] = -1;
        }
        H[0] = rand() % DIMENSION; stock[H[0]] = -1;
        // EAX kernel
        for(int i=1; i<DIMENSION; i++){
            side = rand() % 2;
            if(i%2 == 1){
                // stockA
                if( stock[GetNextID(H[i-1], pA, side)] != -1 ){ 
                    next = GetNextID(H[i-1], pA, side);
                }else if( stock[GetNextID(H[i-1], pA, !side)] != -1){
                    next = GetNextID(H[i-1], pA, !side);
                }else{
                    next = -1;
                }
            }else{
                // stockB
                if( stock[GetNextID(H[i-1], pB, side)] != -1){ 
                    next = GetNextID(H[i-1], pB, side);
                }else if( stock[GetNextID(H[i-1], pB, !side)] != -1){
                    next = GetNextID(H[i-1], pB, !side);
                }else{
                    next = -1;
                }
            }
            if(next == -1){
                break;
            }else{
                H[i] = next;
                stock[next] = -1;
                full_up = i;
            }
        }
        // get nodes missing
        int missing = DIMENSION - full_up - 1; int missing_count = 0;
        int missings[missing];
        for(int i=0; i<DIMENSION; i++){
            if(stock[popul[pA][i]] != -1){
                missings[missing_count] = stock[popul[pA][i]]; //popul[pA][i];
                stock[popul[pA][i]] = -1;
                missing_count++;
            }
        }
        // two opt on missings
        // int mi , mj , ganancia , actual ;
        // do{
        //     mi = mj = ganancia =0;
        //     for(int i=1; i<missing-1; i++){
        //         for(int j=i+1; j<missing; j++){
        //             actual = + cost[ missings[i-1] ][ missings[i] ] + cost[ missings[j] ][ missings[(j+1)%missing ] ] - cost[ missings[i-1] ][ missings[j] ] - cost[ missings[i] ][ missings[(j+1)%missing ] ];
        //             if ( actual > ganancia ){
        //                 ganancia = actual ; mi = i ; mj = j ;
        //             }
        //         }
        //     }
        //     while(mi < mj){
        //         actual = missings[mi]; missings[mi] = missings[mj]; missings[mj] = actual ; mi++; mj--;
        //     }
        // }while ( ganancia >0);
        // complete valid tour
        missing_count = 0;
        for(int i=full_up+1; i<DIMENSION; i++){
            H[i] = missings[missing_count];
            missing_count++;
        }
        // two opt on new tour
        int aux; int improve = 1; 
        while(improve){
            improve = 0;
            int p1, p2, p3, p4, t3, t4, tmp_distance, max_distance;
            for(int i=0; i<DIMENSION; i++){
                max_distance = 0; p1 = i; p2 = (i + 1) % DIMENSION; int depth = 0; int list_itr = 1;
                while(depth < DEPTH){
                    for(int j=0; j<DIMENSION; j++){
                        if(H[j] == NNlist[H[p1]][list_itr].id){
                            t3 = j; t4 = (j + 1) % DIMENSION; break;
                        }
                    }
                    tmp_distance = cost[H[p1]][H[p2]] + cost[H[t3]][H[t4]] - cost[H[p1]][H[t3]] - cost[H[p2]][H[t4]];
                    if(max_distance < tmp_distance){
                        max_distance = tmp_distance; p3 = t3; p4 = t4;
                    }
                    depth++; list_itr++;
                }
                if(max_distance > 0){
                    if(p2 < p3){
                        for(int k = 0; k < (p3 - p2 + 1) / 2; k++){
                            aux = H[p2 + k]; H[p2 + k] = H[p3 - k]; H[p3 - k] = aux;
                        }   
                    }else{
                        for(int k = 0; k < (DIMENSION - (p2 - p3) + 1) / 2; k++){
                            aux = H[(p2 + k) % DIMENSION]; H[(p2 + k) % DIMENSION] = H[(p3 - k + DIMENSION) % DIMENSION]; H[(p3 - k + DIMENSION) % DIMENSION] = aux;
                        }
                    }
                    improve = 1;
                }
            }
        }
        // save new tour
        H[DIMENSION] = EvaluateFitness(H);
        if(H[DIMENSION] < min_fitness){
            min_fitness = H[DIMENSION];
            for(int l=0; l<DIMENSION+1; l++){
                new_pA[l] = H[l];
            }
        }
    }
    // replace parent A
    if(new_pA[DIMENSION] < popul[pA][DIMENSION]){
        for(int l=0; l<DIMENSION+1; l++){
            popul[pA][l] = new_pA[l];
        }
    }
}

void *GlobalCrossing(void *i){
    struct INDEXS* indexs = (struct INDEXS*)i;
    for(int indv=indexs->start; indv<indexs->end-1; indv++){
        for(int i=0; i<CHILDREN; i++){
            EAX_PSX(indv, indv+1);
        }
    }
    for(int i=0; i<CHILDREN; i++){
        EAX_PSX(indexs->end, indexs->start);
    }
}
