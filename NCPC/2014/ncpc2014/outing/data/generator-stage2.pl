#!/usr/bin/env perl

#
# Reads from STDIN a list of "cycle tail" tuples, converts
# them to an actual graph representation and then shuffles
# the final list for output so that solutions can't infer
# things from their order
#

use strict;
use warnings;

print scalar <>;

my @xes = ();

while (<>) {
  my ($cycle, $stem) = map {int} split / /;
  next if $cycle < 1 or $stem < 0;
  my $index = scalar @xes;

  for my $i (0 .. $cycle-1) {
    push @xes, $index + (($i + 1) % $cycle);
  }

  for my $i (0 .. $stem-1) {
    push @xes, $index + int(rand($i + $cycle));
  }

  $index += $cycle + $stem;
}

my @res = @xes;
my @perm = 0 .. @res-1;
for my $i (reverse (1 .. @res-1)) {
    my $j = int(rand $i);
    ($perm[$i], $perm[$j]) = ($perm[$j], $perm[$i]);
}
for my $i (0 .. @res-1) {
    $res[$perm[$i]] = 1 + $perm[$xes[$i]];
}
print "@res\n";
