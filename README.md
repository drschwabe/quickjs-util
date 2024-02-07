## quickjs-util

Some high-level functions to make it easier to use QuickJS in C++ 


Initialize a JS runtime (with opinionated defaults): 

```
void initJs(JSRuntime* js, JSContext* jsContext);                
```

Exception handler for QuickJS calls:

```
void handleJSexception(JSValue jsResult, JSContext* jsContext);        
```

Function to run Javscript 

```
void runJs(JSContext* jsContext, std::string script); 
```

Function to run JavaScript and return the value back to C++ land: 

```
JSValue returnJs(JSContext* jsContext, std::string script);   
```


#### dependencies

To use this utility lib you will need to include quickjs and quickjs-bind: 

https://github.com/bellard/quickjs

https://github.com/Bzi-Han/quickjs-bind


#### example

```c++
#include "quickjs-libc.h"
#include "quickjs.h"
#include <algorithm> //< needed for quickjs-bind 
#include "quickjsbind.h"   
#include "qjs-util.h" 

JSRuntime *js;
JSContext *context;                 

void log(const char* message) {
  printf("%s\n", message);
}  

void consoleLog(quickjs::Args args) { 
  using namespace std; 
  //Print to C++ from JS       
  for (size_t i = 0; i < args.Size(); i++)
    cout << args[i].Cast<string>() << " ";
    cout << endl;                      
}                             

int main() { 
  log("hello world");  

  //setup JS with globals and dependencies:
  js = JS_NewRuntime();
  context = JS_NewContext(js);        

  qjsutil::initJs(js, context); 

  auto cModule = quickjs::Object(context);
  cModule.AddFunction<consoleLog>("log");
  quickjs::Object::GetGlobal(context).AddObject("c", cModule);

  qjsutil::runJs(context, R"js(
    globalThis.c = c //< access to C++ functions   
    c.log('hello world from JS!') 
  )js"); 
           
}                                 
``` 
