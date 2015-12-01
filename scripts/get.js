import request from 'request';

export default (url) => new Promise((resolve, reject) => {
  request(url, (err, res, body) => {
    if (err) return reject(err);
    res.body = body;
    if (res.statusCode >= 400) return reject(res);
    resolve(res);
  });
});