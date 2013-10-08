use strict;
use warnings;

sub sum_of_multiples {
    my ($bound) = @_;
    my $sum = 0;
    for (my $i = 1; $i < $bound; $i++) {
        if ($i % 3 == 0 or $i % 5 == 0) {
            $sum += $i;
        }
    }
    print $sum . "\n";
}

&sum_of_multiples(10);
&sum_of_multiples(1000);
