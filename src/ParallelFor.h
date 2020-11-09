/*
 * ParallelFor.h
 *
 *  Created on: Nov 4, 2020
 *      Author: nkafle89. Recreated with help from SO
 */

#ifndef SRC_PARALLELFOR_H_
#define SRC_PARALLELFOR_H_

#include <algorithm>
#include <thread>
#include <functional>
#include <vector>

static void parallel_for(unsigned nb_elements, std::function<void(int start, int end)> functor)
{
	unsigned nb_threads_hint = std::thread::hardware_concurrency();
	unsigned nb_threads = nb_threads_hint == 0 ? 8 : (nb_threads_hint);

	unsigned batch_size = nb_elements / nb_threads;
	unsigned batch_remainder = nb_elements % nb_threads;

	std::vector<std::thread> my_threads(nb_threads);


	for (unsigned i=0; i<nb_threads; ++i)
	{
		int start = i*batch_size;
		my_threads[i] = std::thread (functor, start, start+batch_size);
	}

	//for the elements left
	int start = nb_threads * batch_size;
	functor(start, start+batch_remainder);

	std::for_each(my_threads.begin(), my_threads.end(), std::mem_fn(&std::thread::join));
}



#endif /* SRC_PARALLELFOR_H_ */
