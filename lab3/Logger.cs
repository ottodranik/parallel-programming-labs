using System;
using System.Diagnostics;

namespace Lab3App {
  public class Logger {

    /**
     * https://stackoverflow.com/a/14728867
     */
    public static long nanoTime() {
      long nano = 10000L * Stopwatch.GetTimestamp();
      nano /= TimeSpan.TicksPerMillisecond;
      nano *= 100L;
      return nano;
    }

    public static long getTime(long nanoValue) {
      return nanoValue/1000000;
    }
  }
}