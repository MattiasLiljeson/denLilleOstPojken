#!/bin/bash

git clean -f
git checkout -f
git pull
results="`make -f solution.mk`"
results+=$
sendmail $results den-lille-ostpojken+cron@googlegroups.com
