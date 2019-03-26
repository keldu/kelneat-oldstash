#pragma once

#include <stdint.h>
#include <map>
#include <functional>

namespace KelNeat{
		class MineSweep{
		public:
			void buildField(uint32_t a, uint32_t b, uint32_t mi);

			int uncover(uint32_t a, uint32_t b);
			void distributeMines();

			uint32_t score(){return uncovered;}

			int getEle(uint32_t a, uint32_t b);

		private:

			class field_pos{
			public:
				field_pos():field_pos(0,0){}
				field_pos(uint32_t a, uint32_t b):x(a),y(b){}
				field_pos(const field_pos& cop):x(cop.x),y(cop.y){}
				uint32_t x,y;
				/*
				bool operator<(const field_pos& k) const
    			{
					return (x<k.x || (y < k.y && x >= k.x));
    			}
    			*/
    			
			};
			uint32_t mines;
			uint32_t uncovered;
			field_pos size;
			class field_value{
			public:
				field_value():field_value(true,0){}
				field_value(bool a, int b):covered(a),type(b){}
				bool covered;
				int type;
			};

			class Compa{
			public:
			bool operator()(const field_pos& a, const field_pos& b) const {
        		return (a.x<b.x || (a.y < b.y && a.x == b.x));
    		}
    		};


			std::map<field_pos, field_value,Compa> field;

			bool first_done;


			// -1 hidden; 0-8 mine neighbor number;
		};
}
