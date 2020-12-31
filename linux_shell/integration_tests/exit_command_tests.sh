#!/bin/sh

../rshell "echo hello || exit || echo failed"

../rshell "echo hello && exit || echo failed"

../rshell "burger king || echo hello && exit || echo failed"

../rshell "echo hello; exit || echo failed"

../rshell "exit || echo failed"
