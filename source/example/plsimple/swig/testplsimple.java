// This example illustrates how C++ interfaces can be used from Java.
// 
// 1. `cd' to the output directory (may be './build/java').
// 2. Type the following commands to run this program:
//       java  -cp ./plsimple.jar:. testplsimple
//

public class testplsimple {
  static {
    try {
        System.loadLibrary("plsimple");
    } catch (UnsatisfiedLinkError e) {
      System.err.println("Native code library failed to load.\n" + e);
      System.exit(1);
    }
  }

  public static void main(String argv[]) 
  {
    // ----- Object creation -----
    System.out.println( "Hello testplsimple in Java." );
    
    Simple a = new Simple("");
    System.out.println( "Created a object of Simple: " + a );
    
    Simple2 b = new Simple2(a.p());
    System.out.println( "Converted a interface: " + b );
    
    // ----- Call some methods -----
    
    if (a.valid()) {
        System.out.println( "Simple.add(1, 2) = " + a.add(1, 2) );
    } else {
        System.out.println( "Fail to created the internal object of Simple.");
    }
    
    // ----- Delete everything -----
    // Note: this invokes the virtual destructor
    // You could leave this to the garbage collector
    a.delete();
    b.delete();
    
    System.out.println( "Goodbye" );
  }
}
