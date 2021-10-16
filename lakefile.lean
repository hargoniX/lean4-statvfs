import Lake
open System Lake DSL

def cDir : FilePath := "c"
def ffiSrc := cDir / "ffi.c"
def buildDir := defaultBuildDir

def ffiOTarget (pkgDir : FilePath) : FileTarget :=
  oFileTarget (pkgDir / "build/c/ffi.o") (pkgDir / "c/ffi.c" : FilePath) #[] "leanc"

def cLibTarget (pkgDir : FilePath) : FileTarget :=
  staticLibTarget (pkgDir / "build/c/ffi.a") #[ffiOTarget pkgDir]

package statvfs (pkgDir) (args) {
  -- specify the lib as an additional target
  moreLibTargets := #[cLibTarget pkgDir]
}