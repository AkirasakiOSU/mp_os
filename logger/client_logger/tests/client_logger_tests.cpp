#include <gtest/gtest.h>

#include <client_logger.h>


int main(
    int argc,
    char *argv[])
{
    client_logger_builder b;
    b.add_file_stream("file.txt", logger::severity::critical);
    auto l = b.build(), l1 = b.build();
    delete l1;
    delete l;
    return 0;
    /*testing::InitGoogleTest(&argc, argv);
    
    return RUN_ALL_TESTS();*/
}