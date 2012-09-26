#!/bin/bash

git clean -f
git checkout -f
git pull
make -f solution.mk
