#include <iostream>
using namespace std;

#include "Rank.h"
#include "MiniRank.h"

#define THREADS 16

void * callIt(void*data){
	((MiniRank*)data)->run();
}

void Rank::run(){

	pthread_t threads[THREADS];
	MiniRank miniRanks[THREADS];

/*
 * Start the mini-ranks in parallel.
 */
	for(int i=0;i<THREADS;i++){
		MiniRank*miniRank=miniRanks+i;
		miniRank->init(i);
		cout<<"Starting MiniRank # "<<i<<endl;
		pthread_create(threads+0,NULL,callIt,miniRank);
	}

	bool execute=true;

/*
 * In this loop, the Rank will receive messages and give
 * them to mini-ranks. Furthermore, the Rank will pick up 
 * messages from mini-ranks and send them.
 */
	while(execute){
		
		int deadMiniRanks=0;

		for(int i=0;i<THREADS;i++){
			MiniRank*miniRank=miniRanks+i;
			miniRank->lock();

			if(miniRank->hasFinished())
				deadMiniRanks++;

			miniRank->unlock();
		}

		if(deadMiniRanks==THREADS)
			execute=false;
	}

/*
 * Destroy the mini-ranks.
 */
	for(int i=0;i<THREADS;i++)
		miniRanks[i].destroy();
}
