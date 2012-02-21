// This example illustrates how C++ interfaces can be used from C#.

using System;
using example.plsimple;

public class testplsimple
{
    static void Main()
    {
        // ----- Object creation -----
        Console.WriteLine( "Hello testplsimple in C#." );
        
        Simple a = new Simple("");
        Console.WriteLine( "Created a object of Simple: " + a.valid() + ", " + a);
        
        Simple2 b = new Simple2(a.p());
        Console.WriteLine( "Converted a interface: " + (b.valid() ? "ok, " : " fail, ") + b);
        
        // ----- Call some methods -----
        
        if (a.valid()) {
            Console.WriteLine( "Simple.add(1, 2) = " + a.add(1, 2) );
        }
        
        Console.WriteLine( "Goodbye" );
    }
}
