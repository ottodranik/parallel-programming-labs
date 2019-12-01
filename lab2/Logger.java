package lab2;

class Logger {

  /**
   * NanoTime
   * https://stackoverflow.com/questions/180158/how-do-i-time-a-methods-execution-in-java
   */
  public static long getTime(long nanoValue) {
    return nanoValue/1000000;
  }
}
