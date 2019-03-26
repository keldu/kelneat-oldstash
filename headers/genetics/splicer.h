#pragma once

#include "genome.h"

namespace KelNeat{
	class GenePool;
	//Splicer builds Genome from Database Genes
	class Splicer{
	public:
		int32_t buildGenome(uint32_t id, Genome& genome, GenePool& pool);
	private:
	};
}