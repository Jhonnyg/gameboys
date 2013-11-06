#!/bin/env sh
tail -n+4 $(dirname $0)/makewin32.bat | sed "s/^::/#/" | bash
