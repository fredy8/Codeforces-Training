import fs from 'fs';
import path from 'path';
import { spawn } from 'child_process';
import cheerio from 'cheerio';
import get from './get';

const args = process.argv.slice(2);
const contestId = args[0];
const problemId = args[1];
const binFile = path.join(process.cwd(), args[2] || './problem');

if (!contestId || isNaN(contestId)) {
  console.error('Invalid contest id.');
  process.exit(1);
}

if (['A', 'B', 'C', 'D', 'E'].indexOf(problemId) == -1) {
  console.error('Invalid problem id.');
  process.exit(1);
}

let cache = {};
const cacheFile = path.join(__dirname, '.tests_cache');

const saveCache = () => {
  fs.writeFile(cacheFile, JSON.stringify(cache));
};

try {
  cache = JSON.parse(fs.readFileSync(cacheFile));
} catch (e) { }

const testCase = (input, output) => {
  return new Promise((resolve, reject) => {
    const child = spawn(binFile);
    let actual = '', error = '';
    child.stdout.on('data', (data) => actual += data);
    child.stderr.on('data', (data) => error += data);
    
    let killed = false, runtime = false;
    const timeoutId = setTimeout(() => {
      child.stdin.pause();
      child.kill();
      reject({ status: 'TLE' });
      killed = true;
    }, 3000);

    child.on('exit', (code, signal) => {
      if (killed)
        return;

      clearTimeout(timeoutId);

      if (code !== 0) {
        reject({ status: 'RTE' });
        runtime = true;
      }
    });

    child.on('close', () => {
      if (runtime)
        return;

      if (actual !== output && (actual !== output + '\n')) {
        reject({
          status: 'WA',
          expected: output,
          actual
        });
      } else {
        resolve();
      }
    });

    child.stdin.write(input);
  });
};

const processIOs = (data) => {
  const { inputs, outputs } = data;
  const execCase = (index) => {
    if (index < inputs.length) {
      process.stdout.write(`Test ${index} - `);
      testCase(inputs[index], outputs[index])
      .then(() => {
        console.log('OK');
        execCase(index + 1);
      }).catch((err) => {
        if (err.status === 'WA') {
          console.log('WA');
          console.log('EXPECTED:')
          console.log(err.expected);
          console.log('ACTUAL:')
          console.log(err.actual);
        } else if (err.status === 'TLE') {
          console.log('TLE');
        } else if (err.status === 'RTE') {
          console.log('RTE');
        }
      });
    } else {
      console.log('Sample Tests Passed');
    }
  };

  execCase(0);
};

const pId = contestId + problemId;
if (cache[pId]) {
  processIOs(cache[pId]);
} else {
  get(`http://codeforces.com/contest/${contestId}/problem/${problemId}`)
  .then((res) => {
    const $ = cheerio.load(res.body);
    
    const parseTests = (className) => {
      const tests = [];
      $(`.${className} > pre`).each(function () {
        tests.push($('<div>' + $(this).html().replace(/<br>/g, '\n') + '</div>').text());
      });
  
      return tests;
    }
  
    const inputs = parseTests('input');
    const outputs = parseTests('output');
    const data = { inputs, outputs };
    cache[pId] = data;
    saveCache();
  
    return data;
  }).then(processIOs)
  .catch((err) => {
    console.error('Problem not found.');
    process.exit(1);
  });
}
  