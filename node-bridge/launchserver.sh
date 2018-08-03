#!/bin/sh

node index.js &
ssh -o "StrictHostKeyChecking no" -R energetic-api.serveo.net:80:localhost:8080 serveo.net




