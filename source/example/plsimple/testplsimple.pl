# This example illustrates how C++ interfaces can be used from Perl.

use plsimple;

print "Hello testplsimple in Perl.\n";

$a = new plsimple::Simple("");
print "Created a object of Simple: $a\n";

$b = new plsimple::Simple2($a->p());
print "Converted a interface: $b\n";

print "Simple.add(1, 2) = ", $a->add(1, 2), "\n";
