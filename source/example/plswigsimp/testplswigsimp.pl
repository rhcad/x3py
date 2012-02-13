# This example illustrates how C++ interfaces can be used from Perl.

use plswigsimp;

print "Hello testplswigsimp in Perl.\n";

$a = new plswigsimp::Simple("");
print "Created a object of Simple: $a\n";

$b = new plswigsimp::Simple2($a->p());
print "Converted a interface: $b\n";

print "Simple.add(1, 2) = ", $a->add(1, 2), "\n";
