#include <gtest/gtest.h>

#include <client_logger.h>


int main(
    int argc,
    char *argv[])
{
    client_logger_builder b;
    b.add_file_stream("crit.txt", logger::severity::critical);
    b.add_file_stream("debug.txt", logger::severity::debug);
    b.add_file_stream("debug2.txt", logger::severity::debug);
    b.add_file_stream("warn.txt", logger::severity::warning);
    b.add_console_stream(logger::severity::warning);
    b.add_console_stream(logger::severity::debug);
    b.add_output_format("[%t %d %s] %m");
    auto l = b.build(), l1 = b.build();
    l->log("crit", logger::severity::critical);
    l->log("crit", logger::severity::debug)
        /*->log("deb", logger::severity::debug)
        ->log("war", logger::severity::warning)*/;
    delete l1;
    delete l;
    return 0;
    /*testing::InitGoogleTest(&argc, argv);
    
    return RUN_ALL_TESTS();*/
}