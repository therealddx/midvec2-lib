### Thank you for checking out--  
  
# **midvec2-lib**  
  
### A real-time DSP library for arbitrary firmware interfaces.  
  
#### *What does midvec2-lib do?*  
midvec2-lib **tracks** and **processes** discrete-time signals through arbitrary firmware interfaces.  
  
midvec2-lib **tracks** discrete-time signals by establishing a standard for how discrete-time signals are serialized and deserialized; independently of the firmware interface.  
  
midvec2-lib **processes** discrete-time signals by offering a range of operations that can be performed on those discrete-time signals-- for example, convolution with an impulse response; or combination with another signal.  

#### *How does midvec2-lib work?*  
To any client programmer, the most important part of midvec2-lib is the concept of a "Node" (reference `src/Node/`). The "Node" represents an asynchronous process of:  
- `FWIF => char*` -- getting bytes from a firmware interface;  
- `char* => T_in` -- deserializing those bytes into a numerical data type;  
- `T_in => T_out` -- performing a calculation on that numerical type;  
- `T_out => char*` -- serializing the numerical data type into bytes; and  
- `char* => FWIF` -- putting those bytes onto another firmware interface.  
  
In turn, different Nodes exist to solve different types of problems regarding the tracking and processing of data over various interfaces. Reference the documentation under the `doc` folder; or the source files under the `src/Node` folder.  
  
By chaining many Nodes together, the client programmer can devise a cohesive signal processing solution (say, data acquisition via UDP, to which a filter is applied before storage to a textfile).  
  
#### *How do I use it?*  
Following a `git clone`, first build the library by `cd`ing to `build/BuildShared`, and running `build.sh`. It is expected that the client programmer have gcc and g++, at a minimum version of 11.3. This library depends on C++20.
  
From there, `cd` to `src/Application/NodeBench`, and run `build.sh` again. Please heed the build script's output for setting `LD_LIBRARY_PATH` following build. The `nodebench` test application (as well as `bench`) both require the \*.so file from the codebase.  
  
Following that-- if you can `cd` to `src/Application/NodeBench/bin`, and run `nodebench`, then you're in business. Reference its usage statement; and you can start seeing how midvec2-lib ships data around.  
   
If you're still feeling adventurous, you can also build `src/Application/Bench` (just as for `nodebench`-- `build.sh` for library, then `build.sh` for executable), and get a closer verification on how the input pipe mechanisms (the reading of bytes from firmware interfaces) function.  
  
#### *What's the name for?*  
midvec2-lib is the continuation of my "midvec" project, a C library with similar goals, but shallower and broader scope. That project was originally named as a mashup acronym between **m**achine learning, **i**mage processing, **d**igital signal processing, and **vec**tors". Over time, however, my primary interest floated away from ANNs and playing with bitmaps; honing instead towards a complete solution for a narrower problemset.  

#### *What else should I know?*  
- This library and its deliverables are provided under GPLv3 (reference 'LICENSE'), for zero dollar cost. By downloading and using the code, you agree to the license's terms.   
- If you like this library, take a look at midvec2-gui; the Qt visualization of this code.  
- Please forward comments and questions to me here, on GitHub.  
  
### Thank you for taking a look at midvec2-lib!  
  
