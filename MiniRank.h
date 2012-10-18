
#ifndef _MiniRank_h
#define _MiniRank_h

#include <pthread.h>

/*
 * A mini-rank will run in a pthread.
 */
class MiniRank{

	pthread_spinlock_t m_lock;
	bool m_hasFinished;
	int m_number;
public:
	void init(int number);
	void run();
	void lock();
	void unlock();
	bool hasFinished();
	void destroy();
};

#endif
