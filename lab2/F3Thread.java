package lab2;

public class F3Thread implements Runnable {

  public static int count = 0; // количество созданных потоков
  String name; // имя потока
  Matrix P = new Matrix(1000);
  Matrix R = new Matrix(1000);
  Matrix MS = new Matrix(1000, 1000);
  Matrix MT = new Matrix(1000, 1000);
  Matrix O = new Matrix(1000, 1000);

  public F3Thread(String name, Matrix P, Matrix R, Matrix MS, Matrix MT) {
    this.name = name.toUpperCase();
    this.R = R;
    this.P = P;
    this.MS = MS;
    this.MT = MT;
  }

  public F3Thread(String name) {
    this.name = name.toUpperCase();
    P.fillRandomValues();
    R.fillRandomValues();
    MS.fillRandomValues();
    MT.fillRandomValues();
    O.fillRandomValues();
  }

  // O = (P+R)*(MS*MT)
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
      O = Matrix.multiply(
        Matrix.multiply(MS, MT),
        Matrix.add(P, R)
      );
      // MF.displayMatrix();
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