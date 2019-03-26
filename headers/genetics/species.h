#pragma once

#include <memory>
#include <stdint.h>

#include "genome.h"

namespace KelNeat{
	class Species{
	public:
		Species();
	private:
		uint32_t topFitness;
		uint32_t id;
	};
}