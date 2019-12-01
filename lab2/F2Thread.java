package lab2;

import java.util.Random;

public class F2Thread implements Runnable {

  public static int count = 0; // количество созданных потоков
  String name; // имя потока
  int k;
  int h;
  Matrix MG = new Matrix(10, 10);
  Matrix MK = new Matrix(10, 10);
  Matrix ML = new Matrix(10, 10);
  Matrix MF = new Matrix(10, 10);

  public F2Thread(String name, int k, int h, Matrix MG, Matrix MK, Matrix ML) {
    this.name = name.toUpperCase();
    this.k = k;
    this.h = h;
    this.MG = MG;
    this.MK = MK;
    this.ML = ML;
  }

  public F2Thread(String name) {
    Random rand = new Random();
    this.name = name.toUpperCase();
    k = rand.nextInt(10000);
    h = rand.nextInt(10000);
    MG.fillRandomValues();
    MK.fillRandomValues();
    ML.fillRandomValues();
  }

  // MF = k*MG - h*MK*ML
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
      MF = Matrix.subtract(
        Matrix.multiplyOnValue(MG, k),
        Matrix.multiplyOnValue(
          Matrix.multiply(MK, ML),
          h
        )
      );
      // Thread.sleep(1000);
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