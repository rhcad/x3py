// This example illustrates how C++ interfaces can be used from Java.
// 
// 1. `cd' to the output directory (may be './build/java').
// 2. Type the following commands to run this program:
//       java  -cp ./plswigsimp.jar:. testplswigsimp
//

public class testplswigsimp {
  static {
    try {
        System.loadLibrary("plswigsimp");
    } catch (UnsatisfiedLinkError e) {
      System.err.println("Native code library failed to load.\n" + e);
      System.exit(1);
    }
  }

  public static void main(String argv[]) 
  {
    // ----- Object creation -----
    System.out.println( "Hello testplswigsimp in Java." );
    
    Simple a = new Simple("");
    System.out.println( "Created a object of Simple: " + a );
    
    Simple2 b = new Simple2(a.p());
    System.out.println( "Converted a interface: " + b );
    
    Simple3 c = new Simple3(a.p());
    System.out.println( "Converted a interface: " + c );
    
    // ----- Call some methods -----
    
    System.out.println( "Simple.add(1, 2) = " + a.add(1, 2) );
    
    // ----- Delete everything -----
    // Note: this invokes the virtual destructor
    // You could leave this to the garbage collector
    a.delete();
    b.delete();
    c.delete();
    
    System.out.println( "Goodbye" );
  }
}
