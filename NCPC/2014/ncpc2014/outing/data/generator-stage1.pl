#!/usr/bin/env perl

#
# Simple random test case generator.
#
# Usage:
#   ./generator-stage1.pl | ./generator-stage2.pl > testcase.in
#   ../submissions/accepted/hex539-dp-compressed < testcase.in > testcase.ans
#

use strict;
use warnings;

my $n = int(rand(501)) + 500;
my $m = int(rand($n)) + 1;

sub min {my $x = shift; return $x unless @_; my $y = min(@_); return $x <= $y? $x: $y;}
sub max {my $x = shift; return $x unless @_; my $y = min(@_); return $x >= $y? $x: $y;}

while ($n > 0) {
  my $cycle = max(
    1 + int(rand(min($n, 100))),
    1 + int(rand(min($n, 100))),
  );
  my $stem = min(
    int(rand($n - $cycle + 1)),
    int(rand($n - $cycle + 1)),
    4
  );

  print "$cycle $stem\n";
  $n -= $cycle + $stem;
}
