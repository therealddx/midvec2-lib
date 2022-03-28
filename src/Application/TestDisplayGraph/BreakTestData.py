# 
# BreakTestData.py.
# 
# Python script to take the graph dump file and cut its graph dumps
# into many separate files.
# 

import os # os.path, os.sys

def BreakTestData(
    arg_file
  , arg_keyPattern
  , arg_beforeContext
  , arg_afterContext):

  # open arg_file.
  # 
  with open(arg_file, 'r') as myBreakFile:

    # just get all the lines.
    # 
    allLines = myBreakFile.readlines()

    for eachLineIndex in range(len(allLines)):
      sliceLines = []

      if arg_keyPattern in allLines[eachLineIndex]:
        startIndex = eachLineIndex - arg_beforeContext
        if startIndex < 0:
          startIndex = 0

        endIndex = eachLineIndex + arg_afterContext
        if endIndex >= len(allLines):
          endIndex = len(allLines) - 1

        sliceLines = allLines[startIndex:(endIndex + 1)]

        with open(arg_file + "." + str(eachLineIndex + 1), 'w') as myWriteFile:
          for eachLine in sliceLines:
            myWriteFile.write(eachLine)

def main():

  # arg check: invalid argc:
  if len(os.sys.argv) != 5:
    print("BreakTestData.py: error: check usage in *.py script: invalid arg count")
    return

  # cli breakdown (usage):
  #  os.sys.argv[0]: *.py script name.
  #  os.sys.argv[1]: file to break apart.
  #  os.sys.argv[2]: 'key pattern' to look for in 'file to break'.
  #  os.sys.argv[3]: lines of context to take before 'key pattern' line.
  #  os.sys.argv[4]: lines of context to take after 'key pattern' line.
  # 
  arg_file = os.sys.argv[1] # string.
  myFile = None # test file handle to check argument.
  try:
    myFile = open(arg_file, 'r')
  except OSError:
    print("BreakTestData.py: error: can't open file for reading: " + arg_file)
    return
  myFile.close()

  arg_keyPattern = os.sys.argv[2] # string.

  try:
    arg_beforeContext = int(os.sys.argv[3]) # int.
    if arg_beforeContext < 0: # mandate value >= 0.
      raise ValueError
  except ValueError:
    print("BreakTestData.py: error: before context: invalid argument: " + os.sys.argv[3])
    return

  try:
    arg_afterContext = int(os.sys.argv[4]) # int.
    if arg_afterContext < 0: # mandate value >= 0.
      raise ValueError
  except ValueError:
    print("BreakTestData.py: error: after context: invalid argument: " + os.sys.argv[4])
    return

  # made it this far: run.
  BreakTestData(
    arg_file
  , arg_keyPattern
  , arg_beforeContext
  , arg_afterContext)

if __name__ == '__main__':
  main()

