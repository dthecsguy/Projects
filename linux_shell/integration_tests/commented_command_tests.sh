#!/bin/sh

../rshell "echo world #|| echo world"

../rshell "echo world && ls #-a"

../rshell "echo \"hello world\" #||"

../rshell "echo \"hello #world\""
