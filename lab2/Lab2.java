/**
 * Lab2. JAVA threads
 * 
 * NOTES!
 * Example Project - https://github.com/howtoprogram/Kafka-MultiThread-Java-Example
 * Runnable OR Thread - https://www.journaldev.com/1016/java-thread-example
 * Thread member inside Runnable class - https://stackoverflow.com/questions/20311909/thread-member-inside-runnable-class 
 * Slow thread because of Random - https://stackoverflow.com/questions/30699631/basic-java-threading-4-threads-slower-than-non-threading
 * Joining Threads in Java - https://www.geeksforgeeks.org/joining-threads-in-java/
 * Runnable vs. Callable in Java - https://www.baeldung.com/java-runnable-callable
 * Dot and cross vector product - https://www.geeksforgeeks.org/program-dot-product-cross-product-two-vector/
 * Matrix Sorting - https://www.geeksforgeeks.org/sort-matrix-row-wise-column-wise/
 * How check proccessor cores in JAVA - https://bmwieczorek.wordpress.com/2015/11/02/java-monitoring-cpu-and-system-load-of-multi-threaded-application-via-operatingsystemmxbean/
 * Problems with CpuLoad function from jdk - https://stackoverflow.com/a/41265267
 * JAVA Map and HashMap usage - https://stackoverflow.com/questions/31591037/hashmaps-getvalue-returns-object
 */

package lab2;

import lab2.Matrix;
import java.lang.management.*;
import java.lang.reflect.*;

class Lab2 {
  private static String threadNameF1 = "thread1";
  private static String threadNameF2 = "thread2";
  private static String threadNameF3 = "thread3";
  // final static Map<String, Boolean> hasAllWorkersFinished = new HashMap<String, Boolean>();

  public static void main(String[] args) throws java.lang.Exception {
    Thread.currentThread().setName("Java MainThread");
    System.out.println(Thread.currentThread().getName() + " started...\n");
    OperatingSystemMXBean operatingSystemMXBean = ManagementFactory.getOperatingSystemMXBean();

    Matrix A = new Matrix(1200);
    Matrix C = new Matrix(1200);
    Matrix P = new Matrix(1200);
    Matrix R = new Matrix(1200);
    Matrix MA = new Matrix(1200, 1200);
    Matrix ME = new Matrix(1200, 1200);
    Matrix MD = new Matrix(1200, 1200);
    Matrix MF = new Matrix(1200, 1200);
    Matrix O = new Matrix(1200, 1200);
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
    System.out.println(Thread.currentThread().getName() + " DIRECT calculations started...");
    start = System.nanoTime();
    ME = Matrix.multiplyOnValue(
      Matrix.add(
        Matrix.multiply(MA, ME),
        MD
      ),
      Matrix.vectorDotProduct(A, Matrix.sort(C))
    );
    finish = System.nanoTime();
    System.out.println("  F1 finished with time: " + Logger.getTime(finish - start));
    
    delta = System.nanoTime();
    MF = Matrix.multiplyOnValue(
      Matrix.add(
        Matrix.multiply(MA, ME),
        MD
      ),
      Matrix.vectorDotProduct(A, Matrix.sort(C))
    );
    finish = System.nanoTime();
    System.out.println("  F2 finished with time: " + Logger.getTime(finish - delta));
    
    delta = System.nanoTime();
    O = Matrix.multiply(
      Matrix.multiply(MA, MD),
      Matrix.add(P, R)
    );
    finish = System.nanoTime();
    System.out.println("  F3 finished with time: " + Logger.getTime(finish - delta));
    finish = System.nanoTime();
    System.out.println(Thread.currentThread().getName() + " DIRECT calculations finished with time: " + Logger.getTime(finish - start));
    System.out.println();
    System.out.println();
  
    /** 
     * Multithread block
     */
     // CyclicBarrier barrier = new CyclicBarrier(workersCount + 1); // + 1 to include main thread measuring CPU load

    System.out.println(Thread.currentThread().getName() + " THREAD calculations started...");

    start = System.nanoTime();
    
    // ME = (A*SORT(C)) *(MA*ME+MD)
    Thread t1 = new Thread(new F1Thread(Lab2.threadNameF1, A, C, MA, MD, ME));
    t1.setPriority(10);

    // MF = k*MG - h*MK*ML
    Thread t2 = new Thread(new F2Thread(Lab2.threadNameF2, 6574, 2342, MA, MD, ME));
    t2.setPriority(1);

    // O = (P+R)*(MS*MT)
    Thread t3 = new Thread(new F3Thread(Lab2.threadNameF3, P, R, MA, MD));    
    t3.setPriority(5);

    t1.start();
    // t1.join();
    t2.start();
    // t2.join();
    t3.start();
    // t3.join();
    // barrier.await();

    try {
      while (
        t1.isAlive()
        || t2.isAlive()
        || t3.isAlive()
      ) {
        getAndPrintCpuLoad(operatingSystemMXBean);
        Thread.sleep(500);
      }
    } catch (InterruptedException e) {
      System.out.println(Thread.currentThread().getName() + " interrupted");
    }
    finish = System.nanoTime();
    System.out.println();
    System.out.println(Thread.currentThread().getName() + " THREAD calculations finished with time: " + Logger.getTime(finish - start));
    System.out.println();
    System.out.println(Thread.currentThread().getName() + " run is over.");
  }
 
  private static void getAndPrintCpuLoad(OperatingSystemMXBean mxBean) {
    // need to use reflection as the impl class is not visible
    String str = "";
    System.out.println(str);
    for (Method method: mxBean.getClass().getDeclaredMethods()) {
      method.setAccessible(true);
      String methodName = method.getName();
      if (
        methodName.startsWith("get")
        && methodName.contains("Cpu")
        && methodName.contains("Load")
        && Modifier.isPublic(method.getModifiers())
      ) {
        Object value;
        try {
          value = method.invoke(mxBean);
        } catch (Exception e) {
          value = e;
        }
        System.out.println("  " + methodName + " = " + value);
      }
    }
    System.out.println(str);
  }

  /**
   * One more way to start Thread with Runnable class inside
   */
  private static void createAndStartTestWorker(
    String threadName
    // CyclicBarrier cyclicBarrier //use barrier to start all workers at the same time as main thread
  ) {
    new Thread(() -> {
      Thread.currentThread().setName(threadName);
      String thName = Thread.currentThread().getName();
      try {
        // cyclicBarrier.await();
        long counter = (Thread.currentThread().getId() % 10) * 3;
        System.out.println(counter + " <- current counter");
        for (long i = 0L; i < 19999999999L * counter; i++) { // 6s
          // Thread 100% time as RUNNABLE, taking 1/(n cores) of JVM/System overall CPU
        }
        System.out.println(thName + " finished");
      } catch (Exception e) {
        e.printStackTrace();
      }
    }).start();
  }
 
}
