'use strict';

const Matrix = require('./Matrix.js');
const helpers = require('./helpers.js');
const threads = require('worker_threads');

let { P, R, MA, MD } = threads.workerData;
let start = 0, finish = 0;
MA = new Matrix(MA.mainMatrix);
MD = new Matrix(MD.mainMatrix);
P = new Matrix(P.mainMatrix);
R = new Matrix(R.mainMatrix);
// Thread.currentThread().setName(this.name);
console.log("  Thread " + threads.threadId + " named '" + threads.name + "' is running...");
console.log();
try {
  // Displaying the thread that is running
  start = Date.now();
  const res3 = Matrix.multiply(
    Matrix.multiply(MA, MD),
    Matrix.add(P, R)
  );
  // ME.displayMatrix();
  finish = Date.now();
} catch (e) {
  // Throwing an exception
  console.log("  Exception is caught");
}
console.log();
console.log(
  "  Thread " + threads.threadId + " is over with time: " + helpers.getTime(finish, start)
);
console.log();
// process.exit(0);
