#/bin/bash
java GameRank_DataGenerator 5000 0.46 > 13.generated.in
java GameRank_DataGenerator 1000 0.47 > 14.generated.in
java GameRank_DataGenerator 1000 0.48 > 15.generated.in
java GameRank_DataGenerator 2000 0.495 > 16.generated.in
java GameRank_DataGenerator 2000 0.501 > 17.generated.in
java GameRank_DataGenerator 3000 0.47 > 18.generated.in
java GameRank_DataGenerator 5000 0.49 > 19.generated.in
java GameRank_DataGenerator 10000 0.435 > 20.generated.in
java GameRank_DataGenerator 9997 0.44 > 21.generated.in
java GameRank_DataGenerator 9997 0.45 > 22.generated.in
java GameRank_DataGenerator 9999 0.443 > 23.generated.in

java -cp ../submissions/accepted GameRank_Jimmy < 13.generated.in
java -cp ../submissions/accepted GameRank_Jimmy < 14.generated.in
java -cp ../submissions/accepted GameRank_Jimmy < 15.generated.in
java -cp ../submissions/accepted GameRank_Jimmy < 16.generated.in
java -cp ../submissions/accepted GameRank_Jimmy < 17.generated.in
java -cp ../submissions/accepted GameRank_Jimmy < 18.generated.in
java -cp ../submissions/accepted GameRank_Jimmy < 19.generated.in
java -cp ../submissions/accepted GameRank_Jimmy < 20.generated.in
java -cp ../submissions/accepted GameRank_Jimmy < 21.generated.in
java -cp ../submissions/accepted GameRank_Jimmy < 22.generated.in
java -cp ../submissions/accepted GameRank_Jimmy < 23.generated.in
