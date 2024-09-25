#include <not_implemented.h>

#include "../include/client_logger.h"
#include <fstream>
#include <exception>
#include <ios>
std::map<std::string, client_logger::stream> client_logger::_streams = std::map<std::string, client_logger::stream>();
client_logger::stream::stream(std::string const &path) :
    _str(nullptr),
    _countOfLogers(1)
{
    try {
        _str = new std::ofstream;
        _str->open(path, std::ios::app);
        if(!_str->is_open()) {
            delete _str;
            _str = nullptr;
            throw std::logic_error("File open error");
        }
    }
    catch (std::bad_alloc const &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
    catch (std::exception const &e) {
        delete _str;
        _str = nullptr;
        std::cerr << e.what() << std::endl;
        throw e;
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
        _str->flush();
        _str->close();
        delete _str;
        _str = other._str;
        _countOfLogers = other._countOfLogers;
        other._str = nullptr;
        other._countOfLogers = 0;
    }
    return *this;
}

std::ostream &client_logger::stream::operator<<(std::string const &str) const {
    return (*_str << str).flush();
}

client_logger::stream::~stream() {
    _countOfLogers = 0;
    if (_str != nullptr) {
        _str->flush();
        _str->close();
        delete _str;
    }
    _str = nullptr;
}

client_logger::client_logger(std::map<std::string, unsigned char> const &map, std::string const &outputFormat) :
_severities(map),
_outputFormat(outputFormat)
{
    if(map.empty()) throw std::logic_error("map cant be empty");
    if(outputFormat.empty()) throw std::logic_error("Format cant be empty");
    auto iterPaths = map.begin();
    while(iterPaths != map.end()) {
        if(iterPaths->first == "cerr") {
            ++iterPaths;
            continue;
        }
        auto iterStreams = _streams.find(iterPaths->first);
        if(iterStreams != _streams.end()) {
            ++(iterStreams->second._countOfLogers);
        }else {
            _streams.emplace(iterPaths->first, stream(iterPaths->first));
        }
        ++iterPaths;
    }
}

void client_logger::decrementStream(std::map<std::string, unsigned char>::iterator &iterPaths) {
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
#include <iomanip>
std::string client_logger::current_date_to_string() noexcept
{
    auto time = std::time(nullptr);

    std::ostringstream result_stream;
    result_stream << std::put_time(std::localtime(&time), "%H:%M:%S");

    return result_stream.str();
}

std::string client_logger::current_time_to_string() noexcept
{
    auto time = std::time(nullptr);

    std::ostringstream result_stream;
    result_stream << std::put_time(std::localtime(&time), "%d.%m.%Y");

    return result_stream.str();
}

std::string client_logger::getOutputString(std::string const &message, logger::severity severity) const {
    std::string res;
    auto ptr = _outputFormat.begin();
    while(ptr != _outputFormat.end()) {
        if(*ptr == '%') {
            ++ptr;
            if(ptr == _outputFormat.end()) throw std::logic_error("Format error!");
            switch (*ptr) {
                case 'd':
                    res += current_date_to_string();
                    break;
                case 't':
                    res += current_time_to_string();
                    break;
                case 's':
                    res += logger::severity_to_string(severity);
                    break;
                case 'm':
                    res += message;
                    break;
                default:
                    throw std::logic_error("Unknown modificator");
                    break;
            }
        }else res.push_back(*ptr);
        ++ptr;
    }
    return res;
}

void client_logger::checkUniqueFile(client_logger const &other) {
    auto iterSeverity = _severities.begin();
    while(iterSeverity != _severities.end()) {
        if(other._severities.find(iterSeverity->first) == other._severities.end()) {
            decrementStream(iterSeverity);
        }
        ++iterSeverity;
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
        checkUniqueFile(other);
        _severities = other._severities;
        _outputFormat = other._outputFormat;
    }
    return *this;
    //throw not_implemented("client_logger &client_logger::operator=(client_logger const &other)", "your code should be here...");
}

client_logger::client_logger(
    client_logger &&other) noexcept :
_severities(std::move(other._severities)),
_outputFormat(std::move(other._outputFormat))
{
    //throw not_implemented("client_logger::client_logger(client_logger &&other) noexcept", "your code should be here...");
}

client_logger &client_logger::operator=(
    client_logger &&other) noexcept
{
    if(this != &other) {
        checkUniqueFile(other);
        _severities = std::move(other._severities);
        _outputFormat = std::move(other._outputFormat);
    }
    return *this;
    //throw not_implemented("client_logger &client_logger::operator=(client_logger &&other) noexcept", "your code should be here...");
}

client_logger::~client_logger() noexcept
{
    auto iterPaths = _severities.begin();
    while(iterPaths != _severities.end()) {
        decrementStream(iterPaths);
        ++iterPaths;
    }

    //throw not_implemented("client_logger::~client_logger() noexcept", "your code should be here...");
}

logger const *client_logger::log(
    const std::string &text,
    logger::severity severity) const noexcept
{
    auto iterSev = _severities.begin();
    while(iterSev != _severities.end()) {
        if(((iterSev->second) >> static_cast<int>(severity)) & 1) {
            if(iterSev->first == "cerr") {
                std::cerr << getOutputString(text, severity) << std::endl;
                ++iterSev;
                continue;
            }
            auto &target_stream = _streams.find(iterSev->first)->second;
            target_stream << getOutputString(text, severity) << std::endl;
            target_stream._str->flush();
            //_streams.find(iterSev->first)->second._str->flush();
            //*((_streams.find(iterSev->first))->second._str) << 's' << std::endl;
            // *((_streams.find(iterSev->first))->second._str) << getOutputString(text, severity) << std::endl;
        }
        ++iterSev;
    }
    return this;
    //throw not_implemented("logger const *client_logger::log(const std::string &text, logger::severity severity) const noexcept", "your code should be here...");
}