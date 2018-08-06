// Copyright (c) 2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_ZMQ_ZMQPUBLISHER_H
#define BITCOIN_ZMQ_ZMQPUBLISHER_H

#include "zmqabstract.h"
#include "univalue.h"

class CBlockIndex;

class CZMQAbstractPublisher : public CZMQAbstract
{
public:
    bool processTransaction(const CTransaction &transaction);

    bool Initialize();
    void Shutdown();

    bool Execute();
    bool Publish();

    virtual void SetMethod() = 0;
    virtual void SetTopic() = 0;

protected:
    std::string method;
    UniValue request;
    UniValue publish;

};

/* Event classes. Each one is a specific notifier in ValidationInterface */
class CZMQBlockEvent : public CZMQAbstractPublisher
{
    /* Data related to a new block (updatedblocktip)
    */
public:
    bool NotifyBlock(const CBlockIndex *pindex);
};


class CZMQRawTransactionEvent : public CZMQAbstractPublisher
{
    /* Data related to a new transaction
    */
public:
    bool NotifyTransaction(const CTransaction &transaction);
};

/* Topics. inheriting from an event class implies publishing on that event. 
   'method' string is the API method called in client-api/ 
*/
class CZMQBlockDataTopic : public CZMQBlockEvent
{
public:
    void SetTopic(){ topic = "address";};
    void SetMethod(){ method= "block";};
    
};

class CZMQBlockInfoTopic : public CZMQBlockEvent
{
public:
    void SetTopic(){ topic = "block";};
    void SetMethod(){ method= "blockchain";};
    
};

class CZMQBalanceTopic : public CZMQBlockEvent
{
public:
    void SetTopic(){ topic = "balance";};
    void SetMethod(){ method= "balance";};
};

class CZMQTransactionTopic : public CZMQRawTransactionEvent
{
public:
    void SetTopic(){ topic = "transaction";};
    void SetMethod(){ method= "transaction";};
};



class CZMQSettingsUpdatePublisher : public CZMQAbstractPublisher
{
public:
    bool NotifySettingsUpdate();
    void SetMethod(){ method= "settings";};
    void SetTopic(){ topic = "settings";};
};

#endif // BITCOIN_ZMQ_ZMQPUBLISHER_H
