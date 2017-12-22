// defaultpen(1);
bbox(white, Fill);

int h = stdin, w = stdin;
int sz = max(h, w);
size(min(1505, sz * 15 + 4));

int[][] depth = new int[h][w];
int max_depth = 0;
for (int i = 0; i < h; ++i)
    for (int j = 0; j < w; ++j) {
        depth[i][j] = stdin;
        int ampl = abs(depth[i][j]);
        if (ampl > max_depth)
            max_depth = ampl;
    }

write("max depth: ", max_depth);

for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
        path one = shift(j, -i) * unitsquare;
        real frac = abs(depth[i][j]) / max_depth;
        pen fpen = (depth[i][j] < 0 ? frac * blue : frac * green) + (1 - frac) * white;
        filldraw(one, fillpen=fpen);
    }
}

int x = stdin, y = stdin;
--x; --y;
filldraw(shift(y, -x) * unitsquare, fillpen=red);

shipout(bbox(xmargin=2, white, Fill));
