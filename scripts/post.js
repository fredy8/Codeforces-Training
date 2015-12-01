import request from 'request';

export default (url, body, headers) => new Promise((resolve, reject) => {
  request.post({ url, formData: body, headers: headers || {} }, (err, res, responseBody) => {
    if (err) return reject(err);
    res.body = responseBody;
    if (res.statusCode >= 400) return reject(res);
    resolve(res);
  });
});