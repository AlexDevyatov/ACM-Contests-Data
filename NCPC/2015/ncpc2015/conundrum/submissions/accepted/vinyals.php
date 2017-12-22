<?php

$per = array(0 => "P", 1 => "E", 2 => "R");

$line = fgets(STDIN);
$ans = 0;
foreach (str_split($line,3) as $triple) {
  $chars = str_split($triple);
  if (count($chars)<3) break;
  for ($i=0;$i<3;$i++) {
    if ($per[$i]!=$chars[$i]) $ans++;
  }
}
echo $ans . "\n";
