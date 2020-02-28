#include "gmock/gmock.h"  // Google mock
#include "gtest/gtest.h"

#include <string>

class TableMgr {
public:
    virtual std::string GetAuthorizeToken(const std::string& unique_id) = 0;
};

class Client {
public:
    Client(TableMgr* table_mgr) : table_mgr_(table_mgr) {}

    virtual ~Client() = default;

    std::string GetAuthorizeToken(const std::string& unique_id) {
        return table_mgr_->GetAuthorizeToken(unique_id);
    }

private:
    TableMgr* table_mgr_;
};

// TableMgr 的 mock 类
class MockTableMgr : public TableMgr {
public:
    // mock GetAuthorizeToken
    MOCK_METHOD(std::string, GetAuthorizeToken, (const std::string& unique_id), (override));
};

class ClientTestFixture : public ::testing::Test {

};

TEST_F(ClientTestFixture, GetAuthorizeToken) {
    MockTableMgr mock_table_mgr;
    Client client(&mock_table_mgr);
    EXPECT_CALL(mock_table_mgr, GetAuthorizeToken(::testing::_))
        .Times(1)
        .WillOnce(
            ::testing::DoAll(::testing::Return("ASDF"))  // 指定返回值为 "ASDF"
         );
    EXPECT_EQ(client.GetAuthorizeToken("123"), "ASDF");
}

