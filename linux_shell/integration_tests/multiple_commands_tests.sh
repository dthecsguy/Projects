#!/bin/sh

../rshell "echo hello || echo failed || echo passed"

../rshell "echo hello && echo passed "

../rshell "burger king || echo hello && echo passed"

../rshell "echo hello; echo world && echo passed"
