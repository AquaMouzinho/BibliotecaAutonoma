#include "crow.h"
#include <fstream>
#include <sstream>

// Função utilitária para ler arquivos HTML
std::string load_html(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return "Erro: arquivo não encontrado: " + path;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main() {
    crow::SimpleApp app;

    // Página inicial
    CROW_ROUTE(app, "/")([](){
        return load_html("./index.html");
    });

    // Admin
    CROW_ROUTE(app, "/admin/manageadmin")([](){
        return load_html("./admin/manageadmin.html");
    });

    CROW_ROUTE(app, "/admin/pageadmin")([](){
        return load_html("./admin/pageadmin.html");
    });

    CROW_ROUTE(app, "/admin/postadmin")([](){
        return load_html("./admin/postadmin.html");
    });

    // User
    CROW_ROUTE(app, "/user/user")([](){
        return load_html("./user/user.html");
    });

    CROW_ROUTE(app, "/user/postuser")([](){
        return load_html("./user/postuser.html");
    });

    CROW_ROUTE(app, "/user/manageruser")([](){
        return load_html("./user/manageruser.html");
    });


    CROW_ROUTE(app, "/login").methods("POST"_method)([](const crow::request& req){
    	
	// Extrai os dados do corpo da requisição
    	auto body = crow::query_string(req.body);

    	std::string email = body.get("email") ? body.get("email") : "user";
    	std::string senha = body.get("senha") ? body.get("senha") : "user";

    	crow::response res;

    	// Validar login se é admin.
    	if (email == "admin" && senha == "admin") {
        	// Redireciona se estiver certo
        	res.code = 303;
        	res.set_header("Location", "/admin/pageadmin");
        	return res;
    	} 
    	// Validar login se é admin.
    	else if(email == "user" && senha == "user"){
    		res.code = 303;
    		res.set_header("Location", "/user/user");
    		return res;

    	}
    	else {
       		// Resposta com erro simples
       		return crow::response(401, "Login inválido");
    	}
   });


    // Porta e execução
    app.port(18080).multithreaded().run();
}

