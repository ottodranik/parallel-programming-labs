'use strict';

const Matrix = require('./Matrix.js');
const helpers = require('./helpers.js');
const threads = require('worker_threads');

let { A, C, MA, MD, ME } = threads.workerData;
// console.log(MA);
let start = 0, finish = 0;

MA = new Matrix(MA);
MD = new Matrix(MD);
ME = new Matrix(ME);
A = new Matrix(A);
C = new Matrix(C);
// Thread.currentThread().setName(this.name);
console.log("  Thread " + threads.threadId + " named '" + threads.name + "' is running...");
console.log();
// try {
  // Displaying the thread that is running
  start = Date.now();
  const res1 = Matrix.multiplyOnValue(
    Matrix.add(
      Matrix.multiply(MA, ME),
      MD
    ),
    Matrix.vectorDotProduct(A, Matrix.sort(C))
  );
  // ME.displayMatrix();
  finish = Date.now();
  console.log(finish, start);
// } catch (e) {
  // Throwing an exception
//   console.log("  Exception is caught");
// }
console.log();
console.log(
  "  Thread " + threads.threadId + " is over with time: " + helpers.getTime(finish, start)
);
console.log();
// process.exit(0);
