#!/usr/bin/env bash
git clone \
    --depth 1 \
    --filter=blob:none \
    --no-checkout \
    git@github.com:rickardljung/bootcamp_course.git;
 cd bootcamp_course
 git checkout main -- assignments/day7/01_assignment_make

cd assignments/day7/01_assignment_make/
cd lib
make
cd ..
make
./shape_app
