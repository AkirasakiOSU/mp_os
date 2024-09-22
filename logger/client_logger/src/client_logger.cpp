#include <not_implemented.h>

#include "../include/client_logger.h"
#include <fstream>
#include <exception>
std::map<std::string, client_logger::stream> client_logger::_streams;
client_logger::stream::stream(std::string const &path) :
    _str(nullptr),
    _countOfLogers(1)
{
    try {
        _str = new std::ofstream(path);
        if(!_str->is_open()) throw std::logic_error("File open error");
    }
    catch (std::bad_alloc const &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
    catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
    catch (...) {
        std::cerr << "Unknown error" << std::endl;
        throw std::logic_error("Unknown error");
    }
}

client_logger::stream::stream(client_logger::stream &&other) noexcept :
_str(other._str),
_countOfLogers(other._countOfLogers)
{
    other._str = nullptr;
    other._countOfLogers = 0;
}

client_logger::stream &client_logger::stream::operator=(stream &&other) noexcept {
    if(this != &other) {
        _str->close();
        delete _str;
        _str = other._str;
        _countOfLogers = other._countOfLogers;
        other._str = nullptr;
        other._countOfLogers = 0;
    }
    return *this;
}


client_logger::stream::~stream() {
    _countOfLogers = 0;
    if(_str != nullptr) _str->close();
    delete _str;
    _str = nullptr;
}

client_logger::client_logger(std::map<std::string, unsigned char> const &map) :
_severities(map)
{
    auto iterPaths = map.begin();
    while(iterPaths != map.end()) {
        auto iterStreams = _streams.find(iterPaths->first);
        if(iterStreams != _streams.end()) {
            ++(iterStreams->second._countOfLogers);
        }else {
            stream node(iterPaths->first);
            _streams.emplace(iterPaths->first, std::move(node));
        }
        ++iterPaths;
    }
}

void client_logger::encrementStream(std::map<std::string, unsigned char>::iterator &iterPaths) {
    auto iterStreams = _streams.find(iterPaths->first);
    if(iterStreams != _streams.end()) {
        --(iterStreams->second._countOfLogers);
        if(!(iterStreams->second._countOfLogers)) {
            iterStreams->second._str->close();
            delete iterStreams->second._str;
            iterStreams->second._str = nullptr;
            _streams.erase(iterStreams);
        }
    }
}

client_logger::client_logger(
    client_logger const &other) :
    _severities(other._severities)
{
    auto iterSeverities = _severities.begin();
    while(iterSeverities != _severities.end()) {
        ++(_streams.find(iterSeverities->first)->second._countOfLogers);
        ++iterSeverities;
    }
    //throw not_implemented("client_logger::client_logger(client_logger const &other)", "your code should be here...");
}

client_logger &client_logger::operator=(
    client_logger const &other)
{
    if(this != &other) {
        auto iterSeverity = _severities.begin();
        while(iterSeverity != _severities.end()) {
            if(other._severities.find(iterSeverity->first) == other._severities.end()) {
                encrementStream(iterSeverity);
            }
            ++iterSeverity;
        }
        _severities = other._severities;
    }
    return *this;
    //throw not_implemented("client_logger &client_logger::operator=(client_logger const &other)", "your code should be here...");
}

client_logger::client_logger(
    client_logger &&other) noexcept :
_severities(std::move(other._severities))
{
    //throw not_implemented("client_logger::client_logger(client_logger &&other) noexcept", "your code should be here...");
}

client_logger &client_logger::operator=(
    client_logger &&other) noexcept
{
    throw not_implemented("client_logger &client_logger::operator=(client_logger &&other) noexcept", "your code should be here...");
}

client_logger::~client_logger() noexcept
{
    auto iterPaths = _severities.begin();
    while(iterPaths != _severities.end()) {
        encrementStream(iterPaths);
        ++iterPaths;
    }

    //throw not_implemented("client_logger::~client_logger() noexcept", "your code should be here...");
}

logger const *client_logger::log(
    const std::string &text,
    logger::severity severity) const noexcept
{
    throw not_implemented("logger const *client_logger::log(const std::string &text, logger::severity severity) const noexcept", "your code should be here...");
}