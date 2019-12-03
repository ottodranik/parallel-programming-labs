/**
 * Взаимодействие между process - tcp, udp, ipc и прочие месседжы
 * Из треда в тред можно слать просто ивенты
 * Про тред vs процесс - https://youtu.be/CUU49jjHloM?t=1214
 * МежПроцессовое взаимодействие - https://www.youtube.com/watch?v=2OXWZFMvfbc
 * Про треды и общение между ними - https://www.youtube.com/watch?v=zLm8pnbxSII
 * Про возможность совместного использования - https://youtu.be/CUU49jjHloM?t=2904
 */

'use strict';

const Matrix = require('./Matrix.js');
const helpers = require('./helpers.js');
const threads = require('worker_threads');
const os = require('os');
const { Worker } = threads;
// const cp = require('child_process')

const cpuCount = os.cpus().length;

console.log(cpuCount);

const A = new Matrix(1200);
const C = new Matrix(1200);
const P = new Matrix(1200);
const R = new Matrix(1200);
const MA = new Matrix(1200, 1200);
const ME = new Matrix(1200, 1200);
const MD = new Matrix(1200, 1200);
let res1, res2, res3;
A.fillRandomValues();
C.fillRandomValues();
P.fillRandomValues();
R.fillRandomValues();
MA.fillRandomValues();
ME.fillRandomValues();
MD.fillRandomValues();

let start = 0, finish = 0, delta = 0;

/** 
 * No threads block
 */
console.log(threads.threadId + " DIRECT calculations started...");
start = Date.now();
res1 = Matrix.multiplyOnValue(
  Matrix.add(
    Matrix.multiply(MA, ME),
    MD
  ),
  Matrix.vectorDotProduct(A, Matrix.sort(C))
);
finish = Date.now();
console.log("  F1 finished with time: " + helpers.getTime(finish, start));

delta = Date.now();
res2 = Matrix.subtract(
  Matrix.multiplyOnValue(MA, 6574),
  Matrix.multiplyOnValue(
    Matrix.multiply(MD, ME),
    2342
  )
);
finish = Date.now();
console.log("  F2 finished with time: " + helpers.getTime(finish, delta));

delta = Date.now();
res3 = Matrix.multiply(
  Matrix.multiply(MA, MD),
  Matrix.add(P, R)
);
finish = Date.now();
console.log("  F3 finished with time: " + helpers.getTime(finish, delta));
finish = Date.now();
console.log(threads.threadId + " DIRECT calculations finished with time: " + helpers.getTime(finish, start));
console.log();
console.log();

/** 
 * Multithread block
 */
// CyclicBarrier barrier = new CyclicBarrier(workersCount + 1); // + 1 to include main thread measuring CPU load

console.log(threads.name + " THREAD calculations started...");

start = Date.now();

// ME = (A*SORT(C)) *(MA*ME+MD)
const t1 = new Worker("./f1Thread.js", { workerData: { A, C, MA, MD, ME } })
const t2 = new Worker("./f2Thread.js", { workerData: { k: 6574, h: 2342, MA, MD, ME } })
const t3= new Worker("./f3Thread.js", { workerData: { P, R, MA, MD } })
// t1.setPriority(10);

finish = Date.now();
console.log();
console.log(threads.threadId + " THREAD calculations finished with time: " + helpers.getTime(finish, start));
console.log();
console.log(threads.threadId + " run is over.");
