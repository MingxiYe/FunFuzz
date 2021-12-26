file(GLOB
    sources 
    "./CFG/cfgbuilder/*.cpp" 
    "./CFG/SymbolicExecution/*.cpp")
file(GLOB 
    headers 
    "./CFG/cfgbuilder/*.h" 
    "./CFG/contract/*.h" 
    "./CFG/SymbolicExecution/*.h" 
    "./opcodes/*.h" 
    "./opcodes/opcode/*.h"
    "./opcodes/opcode/ArithmeticOpcode/*.h"
    "./opcodes/opcode/ArithmeticOpcode/BinaryArithmeticOpcode/*.h"
    "./opcodes/opcode/ArithmeticOpcode/TernaryArithmeticOpcode/*.h"
    "./opcodes/opcode/ArithmeticOpcode/UnaryArithmeticOpcode/*.h"
    "./opcodes/opcode/BlockOpcode/*.h"
    "./opcodes/opcode/ControlFlowOpcode/*.h"
    "./opcodes/opcode/EnvironmentalOpcode/*.h"
    "./opcodes/opcode/StackOpcode/*.h"
    "./opcodes/opcode/SystemOpocde/*.h"
    "./SolidityInfo/*.h"
    "./Utils/*.h"
    "./Utils/*.hpp")

include_directories(${Boost_INCLUDE_DIRS})
add_library(libcfg ${sources} ${headers})
target_link_libraries(libcfg ${Boost_LIBRARIES})