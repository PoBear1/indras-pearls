#include "../cmplx_lib/complex_calc.h"
#include <iostream>
#include <complex>
int main() {
	cline circle(1,1,0,0);
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
	return 0;
}
