#pragma once 
#include <string> 
#include <boost/bimap.hpp>
#include <gamma_methods/gamma_utils.h>
#include <polymarket/http_client.hpp>

namespace Polymarket{
    GammaClient::GammaClient(std::string base_url) : base_url(std::move(base_url)){};

    TokenMap get_top_n_markets(int n ){

    }
    std::string perform_get(const std::string& endpoint){ 

    }

}