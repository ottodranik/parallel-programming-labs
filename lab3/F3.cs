using System;
using System.Threading;

namespace Lab3App {
  public class F3 {

    public static int count = 0; // количество созданных потоков
    String name; // имя потока
    Matrix P = new Matrix(1000);
    Matrix R = new Matrix(1000);
    Matrix MS = new Matrix(1000, 1000);
    Matrix MT = new Matrix(1000, 1000);
    Matrix O = new Matrix(1000, 1000);

    public F3(String name, Matrix P, Matrix R, Matrix MS, Matrix MT) {
      this.name = name.ToUpper();
      this.R = R;
      this.P = P;
      this.MS = MS;
      this.MT = MT;
    }

    public F3(String name) {
      this.name = name.ToUpper();
      P.fillRandomValues();
      R.fillRandomValues();
      MS.fillRandomValues();
      MT.fillRandomValues();
      O.fillRandomValues();
    }

    // MF = k*MG - h*MK*ML
    public void run() {
      Thread.CurrentThread.Name = this.name;
      long start = 0, finish = 0;
      Console.WriteLine();
      Console.WriteLine("  Thread " + Thread.CurrentThread.ManagedThreadId + " named '" + Thread.CurrentThread.Name + "' is running...");
      Console.WriteLine();
      try {
        // Displaying the thread that is running
        start = Logger.nanoTime();
        // Thread.Sleep(1000);
        O = Matrix.multiply(
          Matrix.multiply(MS, MT),
          Matrix.add(P, R)
        );
        // Thread.Sleep(1000);
        // ME.displayMatrix();
        finish = Logger.nanoTime();
      } catch (Exception e) {
        // Throwing an exception
        Console.WriteLine("  Exception is caught: " + e.Message);
      }
      Console.WriteLine();
      Console.WriteLine(
        "  Thread " + Thread.CurrentThread.Name + " is over with time: " + Logger.getTime(finish - start)
      );
      Console.WriteLine();
    }
  }
}