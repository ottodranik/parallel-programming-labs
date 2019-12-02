'use strict';

const Matrix = require('./Matrix.js');
const helpers = require('./helpers.js');
const threads = require('worker_threads');
const os = require('os');
const { Worker } = threads;
// const cp = require('child_process')

const cpuCount = os.cpus().length;

console.log(cpuCount);

const A = new Matrix(10);
const C = new Matrix(10);
const P = new Matrix(10);
const R = new Matrix(10);
const MA = new Matrix(10, 10);
const ME = new Matrix(10, 10);
const MD = new Matrix(10, 10);
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
res2 = Matrix.multiplyOnValue(
  Matrix.add(
    Matrix.multiply(MA, ME),
    MD
  ),
  Matrix.vectorDotProduct(A, Matrix.sort(C))
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
// t1.setPriority(10);

finish = Date.now();
console.log();
console.log(threads.threadId + " THREAD calculations finished with time: " + helpers.getTime(finish, start));
console.log();
console.log(threads.threadId + " run is over.");

/**
 * Взаимодействие между process - tcp, udp, ipc и прочие месседжы
 * Из треда в тред можно слать просто ивенты
 * Про тред vs процесс - https://youtu.be/CUU49jjHloM?t=1214
 * МежПроцессовое взаимодействие - https://www.youtube.com/watch?v=2OXWZFMvfbc
 * Про треды и общение между ними - https://www.youtube.com/watch?v=zLm8pnbxSII
 * Про возможность совместного использования - https://youtu.be/CUU49jjHloM?t=2904
 */

// const worker1 = cp.fork('./f1Thread.js');
// const worker2 = cp.fork('./f2Thread.js');
// const worker3 = cp.fork('./f3Thread.js');
// const worker4 = cp.fork('./f3Thread.js');
// console.log('Started worker:', worker1.pid);
// console.log('Started worker:', worker2.pid);
// console.log('Started worker:', worker3.pid);
// console.log('Started worker:', worker4.pid);
// workers.push(worker1);
// workers.push(worker2);
// workers.push(worker3);

// const threads = require('worker_threads');
// const { Worker } = threads;

// if (threads.isMainThread) {
//   console.dir({ master: threads });
//   const workerData = { text: 'Data from Master to Worker' };
//   const worker = new Worker("./f1Thread.js");
//   const worker2 = new Worker("./f2Thread.js");
//   const worker3 = new Worker("./f3Thread.js");
//   // worker.on('message', (...args) => {
//   //   console.log({ args });
//   // });
//   // worker.on('error', err => {
//   //   console.log(err.stack);
//   // });
//   // worker.on('exit', code => {
//   //   console.dir({ code });
//   // });
//   // console.dir(getInheritance(worker));
//   // console.dir(getInheritance(worker2));
// } else {
//   console.dir({ worker: threads });
//   // threads.parentPort.postMessage('Hello there!');
//   // setTimeout(() => {
//   //   const data = { text: 'Message from Worker to Master' };
//   //   threads.parentPort.postMessage(data);
//   // }, 1000);
// }