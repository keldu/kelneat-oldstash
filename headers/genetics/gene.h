#pragma once

#include <stdint.h>

namespace KelNeat{
	class Gene{
	public:
		Gene(uint32_t,uint32_t,double,bool,uint32_t);
		Gene(const Gene& a);

		uint32_t getInput() const;
		uint32_t getOutput() const;
		uint32_t getInnovation() const;
		double getWeight() const;
		bool isActive() const;

	private:
		friend class Breeder;
		friend class Genome;

		uint32_t input; 
		uint32_t output;
		double weight;
		bool active;
		uint32_t innovation;
	};
}
