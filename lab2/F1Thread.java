package lab2;

public class F1Thread implements Runnable {

  public static int count = 0; // количество созданных потоков
  String name; // имя потока
  Matrix A = new Matrix(3);
  Matrix C = new Matrix(3);
  Matrix MA = new Matrix(10, 10);
  Matrix ME = new Matrix(10, 10);
  Matrix MD = new Matrix(10, 10);

  public F1Thread(String name, Matrix A, Matrix C, Matrix MA, Matrix MD, Matrix ME) {
    this.name = name.toUpperCase();
    this.A = A;
    this.C = C;
    this.MA = MA;
    this.MD = MD;
    this.ME = ME;
  }

  public F1Thread(String name) {
    this.name = name.toUpperCase();
    A.fillRandomValues();
    C.fillRandomValues();
    MA.fillRandomValues();
    ME.fillRandomValues();
    MD.fillRandomValues();
  }

  // ME = (A*SORT(C)) *(MA*ME+MD)
  @Override
  public void run() {
    long start = 0, finish = 0;
    Thread.currentThread().setName(this.name);
    System.out.println();
    System.out.println("  Thread " + Thread.currentThread().getId() + " named '" + Thread.currentThread().getName() + "' is running...");
    System.out.println();
    try {
      // Displaying the thread that is running
      start = System.nanoTime();
      // Thread.sleep(1000);
      ME = Matrix.multiplyOnValue(
        Matrix.add(
          Matrix.multiply(MA, ME),
          MD
        ),
        Matrix.vectorDotProduct(A, Matrix.sort(C))
      );
      // Thread.sleep(1000);
      // ME.displayMatrix();
      finish = System.nanoTime();
    } catch (Exception e) {
      // Throwing an exception
      System.out.println("  Exception is caught");
    }
    System.out.println();
    System.out.println(
      "  Thread " + Thread.currentThread().getName() + " is over with time: " + Logger.getTime(finish - start)
    );
    System.out.println();
  }
}