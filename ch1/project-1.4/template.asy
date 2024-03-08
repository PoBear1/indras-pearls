size(24cm);
picture hexagon;
real opacity_num=0.05;
filldraw(hexagon,dir(60)--dir(120)--dir(180)--dir(240)--dir(300)--dir(0)--cycle,red+opacity(opacity_num),orange);
real a=100*sqrt(2);
for(int i=0;i<200;++i) {
	add(rotate(a*i)*(shift(5)*hexagon));
}
