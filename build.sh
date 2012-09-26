#!/bin/bash

git clean
git checkout -f
git pull
make -f solution.mk
