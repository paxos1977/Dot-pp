#!/bin/sh

mkdir -p xcode_build && cd xcode_build && cmake -G "Xcode" .. && open Dot++.xcodeproj && cd ..


