#ifndef COMPLEX_CALC_H
#define COMPLEX_CALC_H
#include <exception>
#include <complex>
// For simplicity's sake!
typedef std::complex<long double> complex;

// First typedef the matrix construct so the construct will then become
// {
// 		{a[0][0],a[0][1]},
// 		{a[1][0],a[1][1]}
// }
typedef std::array<std::array<complex,2>,2> matrix;
matrix I={{{1,0},{0,1}}};
complex det(matrix a) {
	return a[0][0]*a[1][1]-a[0][1]*a[1][0];
}
complex tr(matrix a) {
	return a[0][0]+a[1][1];
}
matrix inv(matrix a) {
	if(det(a)==complex(0)) {
		throw std::runtime_error("Error when calling \"matrix inv(matrix)\": attempting to invert matrix with determinant zero");
	} else {
		complex d=det(a);
		return {{{a[1][1]/d,-a[0][1]/d},{-a[1][0]/d,a[0][0]/d}}};
	}
}
matrix operator*(matrix a,matrix b) {
	return {
		{{a[0][0]*b[0][0]+a[0][1]*b[1][0],a[0][0]*b[0][1]+a[0][1]*b[1][1]},
		{a[1][0]*b[0][0]+a[1][1]*b[1][0],a[1][0]*b[0][1]+a[1][1]*b[1][1]}}
	};
}
matrix operator/(matrix a,matrix b) {return a*inv(b);}
matrix sl2(matrix a) {
	if(det(a)!=complex(0)) {
		complex d=det(a); 
		return {{{a[0][0]/sqrt(d),a[0][1]/sqrt(d)},{a[1][0]/sqrt(d),a[1][1]/sqrt(d)}}};
	} else {throw std::runtime_error("Attempting to normalise degenerate matrix");}
}

// mobius maps
complex operator*(matrix a,complex z) {
	return proj((a[0][0]*z+a[0][1])/(a[1][0]*z+a[1][1]));
}
std::array<complex,2> fixed_pts(matrix a) {
	if(a[1][0]!=complex(0)) {
		matrix b=sl2(a);
		return {(a[0][0]-a[1][1]+sqrt(tr(b)*tr(b)-complex(4)))/(complex(2)*a[1][0]),(a[0][0]-a[1][1]-sqrt(tr(b)*tr(b)-complex(4)))/(complex(2)*a[1][0])};
	} else {
		return {proj(complex(1)/complex(0)),a[0][1]/(a[1][1]-a[0][0])};
	}
}

// Geometric construct - attempting to consider lines and circles simultaneously which will be hard
// I just managed to bash out what the representation would become afterwards.
class cline {
private:
	// The representation will be basically like a|z|^2-2Re(z(b-ic))+d=0
	long double a,b,c,d;
public:
	cline(long double a,long double b,long double c,long double d):a(a),b(b),c(c),d(d) {
		// if(b*b+c*c<a*d) {throw std::runtime_error("Bad initialisation of cline class");}
	};
	long double radius() {
		if(a!=0) {
			return sqrt((b*b+c*c)/(a*a)-d/a);
		} else {
			return real(proj(complex(1)/complex(0)));
		}
	}
	long double offset() {
		return d/(2*sqrt(b*b+c*c));
	}
	complex direction() {
		return complex(b,c);
	}
	complex centre() {
		if(a!=0) {
			return complex(b/a,c/a);
		} else {
			return proj(complex(1)/complex(0));
		}
	}
	cline mobius(matrix T) {
		// god this was painful

		// AND this does not work every single time!!!!
		// Bro it DOES NOT work on lines! 
		// It doesn't even work reliably for CIRCLES!
		// Attempt 1 by converting into circle form then bashing
		// Doesn't work unsurprisingly because we have to divide by a somewhere
		// complex z=(T[0][1]+complex(b,c)*T[0][0])*(T[1][1]+conj(complex(b,c))*T[1][0])*a-T[0][0]*T[1][0]*(b*b+c*c-a*d);
		// return cline(
		// 	real(a*((T[1][1]+b*T[1][0])+T[1][0]*T[1][0]*c*c)-T[1][0]*T[1][0]*(b*b+c*c-a*d)),
		// 	real(z),
		// 	-imag(z),
		// 	real(a*((T[0][1]+b*T[0][0])+T[0][0]*T[0][0]*c*c)-T[0][0]*T[0][0]*(b*b+c*c-a*d))
		// );

		// Attempt 2 by plugging the inverse straight in and bashing
		// Actually works finally.
		complex z=(a*T[0][1]*T[1][1]+T[0][1]*T[1][0]*complex(b,c)+T[0][0]*T[1][1]*complex(b,-c)+d*T[0][0]*T[1][0]);
		return cline(
			real(a*T[1][1]*T[1][1]+d*T[1][0]*T[1][0]+(2*b)*T[1][0]*T[1][1]),
			real(z),
			imag(-z),
			real(a*T[0][1]*T[0][1]+d*T[0][0]*T[0][0]+(2*b)*T[0][0]*T[0][1])
		);
	}
	std::array<long double,4> get_params() {
		return {a,b,c,d};
	}
};
#endif
