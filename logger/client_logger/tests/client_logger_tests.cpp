#include <gtest/gtest.h>

#include <client_logger.h>

int main(
    int argc,
    char *argv[])
{
    client_logger_builder b;
    b.transform_with_configuration("test.json", "data");
    b.add_output_format("[%t %d %s] %m");
    auto l2 = b.build();

    delete l2;

    return 0;
}
