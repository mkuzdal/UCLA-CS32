/** @file: IntelWeb.h */

#ifndef INTELWEB_H_
#define INTELWEB_H_

#include "InteractionTuple.h"
#include "DiskMultiMap.h"
#include <string>
#include <vector>
#include <unordered_map>

class IntelWeb
{
public:
    
    /** Constructor for the intel web class. */
    IntelWeb();
    
    /** Destructor for the intel web class. */
    ~IntelWeb();
    
    /** Creates new files for the IntelWeb to perform its actions on.
        @Param: filePrefix: The prefix for the file name to be created.
        @Param: maxDataItems: The expected number of telemetry items to be insert.
        @Post: If successful, 2 files are created and open for the forward and reverse logs. 
               Otherwise no files are open.
        @Return: True if the creation of the files was successful and they are ready to be used, and false otherwise. */
    bool createNew(const std::string& filePrefix, unsigned int maxDataItems);
    
    /** Opens an existing set of files for the IntelWeb to perform its actions on.
        @Pre: The files with the filePrefix exist and are ready to be open
        @Param: filePrefix: The prefix for the file names to be open
        @Post: If successful, the 2 files with the prefix are open and ready to be used. 
               Otherwise no files are open and the current files were close
        @Return: True if the files were opened succesfully (i.e., they both exist). 
                 Otherwise false and no changed made. */
    bool openExisting(const std::string& filePrefix);
    
    /** Closes the files currently being used by the intelWeb class */
    void close();
    
    /** Insertes a list of telemetryData into the log files.
        @Pre: Both of the log files currently being used are open and ready for use.
        @Param: telemetryFile: The name of the file in which to insert the telemetry logs.
        @Post: The forwards and reverse log files contain all of the data from the telemetry log.
        @Return: True if the insertion was succesful (i.e., the telemetry file was read in succesfully).
                 Otherwise false. */
    bool ingest(const std::string& telemetryFile);
    
    /** Goes through the telemetry data and records any malicious entities and interactions between objects.
        @Pre: The telemetry data to crawl through has already been ingested.
        @Param: indicators: The list of the initial malicious entitities.
        @Param: minPrevelanceToBeGood: The minimum amount of times a file/URL has to exist to be considered good.
        @Param: badEntitiesFound: The vector that will contain all of the found malicious entitites.
        @Param: interactions: The vector that will contain all of the unique malicious interactions.
        @Post: Both the interactions and badEntitiesFound vectors will be filled up in lexographical order based on the data.
        @Return: The number of malicious entities discovered while crawling. */
    unsigned int crawl(const std::vector<std::string>& indicators,
                       unsigned int minPrevalenceToBeGood,
                       std::vector<std::string>& badEntitiesFound,
                       std::vector<InteractionTuple>& interactions);
    
    /** Removes all entities of a given key from the logs.
        @Pre: The telemety data to purge has already been ingested.
        @Param: entitiy: The name of the object one wishes to remove.
        @Post: The file has been purged of all interactions containing the entitity.
        @Return: True if at least one deletion was made. Otherwise false. */
    bool purge(const std::string& entity);
    
private:
    
    DiskMultiMap m_Logs;                        // Disk-based data structure to store all "from-to" interactions
    DiskMultiMap m_LogsReverse;                 // Disk-based data structure to store all "to-from" interactions
    unsigned int m_minPrevalenceToBeGood;       // used to calculate P values
    
    /** Used to store / determine whether or not an entity is malicious.
        @Post: m_P keeps a reference to whether or not the entity is malicious or good.
        @Param: s: The name of the entity to check.
        @Param: map: the unordered map in which to store the p-values.
        @Return: True if the entity is not malicious, false otherwise. */
    bool P(const std::string& s, std::unordered_map<std::string, bool>& map,
           const std::vector<std::string>&indicator)
    {
        std::unordered_map<std::string, bool>::iterator MI;
        MI = map.find(s);
        if (MI == map.end())
        {
            for (int i = 0; i < indicator.size(); i++)
                if (indicator[i] == s)
                {
                    std::pair<std::string, bool> toInsert(s, false);
                    map.insert(toInsert);
                    return false;
                } // end if
            
            int count = 0;
            DiskMultiMap::Iterator DI = m_Logs.search(s);
            for (; count < m_minPrevalenceToBeGood && DI.isValid(); count++, ++DI)
                ;
            DiskMultiMap::Iterator DI2 = m_LogsReverse.search(s);
            for (; count < m_minPrevalenceToBeGood && DI2.isValid(); count++, ++DI2)
                ;
            if (count >= m_minPrevalenceToBeGood)
            {
                std::pair<std::string, bool> toInsert(s, true);
                map.insert(toInsert);
                return true;
            } else
            {
                std::pair<std::string, bool> toInsert(s, false);
                map.insert(toInsert);
                return false;
            } // end if-else
        } else
            return MI->second;
    } // end P
    
    /** Used to store / determine whether or not an entity should be stored in the indicators vector.
        @Post: m_Inserted keeps a reference to whether or not the entity needs to be stored.
        @Param: s: The name of the entity to check.
        @Param: map1: The map in which to store whether or not the entity has already been insert.
        @Param: map2: The map of p-values.
        @Return: True if the entity should be inserted, false otherwise. */
    bool shouldInsertEntity(const std::string& s,
                            std::unordered_map<std::string, bool>& map1,
                            std::unordered_map<std::string, bool>& map2,
                            const std::vector<std::string>& indicators)
    {
        if (P(s, map2, indicators))
            return false;
        std::unordered_map<std::string, bool>::iterator MI;
        MI = map1.find(s);
        if (MI == map1.end())
        {
            std::pair<std::string, bool> toInsert(s, false);
            map1.insert(toInsert);
            return true;
        } else
            return MI->second;
    } // end shouldInsertEntity
    
    /** Used to determine whether or not an interaction between two entities needs to be stores into the interactions vector.
        @Param: IT: The from-to interaction to check.
        @Param: interaction: The vector of already occured interactions.
        @Return: True if the interaction should be inserted, false otherwise. */
    bool shouldInsertInteraction(InteractionTuple IT, std::vector<InteractionTuple>& interactions)
    {
        for (int i = 0; i < interactions.size(); i++)
            if (IT.to == interactions[i].to && IT.from == interactions[i].from
                && IT.context == interactions[i].context)
                return false;
        return true;
    } // end shouldInsertInteraction
    
}; // end IntelWeb

#endif // INTELWEB_H_