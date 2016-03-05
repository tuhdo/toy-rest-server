#include "HttpMessage.h"

HttpMessage::HttpMessage(std::string msg) {
    
}

GetMessage::GetMessage(std::string msg):HttpMessage(msg) {
    
}

PostMessage::PostMessage(std::string msg):HttpMessage(msg) {
    
}
