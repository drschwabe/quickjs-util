#include <string>
#include <cstdio>             
#include <iostream>

#include "quickjs-libc.h"
#include "quickjs.h"
#include "quickjsbind.h"
#include "qjs-util.h" 


namespace qjsutil {

void handleJSexception(JSValue jsResult, JSContext* jsContext) {
  if (JS_IsException(jsResult)) {
    //JSRuntime jsRuntime =  JS_GetRuntime(jsContext)
    auto exception = JS_GetException(jsContext);
    std::string message = JS_ToCString(jsContext, exception);
    JS_FreeValue(jsContext, exception);
    std::cout << "Error: " << message << std::endl;     
  }
}   

//re-usable QuickJS run fn: 
void runJs(JSContext* jsContext, std::string script) {
  //bool cud be supplied here to accommodate for if we
  //will return something or note i-e <input> vs <import>
  auto jsResult = JS_Eval(jsContext, script.data(), script.size(), 
    "<import>", JS_EVAL_TYPE_MODULE);   
  handleJSexception(jsResult, jsContext);
}     

void initJs(JSRuntime* js, JSContext* jsContext) {
  printf("hey\n"); 

  JS_SetModuleLoaderFunc(js, NULL, js_module_loader, NULL);
  js_std_init_handlers(js);
  js_init_module_os(jsContext, "os");    
  js_init_module_std(jsContext, "std");      
  js_std_add_helpers(jsContext, -1, NULL);
  std::string initScript = R"xxx(
    import * as os from 'os'
    globalThis.os = os     
    globalThis.log = console.log
  )xxx"; 
  auto jsResult = JS_Eval(jsContext, initScript.data(),
      initScript.size(), 
  "<import>", JS_EVAL_TYPE_MODULE);  
  handleJSexception(jsResult, jsContext);    
}

}
