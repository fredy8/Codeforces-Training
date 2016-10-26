#!/usr/local/bin/babel-node

import path from 'path';
import fs from 'fs';
import post from './post';
import get from './get';

const args = process.argv.slice(2);

if (args.length < 2) {
  console.log('Usage: contestId problemId file');
  process.exit(1);
}

const contestId = args[0];
const problemId = args[1];
const file = args[2];

if (!contestId || isNaN(contestId)) {
  console.error('Invalid contest id.');
  process.exit(1);
}

if (['A', 'B', 'C', 'D', 'E', 'F'].indexOf(problemId) == -1) {
  console.error('Invalid problem id.');
  process.exit(1);
}

let source = '';
try {
  source = fs.readFileSync(path.join(process.cwd(), file || 'problem.cpp'));
} catch (e) {
  console.error('Invalid source file.');
  console.log(e);
  process.exit(1);
}

post(`http://codeforces.com/contest/${contestId}/submit?csrf_token=df1544bdc3f592e709824c919d72b7f9`, {
  csrf_token: 'df1544bdc3f592e709824c919d72b7f9',
  ftaa: 'ab57nabywx2ygqfrmz',
  bfaa: '89f225e804110f6765a573bfa64f0d68',
  action: 'submitSolutionFormSubmitted',
  submittedProblemIndex: problemId,
  programTypeId: '42',
  source: source,
  _tta: '963',
}, {
  Cookie: 'X-User=986d4c5534f264fe57abb0c29f9e84d60fc28207a0ea518636d84b5e0fcffa360a20143347da507d',
}).then((res) => {
  console.log('Submitted.');
}).catch(() => {
  console.log('Failed to submit.');
});
