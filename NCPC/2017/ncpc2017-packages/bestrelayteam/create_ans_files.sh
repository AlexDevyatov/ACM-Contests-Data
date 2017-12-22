#!/bin/bash
rm data/sample/*.ans
rm data/secret/*.ans

for x in data/sample/*.in
do
  python submissions/accepted/jimmy.py < $x > ${x/.in/.ans}
  output_validators/validator $x ${x/.in/.ans} . < ${x/.in/.ans}
done

for x in data/secret/*.in
do
  python submissions/accepted/jimmy.py < $x > ${x/.in/.ans}
  output_validators/validator $x ${x/.in/.ans} . < ${x/.in/.ans}
done
