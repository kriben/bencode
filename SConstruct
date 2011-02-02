env = Environment()
debug = ARGUMENTS.get('debug', 0)

if int(debug):
    env.Append(CXXFLAGS = '-g')
else:
    env.Append(CXXFLAGS = '-O2')

env.Append(CXXFLAGS = "-Wall -Werror")
env.Append(CPPPATH = '.')

env.SharedLibrary("libbencode",
                  ["BencodeDecoder.cpp",
                   "Tokenizer.cpp",
                   "PrettyPrinter.cpp"],
                  LIBS = ["libboost_regex-mt"])

env.Program("tester",
            ["tests/main.cpp",
             "tests/TestBencodeDecoder.cpp",
             "tests/TestTokenizer.cpp",
             "tests/TestValueTypes.cpp"],
            LIBS = ["libbencode", "cppunit"],
            LIBPATH='.')

