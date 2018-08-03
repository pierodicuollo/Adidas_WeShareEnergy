const watch = require('node-watch');
const express    = require('express');
const app        = express();
const port = 8080;
const router = express.Router();
const imageFolder = '../bin/data'
app.use('/data', express.static(imageFolder));

let city = 'Florence';
let image = '';
let responseSkeleton = {"force":0,"image":'/data/default.png',"city":city};

startServer();
watchImageFolder();

function startServer() {
  console.log('Starting API Server');
  app.listen(port);
}

function watchImageFolder() {
  watch(imageFolder, { recursive: true }, function(evt, name) {
    console.log(evt + ' ' + name);
    if (evt !== 'remove') {
      console.log(name)
      console.log('New image added')
      var img = name.replace('../bin','');
      responseSkeleton.image = img;
      var force = getRandomInt(100, 500);
      responseSkeleton.force = force;
    }
  });
}

function getRandomInt(min, max) {
  return Math.floor(Math.random() * (max - min + 1)) + min;
}

app.get('/image', function(req, res) {
  res.setHeader('Access-Control-Allow-Origin', '*');
  res.setHeader('Access-Control-Allow-Methods', 'GET, POST, OPTIONS, PUT, PATCH, DELETE'); // If needed
  res.setHeader('Access-Control-Allow-Headers', 'X-Requested-With,content-type'); // If needed
  res.setHeader('Access-Control-Allow-Credentials', true);
  res.setHeader('Content-Type', 'application/json');
  res.send(responseSkeleton)
});

app.get('/force', function(req, res) {
  res.status(200)
  res.setHeader('Access-Control-Allow-Origin', '*');
  res.setHeader('Access-Control-Allow-Methods', 'GET, POST, OPTIONS, PUT, PATCH, DELETE'); // If needed
  res.setHeader('Access-Control-Allow-Headers', 'X-Requested-With,content-type'); // If needed
  res.setHeader('Access-Control-Allow-Credentials', true);
  res.setHeader('Content-Type', 'application/json');
  res.send(responseSkeleton.force);
});
