var line = readline();
var ans = 0;
for (i = 0; i < line.length; i+=3) {
    for (j = 0; j < 3; j++) {
        if ("PER"[j]!=line[i+j]) ans++;
    }
}
print(ans);
