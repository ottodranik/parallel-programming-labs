using System;
using System.Threading;

namespace Lab3App {
  public class F2 {

    public static int count = 0; // количество созданных потоков
    String name; // имя потока
    int k;
    int h;
    Matrix MG = new Matrix(1000, 1000);
    Matrix MK = new Matrix(1000, 1000);
    Matrix ML = new Matrix(1000, 1000);
    // Matrix MF = new Matrix(1000, 1000);

    public F2(String name, int k, int h, Matrix MG, Matrix MK, Matrix ML) {
      this.name = name.ToUpper();
      this.k = k;
      this.h = h;
      this.MG = MG;
      this.MK = MK;
      this.ML = ML;
    }

    public F2(String name) {
      Random rand = new Random();
      this.name = name.ToUpper();
      k = rand.Next(10000);
      h = rand.Next(10000);
      MG.fillRandomValues();
      MK.fillRandomValues();
      ML.fillRandomValues();
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
        Matrix.subtract(
          Matrix.multiplyOnValue(MG, k),
          Matrix.multiplyOnValue(
            Matrix.multiply(MK, ML),
            h
          )
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