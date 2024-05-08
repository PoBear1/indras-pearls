#include "../cmplx_lib/complex_calc.h"
#include "../cmplx_lib/asy_drawing.h"
#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <map>
using namespace std;
class search_wordtree {
private:
// okay my brain is like dying right now so i have to make annotations
// here we first build a template list from which we calculate the entire list (pain...) (i was never good at bfs stuff; only could do dfs help)
// ----------------------------------------------------------------------
// THOUGHT PROCESS TO GET ALGORITHM
// ok let's plan this
// we are going to apply induction on this
// so the base case is given as the starting point
// now if we are going to produce the next level we need to take each element of the sequence and append it onto the end
// oh wait nvm i've got it i'm stoopid
// so first say how many elements were originally in the sequence (call this M)
// then go over each of these original elements (i.e. elements with index before M)
// after that we are going to take each element in order, then you know just generate from there by appending the number at the end unless if the number is equal 
// ----------------------------------------------------------------------
// here, no_generators DOES NOT INCLUDE the inverses
	static vector<vector<int>> generate_template(uint64_t irred_no_generators,int lvl) {
		vector<vector<int>> generate_sequence{};
		for(int i=0;i<2*irred_no_generators;++i) {
			generate_sequence.push_back({i});
		}
		// this is literally so that we can actually keep track of memory; after all i'm running this on a macbook pro so i don't have a lot of memory to spare
		vector<int> placebo{};
		uint64_t ptr1{0},ptr2{0};
		for(int i=1;i<=lvl;++i) {
			ptr2=generate_sequence.size();
			for(uint64_t k=ptr1;k<ptr2;++k) {
				for(int j=0;j<2*irred_no_generators;++j) {
					if(generate_sequence[k].back()!=(j+irred_no_generators)%(2*irred_no_generators)) {
						placebo=generate_sequence[k]; placebo.push_back(j);
						generate_sequence.push_back(placebo);
						placebo.clear();
					} else {}
				}
			}
			ptr1=ptr2;
		}
		return generate_sequence;
	}
public:
// obv. we first generate the entire list now; gl tho!
	static vector<pair<matrix,int>> generate_list(vector<matrix> v,int lvl) {
		auto irred_no_generators=(v.size())/2;
		vector<vector<int>> template_list=generate_template(irred_no_generators,lvl);
		vector<pair<matrix,int>> list{};
		matrix result{I};
		for(auto v1:template_list) {
			for(auto it=v1.rbegin();it!=v1.rend();--it) {
				result=v[(*it)]*result;
			}
			list.push_back({result,*(v1.rbegin())});
			result=I;
		}
		return list;
	}
};
class schottky_fractal {
private:
// alright time to construct our list of circles to plot!
// ok now how do i choose my circles properly
	matrix a,b,A,B;
	int lvl;
public:
	schottky_fractal(matrix a,matrix b,int lvl_in) {B=inv(b); A=inv(a); lvl=lvl_in;}
	vector<cline> produce_fractal(cline D_a,cline D_b,cline D_A,cline D_B) {
		vector<cline> circles;
		vector<pair<matrix,int>> list=search_wordtree::generate_list({a,b,A,B},lvl);
		for(auto i:list) {
			if(i.second!=2) {circles.push_back(D_a.mobius(i.first));} else {}
		}
		for(auto i:list) {
			if(i.second!=3) {circles.push_back(D_b.mobius(i.first));} else {}
		}
		for(auto i:list) {
			if(i.second!=0) {circles.push_back(D_A.mobius(i.first));} else {}
		}
		for(auto i:list) {
			if(i.second!=1) {circles.push_back(D_B.mobius(i.first));} else {}
		}
		return circles;
	}
};
int main() {
	return 0;
}
