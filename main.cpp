#include <crow/crow_all.h>
#include <string>
#include <boost/filesystem.hpp>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include <app.hpp>

namespace fs = boost::filesystem;
namespace mw = app::middlewares;
using namespace app::helpers;

int main(){
	crow::App<crow::CookieParser, mw::Session> app;
	crow::mustache::set_base("./templates");
	
	SERVE_STATIC(app, "/assets/<path>", [](const crow::request&, const std::string& path) -> crow::response{ 
		static const Regex dotOrDotDot{"(/?\\.+/|/\\.+/?)"}; // slash followed by dots or dots followed by slash
		
		CROW_LOG_DEBUG << "Serving static file: " << path;
		
				
		auto unauthorized = crow::response(403);
		auto notFound = crow::response(404);
		auto serverError = crow::response(500);
		
		if(dotOrDotDot.appliesTo(path))
			return unauthorized;
        
        const auto fsPath = fs::absolute(
			fs::path(fromStatic(path))
		);
			
		if(fs::is_directory(fsPath)) //decomposed if for security purposes (could interprete "./" or "../")
			return unauthorized;
			
		if(!fs::is_regular_file(fsPath))
			return notFound;
		
		std::ifstream file(fsPath.c_str());
		if(!file.is_open())
			return serverError;		
		
		std::stringstream stream{};
		
		while(file.good()){
			std::string buffer;
			std::getline(file, buffer);
			
			if(file.good() || file.eof())
				stream << buffer << '\n';
		}
		
		bool isEOF = file.eof();
		file.close();
		if(isEOF){
			crow::response res(stream.str());
			res.add_header("Content-Type", "application/octet-stream");
			return res;
		}else
			return serverError;
		
	});

	GET(app, "/", []{
		return "Yolo !";
	});
	
	GET(app, "/<int>", [](int param){
		return "Yolo: " + std::to_string(param);
	});
	
	GET(app, "/json", []{
		crow::json::wvalue json;
		json["life"] = 42;
		return json;
	});
	
	GET(app, "/json/<int>", [](int param){
		crow::json::wvalue json;
		json["life"] = param;
		return json;
	});
	
	GET(app, "/user/<string>/<string>", [](const std::string& username, const std::string& password){
		crow::mustache::context data;
		data["username"] = username;
		data["password"] = password;
		
		return crow::mustache::load("layout.twig").render(data);
	});
    
    GET(app, "/s", [&](const crow::request& rq){
        auto session = CTX(app, mw::Session, rq).session;
        
        return session->has("PINGAS")
        ? session->dump()
        : [&]{
            session->set("PINGAS", std::rand());
            return std::string("nope");
        }();
    });
	
	CROW_LOG_INFO << "Base path: " << fs::current_path();

// 	app.loglevel(crow::LogLevel::Debug);
    app.loglevel(crow::LogLevel::Info);
	app.port(18080).multithreaded().run();

    return 0;
}
