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

if (['A', 'B', 'C', 'D', 'E'].indexOf(problemId) == -1) {
  console.error('Invalid problem id.');
  process.exit(1);
}

let source = 'isadnfaisndf';
/*try {
  source = fs.readFileSync(path.join(process.cwd(), file || 'problem.cpp'));
} catch (e) {
  console.error('Invalid source file.');
  console.log(e);
  process.exit(1);
}*/

get(`http://codeforces.com/contest/${contestId}/submit`)
.then(() => {

}).then(() => {
  post(`http://codeforces.com/contest/${contestId}/submit?csrf_token=fbc1671475222384ffaa924ed380d1fd`, {
    csrf_token: 'fbc1671475222384ffaa924ed380d1fd',
    ftaa: 'ab57nabywx2ygqfrmz',
    bfaa: '89f225e804110f6765a573bfa64f0d68',
    action: 'submitSolutionFormSubmitted',
    submittedProblemIndex: problemId,
    programTypeId: '42',
    source: source,
    _tta: '963',
  }, {
    Accept: 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8',
    'Accept-Encoding': 'gzip, deflate',
    'Accept-Language': 'en-US,en;q=0.8,es;q=0.6',
    'Cache-Control': 'max-age=0',
    Connection: 'keep-alive',
    'Content-Length': '1081',
    'Content-Type': 'multipart/form-data; boundary=----WebKitFormBoundaryXHYy0RyKFhaAnch5',
    Cookie: 'lastOnlineTimeUpdaterInvocation=1448943823024; JSESSIONID=34504B3BAFF18C5E3182F40E567BD209-n1; 39ce7=CFNwFkad; __utmt=1; _ym_uid=1448943466990522828; _ym_isad=1; evercookie_png=ab57nabywx2vgqfrmz; evercookie_etag=ab57nabywx2vgqfrmz; evercookie_cache=ab57nabywx2vgqfrmz; 70a7c28f3de=ab57nabywx2vgqfrmz; X-User=1681015665a2a57b1090056f1ae5abc32827be12148516c5a0eb62eccfde3a8b4b516c7eef64a736; __utma=71512449.997551442.1448943465.1448943465.1448943720.2; __utmb=71512449.8.10.1448943720; __utmc=71512449; __utmz=71512449.1448943720.2.2.utmcsr=google|utmccn=(organic)|utmcmd=organic|utmctr=(not%20provided)',
    Host: 'codeforces.com',
    Origin: 'http: //codeforces.com',
    Referer: 'http: //codeforces.com/contest/602/submit',
    'Upgrade-Insecure-Requests': '1',
    'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/46.0.2490.86 Safari/537.36'
  }).then((res) => {
    console.log(res.body);
    console.log('Submitted.');
  }).catch(() => {
    console.log('Failed to submit.');
  });
});