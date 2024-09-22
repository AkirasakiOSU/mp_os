#ifndef MATH_PRACTICE_AND_OPERATING_SYSTEMS_CLIENT_LOGGER_H
#define MATH_PRACTICE_AND_OPERATING_SYSTEMS_CLIENT_LOGGER_H

#include <logger.h>
#include "client_logger_builder.h"

class client_logger final:
    public logger
{
    friend client_logger_builder;
public:
    struct stream {
        std::ofstream *_str;
        size_t _countOfLogers;

        explicit stream(std::string const &);
        stream(stream const &) = delete;
        stream(stream &&) noexcept;
        ~stream();
        stream &operator=(stream const &) = delete;
        stream &operator=(stream &&) noexcept;
    };
private:


    static std::map<std::string, stream> _streams;
    std::map<std::string, unsigned char> _severities;


    explicit client_logger(std::map<std::string, unsigned char> const &);

    static void encrementStream(std::map<std::string, unsigned char>::iterator &);

public:

    client_logger(
        client_logger const &other);

    client_logger &operator=(
        client_logger const &other);

    client_logger(
        client_logger &&other) noexcept;

    client_logger &operator=(
        client_logger &&other) noexcept;

    ~client_logger() noexcept override;

public:

    [[nodiscard]] logger const *log(
        const std::string &message,
        logger::severity severity) const noexcept override;

};

#endif //MATH_PRACTICE_AND_OPERATING_SYSTEMS_CLIENT_LOGGER_H