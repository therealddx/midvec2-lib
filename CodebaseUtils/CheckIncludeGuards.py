# 
# CheckIncludeGuards.py.
# 
# For all header or template files in the codebase, ensure that their
# include guards are in place to match the filename.
# 
# From there, print out a view of all the files, and provide an aggregate
# pass/fail check.
# 

# 
# os.walk('.') returns a list of 3-tuples with the following format:
#  - The directory being examined.
#  - The directories under it.
#  - The files under it.
# 
# The 3-tuples that os.walk('.') returns are sorted in order of the first
# item in that tuple: The directory being examined.
# 
# That directory being examined gets traversed in breadth-first order.
# 

import os # os.sys, os.path.

INCLUDE_GUARD_FILE_EXTENSIONS = [".h", ".hh", ".hpp", ".tpp"]

def CheckIncludeGuards(arg_sourceTreePath):

  # debug.
  fDebug = open("./dbg-CheckIncludeGuards.txt", 'w')

  # initiate a recursive walk down the source tree.
  # for each file you see on the way down:
  #  if its extension is one of the includable files (header, template-implementation, etc.)
  #   then run 'CheckIncludeGuard' on its absolute path.
  # 
  for cwd, lsDirs, lsFiles in os.walk(arg_sourceTreePath):
    print("os.walk: " + cwd + ", " + str(lsDirs) + ", " + str(lsFiles), file=fDebug)
    for eachFile in lsFiles:
      print("..is " + eachFile + " an includable? (extn '" + os.path.splitext(eachFile)[1] + "')", file=fDebug)
      if os.path.splitext(eachFile)[1] in INCLUDE_GUARD_FILE_EXTENSIONS:
        print("...." + eachFile + " is an includable. checking its includeguard...", file=fDebug)
        CheckIncludeGuard(os.path.join(cwd, eachFile), fDebug)

  # close debug file.
  fDebug.close()

# 
# CheckIncludeGuard.
# 
# Executes the operation of actually checking the include-guard
# for an includable (header / template) file.
# 
# Given arg_filePath (either absolute path, or relative path from python cwd),
# ensure that its three include-guard components (#ifndef, #define, #endif) are
# in place and named appropriately.
# 
# Returns nothing.
# 
def CheckIncludeGuard(arg_filePath, arg_debugFileHandle):

  # define a desired capitalized name for the includeguard:
  #  the basename of the arg_filePath. (MyCppClass.hpp)
  #  with '.' replaced by '_'. (MyCppClass_hpp).
  #  all letters to uppercase. (MYCPPCLASS_HPP).
  # 
  capitalName = os.path.basename(arg_filePath).replace('.', '_').upper()
  print("......checking '" + os.path.basename(arg_filePath) + "' for include guard '" + capitalName + "'",
    file=arg_debugFileHandle)

  # open a read handle to that source file.
  # 
  # let the regexwork be simple:
  #  flag anything that doesn't conform to strict whitespace standards.
  #  do not try to deduce meaningful syntax.
  #   (e.g. whether some idiot put the '#ifndef' in the middle of the file)
  # 
  #  find a match for '#ifndef (capital-name)'
  #  find a match for '#define (capital-name)'.
  #  find a match for '#endif \/\/ (capital-name)'.
  # 

  # vars: search + check.
  # 
  find_ifndef = "#ifndef " + capitalName + "\n"
  find_define = "#define " + capitalName + "\n"
  find_endif  = "#endif // " + capitalName + "\n"

  # get all lines from source file.
  # 
  allLines = []
  with open(arg_filePath, 'r') as f:
    allLines = f.readlines()

  # if all the keys you care about are there:
  # 
  if find_ifndef in allLines and find_define in allLines and find_endif in allLines:
    print("CheckIncludeGuards.py: " + arg_filePath + ": ok")
  else:
    print("CheckIncludeGuards.py: " + arg_filePath + ": bad")

  # granular output for debug printout.
  # 
  if find_ifndef in allLines:
    print("........searching for '" + find_ifndef.strip() + "': OK", file=arg_debugFileHandle)
  else:
    print("........searching for '" + find_ifndef.strip() + "': BAD", file=arg_debugFileHandle)

  if find_define in allLines:
    print("........searching for '" + find_define.strip() + "': OK", file=arg_debugFileHandle)
  else:
    print("........searching for '" + find_define.strip() + "': BAD", file=arg_debugFileHandle)

  if find_endif in allLines:
    print("........searching for '" + find_endif.strip() + "': OK", file=arg_debugFileHandle)
  else:
    print("........searching for '" + find_endif.strip() + "': BAD", file=arg_debugFileHandle)

def main():
  # parse cli args.
  # 
  # usage:
  #  os.sys.argv[0]: *.py script executable name.
  #  os.sys.argv[1]: absolute path to source tree.
  # 

  # arg check: ensure that path, os.sys.argv[1], exists.
  #  else: exit.
  # 
  arg_sourceTreePath = os.sys.argv[1]
  if os.path.exists(arg_sourceTreePath) == False:
    print("CheckIncludeGuards.py: error: invalid source tree path")
    return
 
  # run.
  # 
  CheckIncludeGuards(arg_sourceTreePath)

# module entry.
# 
if __name__ == '__main__':
  main()

