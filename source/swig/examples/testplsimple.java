// This example illustrates how C++ interfaces can be used from Java.

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
    
    Simple a = new Simple("");
    System.out.println( "Created a object of Simple: " + a );
    
    Simple2 b = new Simple2(a.p());
    System.out.println( "Converted a interface: " + b );
    
    // ----- Call some methods -----
    
    System.out.println( "Simple.add(1, 2) = " + a.add(1, 2) );
    
    // ----- Delete everything -----
    // Note: this invokes the virtual destructor
    // You could leave this to the garbage collector
    a.delete();
    b.delete();
    
    System.out.println( "Goodbye" );
  }
}
