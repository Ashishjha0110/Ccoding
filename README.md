# Parsing Json file to setup function in C.

This particular project is parsing given json data based on the mvp requirements mentioned below.
This project will be resposible to generate a .c file containing a function with various declarations mentioned in the input json file.

## Requirements

### MVP 

- pass all the node defination to a json file namely valid.json
- Parse the given json file to equivalent structure in C 
- Analyze the parsed json structure and decide on the autocode generation
- Create a C file namely autoCodeSetup.c 
- Append the C file with the generated autocode after parsing the json file.


## Basic Commands 

### Compile code with static linking

`gcc -o output -I.. main.c json.c -lm`

### Exeute the output

`./output`

## Process flow

- A valid json file with node defination is required.
- Structure for valid json file is shown below
```json
[
  {
    "NodeA": {
      "Type": "Input",
      "Channel":"DI_Channel_I1_0", 
      "Initial State": "GPIO_PIN_RESET"
    }
  },
  {
    "NodeB": {
      "Type": "Input",
      "Channel":"DI_Channel_I0_0", 
      "Initial State": "GPIO_PIN_SET"
    }
  }
 ]
 ```
 - valid.json is then parse using [json parsing](https://github.com/udp/json-parser) library 
 - In main.c create the function to read all the nodes generated after json parsing 
 - Generate the code based on the node defination.
 - Append the generated code to autocodesetup.c
 
