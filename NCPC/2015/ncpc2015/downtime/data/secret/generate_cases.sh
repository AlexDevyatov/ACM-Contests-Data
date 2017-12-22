# standard uniform
echo "1 0 5 20" | python generate.py > 1.in
echo "2 0 10 100" | python generate.py > 2.in
echo "3 0 15 20" | python generate.py > 3.in
echo "4 0 100000 1000" | python generate.py > 4.in
echo "5 0 100000 3" | python generate.py > 5.in
echo "6 0 100000 25" | python generate.py > 6.in
echo "7 0 100000 100000" | python generate.py > 7.in

# even distribution
echo "8 3 12345 100" | python generate.py > 8.in
echo "9 3 23456 49" | python generate.py > 9.in
echo "10 3 99997 777" | python generate.py > 10.in

# edge left
echo "11 1 25000 200" | python generate.py > 11.in
echo "12 1 50000 100" | python generate.py > 12.in

# edge right
echo "13 2 25000 200" | python generate.py > 13.in
echo "14 2 50000 100" | python generate.py > 14.in

# some random stuff
echo "15 0 1000 10" | python generate.py > 15.in
echo "16 0 2999 17" | python generate.py > 16.in
echo "17 0 3998 119" | python generate.py > 17.in
echo "18 0 4997 523" | python generate.py > 18.in
echo "19 3 1996 10" | python generate.py > 19.in
echo "20 3 2995 13" | python generate.py > 20.in
echo "21 3 3994 19" | python generate.py > 21.in
echo "22 3 4993 123" | python generate.py > 22.in

echo "1 1
0" > 23.in

echo "1 1
100000" > 24.in

SOLVER=osk
for i in `seq 1 24`; do ./$SOLVER < $i.in > $i.ans; done
