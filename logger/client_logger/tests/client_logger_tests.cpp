#include <gtest/gtest.h>

#include <client_logger.h>

int main(
    int argc,
    char *argv[])
{
    client_logger_builder b;
    b.add_file_stream("crit.txt", logger::severity::critical);
    // b.add_file_stream("debug.txt", logger::severity::debug);
    // b.add_file_stream("debug2.txt", logger::severity::debug);
    // b.add_file_stream("warn.txt", logger::severity::warning);
    b.add_console_stream(logger::severity::critical);
    // b.add_console_stream(logger::severity::debug);
    b.add_output_format("[%t %d %s] %m");
    auto l2 = b.build();
    l2->log("crit1", logger::severity::critical);
    //_sleep(2000);
    l2->log("crit2", logger::severity::critical);
        /*->log("deb", logger::severity::debug)
        ->log("war", logger::severity::warning)#1#;
    //delete l1;
    return 0;
    /*testing::InitGoogleTest(&argc, argv);
    
    return RUN_ALL_TESTS();*/
    delete l2;

    return 0;
}
