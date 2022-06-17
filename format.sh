#!/usr/bin/env bash
find ./* -name *.cpp -or -name *.h -not -name *cap* | xargs clang-format -i 
