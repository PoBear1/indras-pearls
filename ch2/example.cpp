#include "../cmplx_lib/complex_calc.h"
#include <iostream>
#include <complex>
int main() {
	cline circle(2,0,0,-2);
	matrix invert_mat{{{0,1},{1,0}}};
	cline invert=circle.mobius(invert_mat);
	std::cout<<"\"circle\" centre: "<<circle.centre()<<", radius: "<<circle.radius()<<std::endl;
	std::cout<<"\"invert\" centre: "<<invert.centre()<<", radius: "<<invert.radius()<<std::endl;
	std::cout<<"\"invert\" offset: "<<invert.offset()<<", dir: "<<invert.direction()<<std::endl;
	std::cout<<"\"invert\" parameters: ";
	std::array<long double,4> a=invert.get_params();
	for(auto i:a) {
		std::cout<<i<<", ";
	}
	std::cout<<"\b\b  "<<std::endl;
	cline line(0,2,0,2);
	cline invert_line=line.mobius(invert_mat);
	std::cout<<"\"line\" offset: "<<line.offset()<<", dir: "<<line.direction()<<std::endl;
	std::cout<<"\"line\" centre: "<<line.centre()<<", radius: "<<line.radius()<<std::endl;
	std::cout<<"\"invert_line\" centre: "<<invert_line.centre()<<", radius: "<<invert_line.radius()<<std::endl;
	std::cout<<"\"invert_line\" offset: "<<invert_line.offset()<<", dir: "<<invert_line.direction()<<std::endl;
	std::cout<<"\"invert_line\" parameters: ";
	std::array<long double,4> b=invert_line.get_params();
	for(auto i:b) {
		std::cout<<i<<", ";
	}
	std::cout<<"\b\b  "<<std::endl;
	return 0;
}
