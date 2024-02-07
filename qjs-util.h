#ifndef QJS_UTIL_H 
#define QJS_UTIL_H 

#include "qjs-util.cpp" 

namespace qjsutil {

//re-usable exception handler for QuickJS calls:  
void handleJSexception(JSValue jsResult, JSContext* jsContext);        

//main fn to run Javscript 
void runJs(JSContext* jsContext, std::string script); 

JSValue returnJs(JSContext* jsContext, std::string script);   

//initialize a JS runtime (with opinionated defaults): 
void initJs(JSRuntime* js, JSContext* jsContext); 

}

#endif // !QUIKJS_BIND_H

