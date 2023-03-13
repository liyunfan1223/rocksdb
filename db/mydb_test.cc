#include <gtest/gtest.h>
#include <iostream>

#include "env/mock_env.h"
#include "rocksdb/options.h"
#include "test_util/testutil.h"
#include "db/db_test_util.h"

namespace ROCKSDB_NAMESPACE {

class MYDBTest : public DBTestBase {
 public:
  MYDBTest() : DBTestBase("mydb_test", false) {}
};

TEST(MYDBTest, Environment) {
  Env* env = rocksdb::Env::Default();
  EnvOptions env_options;
  std::string trace_path = "/tmp/binary_trace_test_example";
  std::unique_ptr<TraceWriter> trace_writer;
  DB* db = nullptr;
  std::string db_name = "/tmp/rocksdb";

  /*Create the trace file writer*/
  NewFileTraceWriter(env, env_options, trace_path, &trace_writer);
  // std::unique_ptr<MockEnv> mock_env{MockEnv::Create(Env::Default())};
  Options options;
  options.create_if_missing = true;
  // options.env = mock_env.get();
  DB::Open(options, db_name, &db);
  TraceOptions trace_opt;
  /*Start tracing*/
  db->StartBlockCacheTrace(trace_opt, std::move(trace_writer));

  /* Your call of RocksDB APIs */

  /*End tracing*/
  db->EndBlockCacheTrace();
}

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    RegisterCustomObjects(argc, argv);
    return RUN_ALL_TESTS();
}