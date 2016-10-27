#!/bin/bash
REPO=`git config remote.origin.url`

git clone $REPO html
cd html/
git checkout gh-pages || git checkout --orphan gh-pages
rm -rf *

cd -

doxygen Doxygen.config

cd html/

if [[ -z `git status --porcelain` ]]; then
    echo "No changes to the docs"
    exit 0
fi

SHA=`git log -1 --format="%s(%h %cd)" --date=short`

git add .
git commit -m "Auto-update" -m "Commit: ${SHA}"
git push origin HEAD

cd -

rm -rf html/
