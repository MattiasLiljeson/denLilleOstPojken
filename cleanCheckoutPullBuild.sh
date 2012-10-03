#!/bin/bash

git clean -f
git checkout -f
git pull
bash build.sh
