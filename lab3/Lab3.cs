/**
 * Lab3. C# threads
 * 
 * NOTES!
 * Array Initialization - https://docs.microsoft.com/en-us/dotnet/csharp/programming-guide/arrays/multidimensional-arrays
 * ThreadStart Delegate - https://docs.microsoft.com/en-us/dotnet/api/system.threading.threadstart?view=netframework-4.8
 * !!Thread Class!! - https://docs.microsoft.com/en-us/dotnet/api/system.threading.thread?view=netframework-4.8
 * Move from Java to C# - https://medium.com/better-programming/java-to-c-c-to-java-f766c9f659c4
 * C# CPU usage - https://medium.com/@jackwild/getting-cpu-usage-in-net-core-7ef825831b8b
 */

using System;
using System.Threading;
using System.Diagnostics;

namespace Lab3App {
  public class Lab3 {
    private static String threadNameF1 = "thread1";
    private static String threadNameF2 = "thread2";
    private static String threadNameF3 = "thread3";
    
    public static void Main() {
      Thread.CurrentThread.Name = "C# MainThread";
      Console.WriteLine(Thread.CurrentThread.Name + " started...\n");
      var currentProcessName = Process.GetCurrentProcess().ProcessName;
      PerformanceCounter cpuCounter = new PerformanceCounter("Processor", "% Processor Time", currentProcessName);

      Matrix A = new Matrix(1000);
      Matrix C = new Matrix(1000);
      Matrix P = new Matrix(1000);
      Matrix R = new Matrix(1000);
      Matrix MA = new Matrix(1000, 1000);
      Matrix ME = new Matrix(1000, 1000);
      Matrix MD = new Matrix(1000, 1000);
      // Matrix MF = new Matrix(1000, 1000);
      // Matrix O = new Matrix(1000, 1000);
      A.fillRandomValues();
      C.fillRandomValues();
      P.fillRandomValues();
      R.fillRandomValues();
      MA.fillRandomValues();
      ME.fillRandomValues();
      MD.fillRandomValues();

      long start = 0, finish = 0, delta = 0;

      /** 
       * No threads block
       */
      Console.WriteLine(Thread.CurrentThread.Name + " DIRECT calculations started...");
      start = Logger.nanoTime();
      Matrix.multiplyOnValue(
        Matrix.add(
          Matrix.multiply(MA, ME),
          MD
        ),
        Matrix.vectorDotProduct(A, Matrix.sort(C))
      );
      finish = Logger.nanoTime();
      Console.WriteLine("  F1 finished with time: " + Logger.getTime(finish - start));
      
      delta = Logger.nanoTime();
      MF = Matrix.subtract(
        Matrix.multiplyOnValue(MA, 6574),
        Matrix.multiplyOnValue(
          Matrix.multiply(MD, ME),
          2342
        )
      );
      finish = Logger.nanoTime();
      Console.WriteLine("  F2 finished with time: " + Logger.getTime(finish - delta));

      delta = Logger.nanoTime();
      Matrix.multiply(
        Matrix.multiply(MA, MD),
        Matrix.add(P, R)
      );
      finish = Logger.nanoTime();
      Console.WriteLine("  F3 finished with time: " + Logger.getTime(finish - delta));
      finish = Logger.nanoTime();
      Console.WriteLine("Main thread DIRECT calculations finished with time: " + Logger.getTime(finish - start));
      Console.WriteLine();
      Console.WriteLine();

      /** 
       * Multithread block
       * The constructor for the Thread class requires a ThreadStart 
       * delegate that represents the method to be executed on the thread.
       */
      Console.WriteLine("Main thread THREAD calculations started...");

      start = Logger.nanoTime();
      
      // ME = (A*SORT(C)) *(MA*ME+MD)
      F1 f1 = new F1(Lab3.threadNameF1, A, C, MA, MD, ME);
      ThreadStart threadF1Delegate = new ThreadStart(f1.run);
      Thread t1 = new Thread(threadF1Delegate);
      t1.Priority = ThreadPriority.Lowest;

      // MF = k*MG - h*MK*ML
      F2 f2 = new F2(Lab3.threadNameF2, 6574, 2342, MA, MD, ME);
      ThreadStart threadF2Delegate = new ThreadStart(f2.run);
      Thread t2 = new Thread(threadF2Delegate);
      t2.Priority = ThreadPriority.Normal;

      // O = (P+R)*(MS*MT)
      F3 f3 = new F3(Lab3.threadNameF3, P, R, MA, MD);
      ThreadStart threadF3Delegate = new ThreadStart(f3.run);
      Thread t3 = new Thread(threadF3Delegate);
      t3.Priority = ThreadPriority.Highest;

      t1.Start();
      // t1.Join();
      t2.Start();
      // t2.Join();
      t3.Start();
      // t3.Join();

      // Note that on a uniprocessor, the new thread does not get any processor
      // time until the main thread is preempted or yields. 
      // Uncomment the Thread.Sleep that follows t.Start() to see the difference.
      // Thread.Sleep(0);

      try {
        while (
          t1.IsAlive
          || t2.IsAlive
          || t3.IsAlive
        ) {
          // Console.WriteLine("Main thread will be alive till the child threads is live...");
          getAndPrintCpuLoad(cpuCounter);
          Thread.Sleep(1000);
        }
      } catch (ThreadInterruptedException e) {
        Console.WriteLine("Main thread interrupted: " + e.Message);
      }
      finish = Logger.nanoTime();
      Console.WriteLine();
      Console.WriteLine(Thread.CurrentThread.Name + " THREAD calculations finished with time: " + Logger.getTime(finish - start));
      Console.WriteLine();
      Console.WriteLine(Thread.CurrentThread.Name + " run is over.");
    }

    private static void getAndPrintCpuLoad(PerformanceCounter cpuCounter) {
      Console.WriteLine("  | CPU load: " + cpuCounter.NextValue() + "%");
    }
  }
}