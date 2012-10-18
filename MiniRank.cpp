#include <iostream>
using namespace std;

#include "MiniRank.h"
#include <stdint.h>
#include <pthread.h>

void MiniRank::lock(){
	pthread_spin_lock(&m_lock);
}

void MiniRank::unlock(){
	pthread_spin_unlock(&m_lock);
}

void MiniRank::run(){

	uint64_t ticks=20000000;

	pthread_spin_init(&m_lock,PTHREAD_PROCESS_PRIVATE);

	lock();
	m_hasFinished=false;
	unlock();

	cout<<"Running MiniRank # "<<m_number<<endl;

	while(ticks--){

		lock();

		if(ticks%1000000==0){
			cout<<"MiniRank # "<<m_number<<" is advancing "<<ticks<<endl;
		}

		// do stuff

		unlock();
	}

	lock();
	m_hasFinished=true;
	unlock();

	cout<<"MiniRank # "<<m_number<<" finished"<<endl;
}

bool MiniRank::hasFinished(){
	return m_hasFinished;
}

void MiniRank::destroy(){

	pthread_spin_destroy(&m_lock);
}

void MiniRank::init(int number){
	m_number=number;
}
