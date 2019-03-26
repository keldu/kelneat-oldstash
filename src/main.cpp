#include "neat.h"

#include <iostream>
#include <array>

#include "minesweep.h"



int main(int argc, const char** argv){

	KelNeat::MineSweep sweep;

	KelNeat::Neat neat("test.db");

	uint32_t m = 5;
	uint32_t n = 5;
	uint32_t mine = 5;

	int rc = neat.loadPool();
	if(rc != 0){
		rc = neat.createPool(m*n,m*n,true, false);
		if(rc != 0){
			std::cout<<"Couldn't create Pool"<<std::endl;
		}else{
			neat.createPopulation(100);
			std::cout<<"Pool created"<<std::endl;	
		}
	}else{
		std::cout<<"Pool loaded"<<std::endl;
	}

	//simple game minesweeper

	uint32_t current;

	size_t sample = 0;
	while(sample < 100000){

	if(neat.isGenomeUnevaluatedEmpty()){
		size_t refill = neat.refillUnevaluatedQueue(50);
		if( refill == 0 ){
			neat.cloneBestPopulation(20, 5);
			neat.refillUnevaluatedQueue(50);
		}
	}
	
	current = neat.getNextUnevaluatedGenomes();

	sweep.buildField(m, n, mine);
	std::unique_ptr<KelNeat::Network> network = neat.createRecurrentNetwork(current);

	int64_t score = 0;

	int64_t next = 0;

	uint32_t pos_x;
	uint32_t pos_y;
	while(true){
		for(size_t i = 0; i < m; ++i){
			for(size_t j = 0; j < n; ++j){
				network->setInput(sweep.getEle(i, j), i*n + j);
			}
		}

		for(size_t i = 0; i < 50; ++i){
			network->step();
		}

		double max = network->getOutput(0);
		uint32_t max_pos_x = 0;
		uint32_t max_pos_y = 0;
		for(size_t i = 0; i < m; ++i){
			for(size_t j = 0; j < n; ++j){
				float max_help = network->getOutput(i*n + j);
				if(max_help > max){
					max = max_help;
					max_pos_x = i;
					max_pos_y = j;
				}
			}
		}
		pos_x = max_pos_x;
		pos_y = max_pos_y;

		next = sweep.uncover(pos_x,pos_y);

		if(next == -10){
			score += -10;
			break;
		}else if( next == -100){
			score += -100;
			break;
		}else if( next == 100){
			score += 100;
			break;
		}else if(next == -50){
			score += -50;
			break;
		}else{
			score += next;
		}
	}
	score += sweep.score();

	//std::cout<<"predicted Pos "<<pos_x<<" "<<pos_y<<std::endl;
	std::cout<<"Current Genome: "<<current
	<<" has Score "<<score<<" and pos: "<<pos_x<<" "<<pos_y
	<<std::endl;
	network->setFitness(score);
	network->evaluate();
	
	++sample;

	}

	return 0;
}
