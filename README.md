# kshttp
**K**asouza's **S**imple **HTTP** Server is a very very simple HTTP server. I've made it mostly because I was curious to see how hard it was to make an http sever in c/c++.
It was quite an interesting journey to learn a bit about socket programming. This isn't finished yet, I plan to add some features, make it a bit safer and add a cleaner API. Also make it compile to an actual library.
If you're curious, take a look at the code (All functions are documented in the header files, the docs are very ~~bad~~ good)!

# Compiling and Running
This project will only work on linux right now (maybe Mac??).
To compile do the following:
```
mkdir build
cd build
cmake .. && cmake --build .
```

and run it by running the generated executable:

`./kshttp`

The default program will listen to `localhost:8080` and respond with something AMAZING.

That's pretty much it by now.

# AAAAAAAAAAAAAA its actually broken right now because for some reason Catch2(testing framework) just won't compile, I'll try to solve it soon
