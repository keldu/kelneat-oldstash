#pragma once

#include <stdint.h>

namespace KelNeat{
	class Edge{
	public:
		Edge();

		void setData(uint32_t in, uint32_t out, float weight);

		uint32_t getInput() const;
		uint32_t getOutput() const;
		float getWeight() const;

	private:
		uint32_t input, output;
		float weight;
	};
}