using System;
using System.Threading;

namespace Lab3App {
  public class F1 {

    public static int count = 0; // количество созданных потоков
    String name; // имя потока
    Matrix A = new Matrix(1000);
    Matrix C = new Matrix(1000);
    Matrix MA = new Matrix(1000, 1000);
    Matrix ME = new Matrix(1000, 1000);
    Matrix MD = new Matrix(1000, 1000);

    public F1(String name, Matrix A, Matrix C, Matrix MA, Matrix MD, Matrix ME) {
      this.name = name.ToUpper();
      this.A = A;
      this.C = C;
      this.MA = MA;
      this.MD = MD;
      this.ME = ME;
    }

    public F1(String name) {
      this.name = name.ToUpper();
      A.fillRandomValues();
      C.fillRandomValues();
      MA.fillRandomValues();
      ME.fillRandomValues();
      MD.fillRandomValues();
    }

    // ME = (A*SORT(C)) *(MA*ME+MD)
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
        ME = Matrix.multiplyOnValue(
          Matrix.add(
            Matrix.multiply(MA, ME),
            MD
          ),
          Matrix.vectorDotProduct(A, C)
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