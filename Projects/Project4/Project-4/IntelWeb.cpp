/** @file: IntelWeb.cpp */

#include "IntelWeb.h"
#include "InteractionTuple.h"
#include "MultiMapTuple.h"
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

/** Greater than operation for the InteractionTuple class.
    @Param: lhs: The left hand side of the operation.
    @Param: rhs: The right hand side of the operation.
    @Return: True if lhs should come before rhs in sorted order. */
bool L(const InteractionTuple& lhs, const InteractionTuple& rhs)
{
    // if the context of the left is less than the right return true;
    if (lhs.context < rhs.context) return true;
    // otherwise return false
    else if (lhs.context > rhs.context) return false;
    // if they are equal, check the 'from' data member
    else if (lhs.from < rhs.from) return true;
    else if (lhs.from > rhs.from) return false;
    // if they are still equal, then check the 'to' data member
    else if (lhs.to < rhs.to) return true;
    else return false;
} // end GreaterThan operator

IntelWeb::IntelWeb(): m_minPrevalenceToBeGood(0)
{
} // end constructor

IntelWeb::~IntelWeb()
{
    // simply close the logs
    m_Logs.close();
    m_LogsReverse.close();
} // end destructor

bool IntelWeb::createNew(const std::string& filePrefix, unsigned int maxDataItems)
{
    // close the previous logs
    m_Logs.close();
    m_LogsReverse.close();
    // create the forwards log
    if(!m_Logs.createNew(filePrefix + "-logs", (4*maxDataItems/3)+1))
        return false;
    
    // create the reverse log
    if(!m_LogsReverse.createNew(filePrefix + "-logsR", 4*maxDataItems/3))
    {
        // if failed, close the already open forwards log
        m_Logs.close();
        return false;
    } // end if
    return true;
} // end createNew

bool IntelWeb::openExisting(const std::string& filePrefix)
{
    // close the previous logs
    m_Logs.close();
    m_LogsReverse.close();
    
    // open the forwards log
    if(!m_Logs.openExisting(filePrefix + "-logs"))
        return false;
    
    // open the reverse log
    if(!m_LogsReverse.openExisting(filePrefix + "-logsR"))
    {
        // if failed, close the already open forwards log
        m_Logs.close();
        return false;
    } // end if
    return true;
} // end openExisting

void IntelWeb::close()
{
    // close the logs
    m_Logs.close();
    m_LogsReverse.close();
} // end close

bool IntelWeb::ingest(const std::string& telemetryFile)
{
    // create an ifstream for the file
    std::ifstream infile(telemetryFile);
    if (!infile)
        return false;

    std::string K, V, C;
    // loop through the file
    while (infile >> C >> K >> V)
    {
        // insert every key-value-context pair into the forwards log...
        m_Logs.insert(K, V, C);
        // and every value-key-context pair into the reverse log.
        m_LogsReverse.insert(V, K, C);
    } // end while
    return true;
} // end ingest

unsigned int IntelWeb::crawl(const std::vector<std::string>& indicators,
                             unsigned int minPrevalenceToBeGood,
                             std::vector<std::string>& badEntitiesFound,
                             std::vector<InteractionTuple>& interactions)
{
    std::unordered_map<std::string, bool> P;        // Cache for determining P values
    std::unordered_map<std::string, bool> Inserted; // Cache for determining if needs to be inserted or not
    m_minPrevalenceToBeGood = minPrevalenceToBeGood;
    // clear both of the vectors
    badEntitiesFound.clear();
    interactions.clear();
    std::queue<std::string> queue;
    // push all of the indicators onto the queue
    for (int i = 0; i < indicators.size(); i++)
        queue.push(indicators[i]);
    while (!queue.empty())
    {
        // get an item
        std::string MaliciousEntity = queue.front();
        queue.pop();
        DiskMultiMap::Iterator I = m_Logs.search(MaliciousEntity);
        DiskMultiMap::Iterator IR = m_LogsReverse.search(MaliciousEntity);
        // if the item exists in the map, and should be inserted into the vector (based on its p-value)
        if ((I.isValid() || IR.isValid()) &&
            shouldInsertEntity(MaliciousEntity, Inserted, P, indicators))
            // insert it into the vector
            badEntitiesFound.push_back(MaliciousEntity);
        // now check all of the value's that interacted with the given key
        while (I.isValid())
        {
            MultiMapTuple MMT = *I;
            // if they haven't been check already...
            if (shouldInsertEntity(MMT.value, Inserted, P, indicators))
            {
                // push them onto the vector and queue
                badEntitiesFound.push_back(MMT.value);
                queue.push(MMT.value);
            } // end if
            InteractionTuple IT(MMT.key, MMT.value, MMT.context);
            if (shouldInsertInteraction(IT, interactions))
                interactions.push_back(IT);
            ++I;
        } while (IR.isValid())
        {
            MultiMapTuple MMT = *IR;
            if (shouldInsertEntity(MMT.value, Inserted, P, indicators))
            {
                badEntitiesFound.push_back(MMT.value);
                queue.push(MMT.value);
            } // end if
            InteractionTuple IT(MMT.value, MMT.key, MMT.context);
            if (shouldInsertInteraction(IT, interactions))
                interactions.push_back(IT);
            ++IR;
        } // end while
    } // end while
    
    // sort the vectors
    std::sort(badEntitiesFound.begin(), badEntitiesFound.end());
    std::sort(interactions.begin(), interactions.end(), L);
    return badEntitiesFound.size();
} // end crawl

bool IntelWeb::purge(const std::string& entity)
{
    bool toReturn = false;
    DiskMultiMap::Iterator I = m_Logs.search(entity);
    DiskMultiMap::Iterator IR = m_LogsReverse.search(entity);
    // if the key exists somewhere in the map
    if (I.isValid() || IR.isValid())
        toReturn = true;
    // erase all forwards and reverse interactions
    while (I.isValid())
    {
        MultiMapTuple MMT = *I;
        m_Logs.erase(MMT.key, MMT.value, MMT.context);
        m_LogsReverse.erase(MMT.value , MMT.key, MMT.context);
        I = m_Logs.search(entity);
    } while (IR.isValid())
    {
        MultiMapTuple MMT = *IR;
        m_LogsReverse.erase(MMT.key, MMT.value, MMT.context);
        m_Logs.erase(MMT.value, MMT.key, MMT.context);
        IR = m_Logs.search(entity);
    } // end while
    return toReturn;
} // end purge
