defaultpen(fontsize(10pt));
usepackage("amsmath");
usepackage("amssymb");
settings.tex="pdflatex";
settings.outformat="pdf";
// Replacement for olympiad+cse5 which is not standard
import geometry;
import graph;
import math;
real markscalefactor=0.02;
// recalibrate fill and filldraw for conics
void filldraw(picture pic = currentpicture, conic g, pen fillpen=defaultpen, pen drawpen=defaultpen)
{ filldraw(pic, (path) g, fillpen, drawpen); }
void fill(picture pic = currentpicture, conic g, pen p=defaultpen)
{ filldraw(pic, (path) g, p); }
// some geometry
guide Circle(pair O,pair A) { return circle(O,abs(O-A)); }
pair foot(pair P, pair A, pair B) { return foot(triangle(A,B,P).VC); }
pair orthocenter(pair A, pair B, pair C) { return orthocentercenter(A,B,C); }
pair centroid(pair A, pair B, pair C) { return (A+B+C)/3; }
pair circumcenter(pair A=(0,0), pair B=(0,0), pair C=(0,0)) {
	pair M,N,P,Q; 
	M=midpoint(A--B); 
	N=midpoint(B--C); 
	P=rotate(90,M)*A; 
	Q=rotate(90,N)*B; 
	return extension(M,P,N,Q);
}
pair incenter(pair A=(0,0), pair B=(0,0), pair C=(0,0)) { 
	pair P,Q; 
	P=rotate((angle(C-A)-angle(B-A))*90/pi,A)*B; 
	Q=rotate((angle(A-B)-angle(C-B))*90/pi,B)*C; 
	return extension(A,P,B,Q);
}
real inradius(pair A,pair B,pair C) { 
	real a,b,c,s; 
	a=abs(B-C); 
	b=abs(A-C); 
	c=abs(B-A); 
	s=(a+b+c)/2; 
	return sqrt(s*(s-a)*(s-b)*(s-c))/s;
}
guide incircle(pair A=(0,0), pair B=(0,0), pair C=(0,0)) { return Circle(incenter(A,B,C),inradius(A,B,C));}
// cse5 abbreviations
path CP(pair P, pair A) { return circle(P, abs(A-P)); }
path CR(pair P, real r) { return circle(P, r); }
pair IP(path p, path q) { return intersectionpoints(p,q)[0]; }
pair OP(path p, path q) { return intersectionpoints(p,q)[1]; }
path Line(pair A, pair B, real a=0.6, real b=a) { return (a*(A-B)+A)--(b*(B-A)+B); }
// cse5 more useful functions
picture CC() {
	picture p=rotate(0)*currentpicture;
	currentpicture.erase();
	return p;
}
pair MP(Label s, pair A, pair B = plain.S, pen p = defaultpen) {
	Label L = s;
	label(L, A, B, p);
	return A;
}
pair Drawing(Label s = "", pair A, pair B = plain.S, pen p = defaultpen) {
	dot(MP(s, A, B, p), p);
	return A;
}
path Drawing(path g, pen p = defaultpen, arrowbar ar = None) {
	draw(g, p, ar);
	return g;
}
path rightanglemark(pair A, pair B, pair C, real s=8) { 
	pair P,Q,R; 
	P=s*markscalefactor*unit(A-B)+B; 
	R=s*markscalefactor*unit(C-B)+B; 
	Q=P+R-B; 
	return P--Q--R;
}
pair bisectorpoint(pair A ... pair[] BC) {
	pair P,B,C,M; 
	if (BC.length==1) {  
		B=BC[0];  
		M=midpoint(A--B);  
		P=unit(rotate(90,M)*A-M)+M; 
	} 
	else if (BC.length==2) {  
		B=BC[0];  
		C=BC[1];  
		P=unit(midpoint((unit(A-B)+B)--(unit(C-B)+B))-B)+B; 
	} 
	return P;
}
unitsize(10cm);
draw(circle((1, 0), 1), heavygreen);
draw(Line((0.5, 1000), (0.5, -1000)), orange);
draw(Line((-0.5, 1000), (-0.5, -1000)), orange);
draw(circle((-1, 0), 1), heavygreen);
clip((-3,-3)--(-3,3)--(3,3)--(3,-3)--cycle);
