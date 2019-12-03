'use strict';

const Matrix = require('./Matrix.js');
const helpers = require('./helpers.js');
const threads = require('worker_threads');

let { k, h, MA, MD, ME } = threads.workerData;
let start = 0, finish = 0;
MA = new Matrix(MA.mainMatrix);
MD = new Matrix(MD.mainMatrix);
ME = new Matrix(ME.mainMatrix);
// Thread.currentThread().setName(this.name);
console.log("  Thread " + threads.threadId + " named '" + threads.name + "' is running...");
console.log();
try {
  // Displaying the thread that is running
  start = Date.now();
  const res2 = Matrix.subtract(
    Matrix.multiplyOnValue(MA, k),
    Matrix.multiplyOnValue(
      Matrix.multiply(MD, ME),
      h
    )
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
