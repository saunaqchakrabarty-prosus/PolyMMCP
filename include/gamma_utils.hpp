#pragma once 
#include <string> 
#include <boost/bimap.hpp>

namespace Polymarket{
    using TokenMap = boost::bimap<std::string, std::string>;
    using TokenPair = TokenMap::value_type;

    class GammaClient{
        public: 
            GammaClient(std::string base_url = "https://gamma-api.polymarket.com"); 
            TokenMap get_top_n_markets(int n); 
        
        private: 
            std::string base_url; 
            std::string perform_get(const std::string& endpoint);
    };
}