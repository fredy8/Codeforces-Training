import request from 'request';
import Promise from 'bluebird';
import cheerio from 'cheerio';
import R from 'ramda';
import fs from 'fs';

const get = (url) => new Promise((resolve, reject) => {
  request(url, (err, res, body) => {
    if (err) return reject(err);
    res.body = body;
    if (res.statusCode !== 200) return reject(res);
    resolve(res);
  });
});

const getContestStats = (problemId) =>
  get(`http://codeforces.com/contest/${problemId}/standings/page/1`)
  .then((res) => {
    const $ = cheerio.load(res.body);
    
    const pages = $('div.custom-links-pagination a');
    if (pages.length == 0) return [];
    const lastPageHtml = $(pages[pages.length - 1]).html();
    const totalParticipants = parseInt(lastPageHtml.slice(lastPageHtml.lastIndexOf(';') + 1), 10);
    const solvedBy = [];

    $('td.smaller > .cell-passed-system-test').slice(1).each(function () {
      solvedBy.push(1 - parseInt($(this).html(), 10) / totalParticipants);
    });

    return solvedBy;
  });

console.log('Fetching contests list...');
get('http://codeforces.com/api/contest.list')
.then((res) => {
  console.log('Done')
  const parsedBody = JSON.parse(res.body);
  const allContests = parsedBody.result;
  const contests = allContests
  .filter((contest) => contest.durationSeconds === 7200 && contest.name.includes('Div. 2') && contest.type === 'CF' && contest.phase == 'FINISHED')
  .map((contest) => contest.id);

  let currentContestIdx = 0;
  const problems = [];
  const promises = [];
  let completed = 0;

  console.log('Fetching problems...')
  contests.forEach((contestId) => {
    const promise = getContestStats(contestId)
    .then((stats) => {
      const percentComplete = ((++completed)/contests.length)*100;
      console.log(`${parseFloat(Math.round(percentComplete * 100) / 100).toFixed(2)}%`)
      if (stats.length != 5) return;
      for(let i = 0; i < 5; i++) {
        problems.push({
          url: `http://codeforces.com/contest/${contestId}/problem/${String.fromCharCode(65 + i)}`,
          difficulty: stats[i]
        });
      }
    });

    promises.push(promise);
  });

  Promise.all(promises).then(() => {
    console.log('Done.');
    fs.writeFile('problems.json', JSON.stringify(problems, null, 4), (err) => {
      if(err) return console.log(err);
    }); 
  });
});