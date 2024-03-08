unitsize(2cm);
path hexagon=dir(0)--dir(60)--dir(120)--dir(180)--dir(240)--dir(300)--cycle;
pair genT=(3,0),genS=(1.5,0.5*sqrt(3));
path clip_boundary=(10,10)--(10,-10)--(-10,-10)--(-10,10)--cycle;
pen[] nice_colours={red,yellow,blue,green,fuchsia,purple,cyan};
for(int i=-20;i<=20;++i) {
	for(int j=-20;j<=20;++j) {
		filldraw(shift(i*genT+j*genS)*hexagon,nice_colours[(5*i*j*j+j*j*j)%7],black);
	}
}
clip(clip_boundary);
