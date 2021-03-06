#!/usr/local/bin/babel-node

import readline from 'readline';
import fs from 'fs';
import problems from './problems.json';
const exec = require('child_process').exec;

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
  terminal: false
});

let state = 'not started', lastTime, times, pausedState, problem;

const formatMinutes = (millis) => {
  return parseFloat(Math.round(millis / 10 / 60) / 100).toFixed(2) + ' min';
};

const log = () => {
  const total = times.understanding + times.solving + times.coding;
  console.log(`
    Understanding:  ${formatMinutes(times.understanding)}
    Solving:        ${formatMinutes(times.solving)}
    Coding:         ${formatMinutes(times.coding)}
    TOTAL:          ${formatMinutes(total)}
  `);

  const date = new Date();
  const formattedDate = `${date.getMonth()+1}-${date.getDate()}-${date.getFullYear()}`;
  problem = problem || { url: '', difficulty: '' };
  fs.appendFile('logs.csv', `${formattedDate},${problem.url},${problem.difficulty},${times.understanding},${times.solving},${times.coding},${total}\n`, (err) => {
    if (err) {
      console.log('There was an error writing to the logs. Try logging manually.');
      console.error(err);
    }
  });
};

const setState = (nextState) => {
  if (state == 'not started') {
    console.log('Not started.');
  } else if (state == 'paused') {
    console.log('Resume before changing state.');
  } else {
    times[state] += Date.now() - lastTime;
    lastTime = Date.now();
    state = nextState;
    console.log('SWITCHED TO ' + nextState);
  }
};

const start = () => {
  times = {
    'understanding': 0,
    'solving': 0,
    'coding': 0
  };
  state = 'understanding';
  lastTime = Date.now();
  console.log('STARTING');
  console.log('SWITCHED TO ' + state);
};

const stop = () => {
  if (state == 'not started') {
    return console.log('Not started.');
  }

  if (state == 'paused')
    state = pausedState;
  else
    times[state] += Date.now() - lastTime;

  state = 'not started';
  console.log('STOPPED');
  log();
};

const pause = () => {
  if (state == 'paused') {
    console.log('Already paused.')
  } else if (state == 'not started') {
    console.log('Not started.');
  } else {
    pausedState = state;
    times[state] += Date.now() - lastTime;
    state = 'paused';
    console.log('PAUSED');
  }
};

const resume = () => {
  if (state == 'paused') {
    state = pausedState;
    lastTime = Date.now();
    console.log('RESUMED ' + state);
  } else {
    console.log('Not paused.');
  }
};

let assigning = false;
const assignProblem = (input) => {
  if (!input) {
    console.log('Select problem level: (1-10)');
    assigning = true;
  } else {
    try {
      const level = parseInt(input);
      if (level < 1 || level > 10) {
        console.log('Invalid problem level');
      } else {
        const levelProblems = problems.filter((problem) => (problem.difficulty > (level - 1)/10 && problem.difficulty <= level/10) || (problem.difficulty == 0 && level == 1));
        const index = Math.floor(Math.random() * (levelProblems.length));
        problem = levelProblems[index];
        exec(`open ${problem.url}`, (err) => {
          if (err) {
            console.log(problem.url);
          }
        });
      }
    } catch (e) {
      console.log('Invalid problem level');
    }
    assigning = false;
  }
};

const commands = () => {
  console.log(`
    Commands:
    s - start or switch to solving if already started.
    e - end
    p - pause or get problem if not started.
    r - resume
    u - switch to understanding
    c - switch to coding
  `);
};

rl.on('line', (line) => {
  if (assigning) {
    return assignProblem(line);
  }

  switch(line[0]) {
    case 's':
      if (state == 'not started') {
        start();
      } else {
        setState('solving');
      }
    break;
    case 'p': 
      if (state == 'not started') {
        assignProblem();
      } else {
        pause();
      }
    break;
    case 'e': stop(); break;
    case 'r': resume(); break;
    case 'u': setState('understanding'); break;
    case 'c': setState('coding'); break;
    default: console.log('Command not recognized.'); commands(); break;
  }
});

commands();
