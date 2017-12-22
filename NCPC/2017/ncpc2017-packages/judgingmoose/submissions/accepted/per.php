<?php

fscanf(STDIN, "%d%d", $l, $r);
$val = 2 * max($l, $r);
if ($val == 0)
   echo "Not a moose";
elseif ($l == $r)
   echo "Even $val";
else
   echo "Odd $val";
