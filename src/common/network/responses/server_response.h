//
// Created by Jin on 5/13/22.
//

#ifndef MEMORY_GAME_SERVER_RESPONSE_H
#define MEMORY_GAME_SERVER_RESPONSE_H


#include <string>
#include <unordered_map>

#include "../../serialization//serializable.h"

// Identifier for the different response types.
// The ResponseType is sent with every server_response to identify the type of server_response
// during the deserialization on the client side.
enum ResponseType{
    req_response,
    state_diff_msg,
    full_state_msg
};

class server_response : public serializable {
private:
    // for deserialization
    static const std::unordered_map<std::string, ResponseType> _string_to_response_type;
    // for serialization
    static const std::unordered_map<ResponseType, std::string> _response_type_to_string;

protected:
    std::string _game_id;
    ResponseType _type;

    struct base_class_properties {
        std::string game_id;
        ResponseType type;
    };

    explicit server_response(base_class_properties); // base constructor
    static base_class_properties create_base_class_properties(ResponseType type, const std::string & game_id);
    static base_class_properties extract_base_class_properties(const rapidjson::Value& json);

public:
    ResponseType get_type() const;
    std::string get_game_id() const;

    // Tries to create the specific server_response from the provided json
    // Throws exception if parsing fails
    static server_response* from_json(const rapidjson::Value & json);

    // Serializes the server_response into a json object taht can be sent over the network
    virtual void write_into_json(rapidjson::Value & json, rapidjson::Document::AllocatorType& allocator) const override;

#ifdef MEMORY_CLIENT
    virtual void Process() const = 0;
#endif
};

#endif //MEMORY_GAME_SERVER_RESPONSE_H
