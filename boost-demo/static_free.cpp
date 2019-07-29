/*************************************************************************
	> File Name: static_free.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 22 Jul 2019 02:33:16 AM CDT
 ************************************************************************/

#include <iostream>
#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>


class Client
{
public:
    Client() {std::cout << " +++ client." << std::endl;}
    ~Client() {std::cout << " --- client." << std::endl;}

    static bool addClient(Client* cli) {
        std::cout << " add client." << std::endl;
        mClients.insert(std::make_pair(cli, boost::shared_ptr<Client>(cli)));
    }

    static bool delClient(Client* cli) {
        std::cout << " del client." << std::endl;
        mClients.erase(cli);
    }

private:
    static std::map<Client*, boost::shared_ptr<Client> > mClients;
};
std::map<Client*, boost::shared_ptr<Client> > Client::mClients;


class UseClient
{
public:
    UseClient() {
        std::cout << " +++ UseClient." << std::endl;
        mCli = new Client;
        Client::addClient(mCli);
    }
    ~UseClient() {
        std::cout << " --- UseClient." << std::endl;
        //Client::delClient(mCli);
    }

private:
    Client *mCli;
};


class Engine
{
public:
    Engine() {std::cout << " +++ Engine." << std::endl;}
    ~Engine() {std::cout << " --- Engine." << std::endl;}

    boost::shared_ptr<UseClient> getClient() {
        if (mClientObjs.size() > 3) {
            return mClientObjs[0];
        }
        else {
            boost::shared_ptr<UseClient> uc(new UseClient);
            mClientObjs.push_back(uc);
            return uc;
        }
    }

private:
    std::vector< boost::shared_ptr<UseClient> > mClientObjs;
};

//g++ static_free.cpp -std=c++11 -I /usr/local/include/ -L /usr/local/lib/
int main()
{
    std::cout << " ------------- main beg --------- " << std::endl;
    //{
    //    Client *c1 = new Client;
    //    c1->addClient(c1);
    //}
    //{
    //    Client *c1 = new Client;
    //    c1->addClient(c1);
    //}
    Engine eg;
    eg.getClient();
    eg.getClient();
    eg.getClient();
    eg.getClient();

    std::cout << " ------------- main end --------- " << std::endl;
    exit(0);
    _exit(0);
    return 0;
}

