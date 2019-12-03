'use strict';

const cloneObject = (a) => JSON.parse(JSON.stringify(a));

const getTime = (finish, start) => finish - start;

module.exports = { cloneObject, getTime }