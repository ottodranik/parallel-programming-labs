'use strict';

const cloneObject = (a) => JSON.parse(JSON.stringify(a));

const getTime = (finish, start) => {
  console.log(finish, start);
  return finish - start;
}

module.exports = { cloneObject, getTime }