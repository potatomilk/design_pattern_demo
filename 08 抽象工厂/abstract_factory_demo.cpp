#include <iostream>

namespace Lib {
    // 基类
    class IDBConnect {
    public:
        virtual void connect() = 0;
    };
    class IDBCommand {
    public:
        virtual void exec() = 0;
    };
    class IDBDataReader {
    public:
        virtual void read() = 0;
    };

    // 工厂基类
    class IDBConnectFactory {
    public:
        virtual IDBConnect* create() = 0;
    };
    class IDBCommandFactory {
    public:
        virtual IDBCommand* create() = 0;
    };
    class IDBDataReaderFactory {
    public:
        virtual IDBDataReader* create() = 0;
    };

    // 合并为一个工厂
    class IDBAbstractFactory {
    public:
        virtual IDBConnect* CreateDbConnect() = 0;
        virtual IDBCommand* CreateDbCommand() = 0;
        virtual IDBDataReader* CreateDbDataReader() = 0;
    };

    // SqlServer数据库访问
    class SqlServerConnect : public IDBConnect {
    public:
        virtual void connect() {
            printf("SqlServer Connect.\n");
        }
    };
    class SqlServerCommand : public IDBCommand {
    public:
        virtual void exec() {
            printf("SqlServer Command.\n");
        }
    };
    class SqlServerDataReader : public IDBDataReader {
    public:
        virtual void read() {
            printf("SqlServer Data Read.\n");
        }
    };
    // 具体工厂
    class SqlServerConnectFactory : public IDBConnectFactory {
    public:
        virtual IDBConnect* create() {
            return new SqlServerConnect();
        }
    };
    class SqlServerCommandFactory : public IDBCommandFactory {
    public:
        virtual IDBCommand* create() {
            return new SqlServerCommand();
        }
    };
    class SqlServerDataReaderFactory : public IDBDataReaderFactory {
    public:
        virtual IDBDataReader* create() {
            return new SqlServerDataReader();
        }
    };
    // 合并工厂
    class SqlServerFactory : public IDBAbstractFactory {
    public:
        virtual IDBConnect* CreateDbConnect() {
            return new SqlServerConnect();
        }
        virtual IDBCommand* CreateDbCommand() {
            return new SqlServerCommand();
        }
        virtual IDBDataReader* CreateDbDataReader() {
            return new SqlServerDataReader();
        }
    };

    // MySql数据库访问
    class MySqlConnect : public IDBConnect {
    public:
        virtual void connect() {
            printf("MySql Connect.\n");
        }
    };
    class MySqlCommand : public IDBCommand {
    public:
        virtual void exec() {
            printf("MySql Command.\n");
        }
    };
    class MySqlDataReader : public IDBDataReader {
    public:
        virtual void read() {
            printf("MySql Data Read.\n");
        }
    };
    // 具体工厂
    class MySqlConnectFactory : public IDBConnectFactory {
    public:
        virtual IDBConnect* create() {
            return new MySqlConnect();
        }
    };
    class MySqlCommandFactory : public IDBCommandFactory {
    public:
        virtual IDBCommand* create() {
            return new MySqlCommand();
        }
    };
    class MySqlDataReaderFactory : public IDBDataReaderFactory {
    public:
        virtual IDBDataReader* create() {
            return new MySqlDataReader();
        }
    };

    class MySqlFactory : public IDBAbstractFactory {
    public:
        virtual IDBConnect* CreateDbConnect() {
            return new MySqlConnect();
        }
        virtual IDBCommand* CreateDbCommand() {
            return new MySqlCommand();
        }
        virtual IDBDataReader* CreateDbDataReader() {
            return new MySqlDataReader();
        }
    };
}

namespace App {
    class AlgoMo {
    public:
        // AlgoMo(Lib::IDBConnectFactory *dbConnFactory, Lib::IDBCommandFactory *dbCmdFactory,
        //     Lib::IDBDataReaderFactory *dbReaderFactory) : dbConnFactory(dbConnFactory),
        //     dbCmdFactory(dbCmdFactory), dbReaderFactory(dbReaderFactory){
        // }
        AlgoMo(Lib::IDBAbstractFactory *abf) : dbfactory(abf) {}
        void progress() {
            // 业务开始时使用SqlServer
            // Lib::SqlServerConnect *sqlConn =
            //     new Lib::SqlServerConnect();
            // Lib::SqlServerCommand *sqlCmd =
            //     new Lib::SqlServerCommand();
            // Lib::SqlServerDataReader *sqlDataReader =
            //     new Lib::SqlServerDataReader();

            // 后来切换到MySql
            // Lib::MySqlConnect *sqlConn =
            //     new Lib::MySqlConnect();
            // Lib::MySqlCommand *sqlCmd =
            //     new Lib::MySqlCommand();
            // Lib::MySqlDataReader *sqlDataReader =
            //     new Lib::MySqlDataReader();

            // 再后来，项目组可自定义数据库，如何解决？
            // 尝试：工厂方法；可能导致混合使用
            // Lib::IDBConnect *dbconn =
            //     dbConnFactory->create();
            // Lib::IDBCommand *dbcmd =
            //     dbCmdFactory->create();
            // Lib::IDBDataReader *dbreader =
            //     dbReaderFactory->create();

            // 抽象工厂模式
            Lib::IDBConnect *dbconn =
                dbfactory->CreateDbConnect();
            Lib::IDBCommand *dbcmd =
                dbfactory->CreateDbCommand();
            Lib::IDBDataReader *dbreader =
                dbfactory->CreateDbDataReader();

            dbconn->connect();
            dbcmd->exec();
            dbreader->read();
        }
    private:
        // Lib::IDBConnectFactory *dbConnFactory;
        // Lib::IDBCommandFactory *dbCmdFactory;
        // Lib::IDBDataReaderFactory *dbReaderFactory;
        Lib::IDBAbstractFactory *dbfactory;
    };
}

int main(int argc, char **argv) {
    printf("Abstract Factory Demo.\n");

    // App::AlgoMo algoSqlServer(new Lib::SqlServerConnectFactory(),
    //             new Lib::SqlServerCommandFactory(),
    //             new Lib::SqlServerDataReaderFactory());

    App::AlgoMo algoSqlServer(new Lib::SqlServerFactory());

    algoSqlServer.progress();

    // App::AlgoMo algoMySql(new Lib::MySqlConnectFactory(),
    //             new Lib::MySqlCommandFactory(),
    //             new Lib::MySqlDataReaderFactory());

    App::AlgoMo algoMySql(new Lib::MySqlFactory());

    algoMySql.progress();

    // 数据库中间件应该是一致性，此时就混用，错了
    // App::AlgoMo algoMySqlMixSqlServer(new Lib::MySqlConnectFactory(),
    //             new Lib::SqlServerCommandFactory(),
    //             new Lib::MySqlDataReaderFactory());

    // algoMySqlMixSqlServer.progress();

    // 那么有没有一种可能，保证一致性呢？即创建具有依赖关系的对象


    return 0;
}