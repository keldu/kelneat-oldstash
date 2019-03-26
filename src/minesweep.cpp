#include "minesweep.h"

#include <random>
#include <iostream>

namespace KelNeat{
		void MineSweep::buildField(uint32_t a, uint32_t b, uint32_t mi){
			size.x = a;
			size.y = b;
			mines = mi;
			uncovered = 0;

			first_done = false;
			field.clear();

			for(uint32_t i = 0; i < size.x; ++i){
				for(uint32_t j = 0; j < size.y; ++j){

					field[ field_pos(i,j) ] = field_value(true,0);
					//field.insert(std::make_pair(field_pos(i,j),field_value(true,0) ) );
				}
			}
		}

		void MineSweep::distributeMines(){
			uint32_t a, b, mi;

			mi = mines;
			while(mi > 0){
				uint32_t a_r = rand();
				uint32_t b_r = rand();
				a = a_r % size.x;
				b = b_r % size.y;
				auto &ele = field.at(field_pos(a,b));
				if(ele.type == 0 && ele.covered){
					ele.type = -1;
					--mi;
				}
			}
			for(uint32_t i = 0; i < size.x; ++i){
				for(uint32_t j = 0; j < size.y; ++j){
					auto &ele = field.at(field_pos(i,j));
					if(ele.type >= 0){
						if( i == 0){
							if( j == 0){
								ele.type += field.at(field_pos(i+1,j)).type == -1 ? 1 : 0;
								ele.type += field.at(field_pos(i,j+1)).type == -1 ? 1 : 0;
								ele.type += field.at(field_pos(i+1,j+1)).type == -1 ? 1 : 0;
							}else if(j == (size.y-1)){
								ele.type += field.at(field_pos(i+1,j)).type == -1 ? 1 : 0;
								ele.type += field.at(field_pos(i,j-1)).type == -1 ? 1 : 0;
								ele.type += field.at(field_pos(i+1,j-1)).type == -1 ? 1 : 0;
							}else{
								ele.type += field.at(field_pos(i,j-1)).type == -1 ? 1 : 0;
								ele.type += field.at(field_pos(i+1,j-1)).type == -1 ? 1 : 0;
								ele.type += field.at(field_pos(i+1,j)).type == -1 ? 1 : 0;
								ele.type += field.at(field_pos(i+1,j+1)).type == -1 ? 1 : 0;
								ele.type += field.at(field_pos(i,j+1)).type == -1 ? 1 : 0;

							}
						}else if( i ==(size.x -1)){
							if( j == 0){
								ele.type += field.at(field_pos(i-1,j)).type == -1 ? 1 : 0;
								ele.type += field.at(field_pos(i-1,j+1)).type == -1 ? 1 : 0;
								ele.type += field.at(field_pos(i,j+1)).type == -1 ? 1 : 0;
							}else if ( j == (size.y -1)){
								ele.type += field.at(field_pos(i-1,j)).type == -1 ? 1 : 0;
								ele.type += field.at(field_pos(i-1,j-1)).type == -1 ? 1 : 0;
								ele.type += field.at(field_pos(i,j-1)).type == -1 ? 1 : 0;
							}else{
								ele.type += field.at(field_pos(i,j-1)).type == -1 ? 1 : 0;
								ele.type += field.at(field_pos(i-1,j-1)).type == -1 ? 1 : 0;
								ele.type += field.at(field_pos(i-1,j)).type == -1 ? 1 : 0;
								ele.type += field.at(field_pos(i-1,j+1)).type == -1 ? 1 : 0;
								ele.type += field.at(field_pos(i,j+1)).type == -1 ? 1 : 0;
							}
						}else{
							if( j== 0){
								ele.type += field.at(field_pos(i-1,j)).type == -1 ? 1 : 0;
								ele.type += field.at(field_pos(i-1,j+1)).type == -1 ? 1 : 0;
								ele.type += field.at(field_pos(i,j+1)).type == -1 ? 1 : 0;
								ele.type += field.at(field_pos(i+1,j+1)).type == -1 ? 1 : 0;
								ele.type += field.at(field_pos(i+1,j)).type == -1 ? 1 : 0;
							}else if( j == (size.y -1) ){
								ele.type += field.at(field_pos(i-1,j)).type == -1 ? 1 : 0;
								ele.type += field.at(field_pos(i-1,j-1)).type == -1 ? 1 : 0;
								ele.type += field.at(field_pos(i,j-1)).type == -1 ? 1 : 0;
								ele.type += field.at(field_pos(i+1,j-1)).type == -1 ? 1 : 0;
								ele.type += field.at(field_pos(i+1,j)).type == -1 ? 1 : 0;
							}else{
								ele.type += field.at(field_pos(i-1,j-1)).type == -1 ? 1 : 0;
								ele.type += field.at(field_pos(i,j-1)).type == -1 ? 1 : 0;
								ele.type += field.at(field_pos(i+1,j-1)).type == -1 ? 1 : 0;
								ele.type += field.at(field_pos(i-1,j)).type == -1 ? 1 : 0;
								ele.type += field.at(field_pos(i+1,j)).type == -1 ? 1 : 0;
								ele.type += field.at(field_pos(i-1,j+1)).type == -1 ? 1 : 0;
								ele.type += field.at(field_pos(i,j+1)).type == -1 ? 1 : 0;
								ele.type += field.at(field_pos(i+1,j+1)).type == -1 ? 1 : 0;
							}
						}
					}
				}
			}
			/*
			for(uint32_t i = 0; i < size.x; ++i){
				for(uint32_t j = 0; j < size.y; ++j){
					auto fi = field.at(field_pos(i,j));
					std::cout<<fi.type<<" ";
				}
				std::cout<<std::endl;
			}
			std::cout<<std::endl;
		

			for(uint32_t i = 0; i < size.x; ++i){
				for(uint32_t j = 0; j < size.y; ++j){
					auto fi = field.at(field_pos(i,j));
					std::cout<<fi.covered<<" ";
				}
				std::cout<<std::endl;
			}
			std::cout<<std::endl;
			*/
		}
		
		int MineSweep::uncover(uint32_t a, uint32_t b){
			auto ele = field.find( field_pos(a,b) );

			if(ele == field.end()){
				return -100;
			}
			if(!ele->second.covered){
				return -50;
			}

			if(!first_done){
				ele->second.covered = false;
				distributeMines();
				first_done = true;
				++uncovered;
				return ele->second.type > 0 ? 0 : 1;
			}

			if(ele->second.covered && ele->second.type >= 0){
				ele->second.covered = false;
				++uncovered;
				return ele->second.type > 0 ? 0 : 1;
			}

			if(size.x * size.y - mines - uncovered == 0){
				return 100;
			}

			if(ele->second.type == -1){
				return -10;
			}

			return 0;
		}

		int MineSweep::getEle(uint32_t a, uint32_t b){
			if(field.at(field_pos(a,b)).covered == true){
				return -1;
			}else{
				return field.at(field_pos(a,b)).type;
			}
		}
}