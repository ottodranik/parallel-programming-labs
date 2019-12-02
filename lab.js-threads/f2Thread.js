'use strict';

const threads = require('worker_threads');
// const { Worker } = threads;

if (threads.isMainThread) {
  // const worker = new Worker(__filename);
  for (let i = 0; i < 12199999999; i++) {

  }
  console.log("finished F2.1: " + process.pid);
} else {
  for (let i = 0; i < 12199999999; i++) {

  }
  console.log("finished F2.2: " + process.pid);
}
