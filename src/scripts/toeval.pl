#!/usr/bin/env perl

use strict;

my %ans;

open(M, "$ARGV[0]");
open(T, "zcat $ARGV[1] |");

while(<M>){
    chomp;
    my ($w, $c) = split;
    $ans{$w} = $c;    
}

while(<T>){
    chomp;
    my @l = split;
    next if !$_;
    die("missing type:$l[0]\n") unless defined $ans{$l[0]};
    print "$ans{$l[0]}\n"
}
