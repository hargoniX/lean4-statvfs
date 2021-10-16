/-
  Copyright (c) 2021 Henrik Böving. All rights reserved.
  Released under MIT license as described in the file LICENSE.
  Authors: Henrik Böving
-/
import Statvfs

open System

def main (args : List String) : IO UInt32 := do
  if h : args = [] then
    IO.println "Missing argument: path"
    return 1
  else
    let path <- FilePath.mk $ args.head h
    if h2 : !(←path.pathExists) then
      IO.println "Invalid path"
      return 1
    let stat <- Statvfs.of_path path
    IO.println "Printing statvfs information"
    IO.println $ repr stat
    return 0
