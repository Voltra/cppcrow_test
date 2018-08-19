#pragma once

////ROUTING
//Base macro
#define METHOD_SPECIFIC_ROUTE(app, route, handler, method...)\
CROW_ROUTE(app, route)\
.methods(method)\
(handler)

//Regular HTTP methods
#define GET(app, route, handler) METHOD_SPECIFIC_ROUTE(app, route, handler, "GET"_method)
#define POST(app, route, handler) METHOD_SPECIFIC_ROUTE(app, route, handler, "POST"_method)
#define PUT(app, route, handler) METHOD_SPECIFIC_ROUTE(app, route, handler, "PUT"_method)
#define DELETE(app, route, handler) METHOD_SPECIFIC_ROUTE(app, route, handler, "DELETE"_method)

//Additional HTTP methods
#define PATCH(app, route, handler) METHOD_SPECIFIC_ROUTE(app, route, handler, "PATCH"_method)
#define HEAD(app, route, handler) METHOD_SPECIFIC_ROUTE(app, route, handler, "HEAD"_method)
#define OPTIONS(app, route, handler) METHOD_SPECIFIC_ROUTE(app, route, handler, "OPTIONS"_method)
#define CONNECT(app, route, handler) METHOD_SPECIFIC_ROUTE(app, route, handler, "CONNECT"_method)
#define TRACE(app, route, handler) METHOD_SPECIFIC_ROUTE(app, route, handler, "TRACE"_method)
#define PURGE(app, route, handler) METHOD_SPECIFIC_ROUTE(app, route, handler, "PURGE"_method)

//Combo methods
#define GET_POST(app, route, handler) METHOD_SPECIFIC_ROUTE(app, route, handler,\
"GET"_method, "POST"_method)

#define ALL(app, route, handler) METHOD_SPECIFIC_ROUTE(app, route, handler,\
"GET"_method, "POST"_method, "PUT"_method, "DELETE"_method)

#define EVERYTHING(app, route, handler) METHOD_SPECIFIC_ROUTE(app, route, handler,\
"GET"_method, "POST"_method, "PUT"_method, "DELETE"_method, "PATCH"_method, "HEAD"_method,\
"OPTIONS"_method, "CONNECT"_method, "TRACE"_method, "PURGE"_method)

//Aliases
#define SERVE_STATIC(app, route, handler) ALL(app, route, handler)

////TOOLS
#define CTX(app, mw, rq) app.get_context<mw>(rq)
