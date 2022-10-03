# "cstack.h"
#### by Karetskii Vladislav, MIPT 2022

This is my implementation of the stack structure.
You can make it's more saveful.

## How to turn on difrent types of protection

#### Compile with canary protection

in ```cstack.h```
~~~~
 // this is code turns on canary protection
    ...........

 >>>#define SAVEFLAG 0
    #define HASHFLAG 0

    ............
~~~~

#### Compile with Has-protaction

in ```cstack.h```
~~~~
 // this is code turns on canary protection
    ...........

    #define SAVEFLAG 0
 >>>#define HASHFLAG 0

    ............
~~~~

You can also change hash algorithm in function ```static uint64_t stackHash``` in ```cstack.cpp```.