env = Environment()
debug = ARGUMENTS.get('debug', 0)

if int(debug):
    env.Append(CXXFLAGS = '-g')
else:
    env.Append(CXXFLAGS = '-O2')

env.Append(CXXFLAGS = "-Wall -Werror")

env.SharedLibrary("libbencode",
                  ["BencodeDecoder.cpp",
                   "Tokenizer.cpp",
                   "PrettyPrinter.cpp"],
                  LIBS = ["libboost_regex-mt"],
                  CPPPATH = ".")

env.Program("tester",
            ["main.cpp",
             "TestBencodeDecoder.cpp",
             "TestTokenizer.cpp",
             "TestValueTypes.cpp"],
            LIBS = ["libbencode", "cppunit"],
            LIBPATH='.')
