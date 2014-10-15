#!/bin/sh
tar cvf - usr | ( cd / ; tar xf - )
echo "Installed"
