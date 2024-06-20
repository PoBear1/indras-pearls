#ifndef SCHOTTKY_PLOT_H
#define SCHOTTKY_PLOT_H
#include "../cmplx_lib/complex_calc.h"
#include "../cmplx_lib/asy_drawing.h"
#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <array>
#include <map>
using std::vector;
using std::pair;
using std::string;
using std::array;
class search_wordtree {
public:
// okay my brain is like dying right now so i have to make annotations
// here we first build a template list from which we calculate the entire list (pain...) 
// (i was never good at bfs stuff; only could do dfs help)
// ----------------------------------------------------------------------
// THOUGHT PROCESS TO GET ALGORITHM
// ok let's plan this
// we are going to apply induction on this
// so the base case is given as the starting point
// now if we are going to produce the next level we need to take each element of the sequence and append it onto the end
// oh wait nvm i've got it i'm stoopid
// so first say how many elements were originally in the sequence (call this M)
// then go over each of these original elements (i.e. elements with index before M)
// after that we are going to take each element in order, then you know just generate from there 
// by appending the number at the end unless if the number is equal 
// ----------------------------------------------------------------------
// here, no_generators DOES NOT INCLUDE the inverses
	static vector<vector<int>> generate_template(uint64_t irred_no_generators,int lvl) {
		vector<vector<int>> generate_sequence{};
		for(int i=0;i<2*irred_no_generators;++i) {
			generate_sequence.push_back({i});
		}
		// this is literally so that we can actually keep track of memory; after all i'm running this on a macbook pro 
		// so i don't have a lot of memory to spare
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
		generate_sequence.insert(generate_sequence.begin(),{});
		return generate_sequence;
	}
// obv. we first generate the entire list now; gl tho!
	static vector<pair<matrix,int>> generate_list(vector<matrix> v,int lvl) {
		auto irred_no_generators=(v.size())/2;
		vector<vector<int>> template_list=generate_template(irred_no_generators,lvl);
		vector<pair<matrix,int>> list{};
		matrix result{I};
		for(auto v1:template_list) {
			for(auto it=v1.rbegin();it!=v1.rend();++it) {
				result=v[(*it)]*result;
			}
			list.push_back({result,*(v1.rbegin())});
			result=I;
		}
		return list;
	}
};
// wait lol there's a way to construct good circles!
class schottky_fractal {
private:
	matrix a,b,A,B;
	int lvl;
public:
	schottky_fractal(matrix a_in,matrix b_in,int lvl_in) {a=a_in; b=b_in; B=inv(b_in); A=inv(a_in); lvl=lvl_in;}
	pair<cline,cline> generate_pair(cline D,matrix T) {
		auto fixed=fixed_pts(T); 
		if(abs(fixed[0]-D.centre())>D.radius()&&abs(fixed[1]-D.centre())>D.radius()) {
			throw std::runtime_error("Attempting to use circles not containing fixed points");
		} else {}
		if((D.mobius(T)).radius()<D.radius()) {
			if((D.mobius(T)).contains(T*(D.centre()))) {
				throw std::runtime_error("Attempting to use circle containing negative fixed point");
			} else {
				return {D,D.mobius(T)};
			}
		} else if((D.mobius(T)).radius()==D.radius()) {
			return {D,D.mobius(T)};
		} else {
			// i miss year 9...
			cline prev{D},now{D.mobius(T)};
			while(now.contains(T*prev.centre())) {
				prev=now;
				now=prev.mobius(T);
			}
			return {prev,now}; 
		}
	}
	vector<pair<cline,int>> produce_fractal(cline D_a,cline D_b,cline D_A,cline D_B) {
		vector<pair<cline,int>> circles;
		vector<pair<matrix,int>> list=search_wordtree::generate_list({a,b,A,B},lvl);
		for(auto i:list) {
			if(i.second!=2) {circles.push_back({D_a.mobius(i.first),0});} else {}
			if(i.second!=3) {circles.push_back({D_b.mobius(i.first),1});} else {}
			if(i.second!=0) {circles.push_back({D_A.mobius(i.first),2});} else {}
			if(i.second!=1) {circles.push_back({D_B.mobius(i.first),3});} else {}
		}
		return circles;
	}
};
#endif
