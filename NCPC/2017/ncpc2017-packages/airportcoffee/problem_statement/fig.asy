import graph3;
unitsize(1cm);

defaultpen(fontsize(9pt));
fill(circle((0, 0), 0.1));
fill(circle((10, 0), 0.1));
label("$0$", (0, 0.4));
label("$100\,000$", (10, 0.4));

draw((0.5, -0.1) -- (0.5, 0.1));
draw((2, -0.1) -- (2, 0.1));
draw((5, -0.1) -- (5, 0.1));
draw((5.5, -0.1) -- (5.5, 0.1));
draw((7, -0.1) -- (7, 0.1));

fill((0.40, 0.28)--(0.60, 0.28)--(0.5, 0.13)--cycle,black);
fill((5.4, 0.28)--(5.6, 0.28)--(5.5, 0.13)--cycle,black);

draw( (0, 0) -- ((5000 + 60 * 100) / 10000, 0));
draw( ((5000 + 60 * 100) / 10000, 0) -- ( (5000 + 60 * 100 + 138 * 300) / 10000, 0), dotted);
draw( ((5000 + 60 * 100 + 138 * 300) / 10000, 0) -- ((55000 + 60 * 100) / 10000, 0));
draw( ((55000 + 60 * 100) / 10000, 0) -- (10, 0), dotted);

//100000 100 138 60 300
//5
//5000 20000 50000 55000 75000