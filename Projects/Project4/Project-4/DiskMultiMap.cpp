/** @file: DiskMultiMap.cpp */

#include "DiskMultiMap.h"
#include <string>

DiskMultiMap::DiskMultiMap()
: m_buckets(0)
{
} // end constructor

DiskMultiMap::~DiskMultiMap()
{
    m_BF.close();
} // end destructor

bool DiskMultiMap::createNew(const std::string& filename, unsigned int numBuckets)
{
    m_buckets = numBuckets;
    if (m_BF.isOpen())
        m_BF.close();
    if(m_BF.createNew(filename))
    {
        TableHeader T;
        T.numBuckets = numBuckets;
        T.ErasedKey = -1;
        T.ErasedMMT = -1;
        T.currentPosition = sizeof(TableHeader) + numBuckets*sizeof(Bucket_Node);
        m_BF.write(T, 0);
        for (int i = 0; i < numBuckets * sizeof(Bucket_Node); i += sizeof(Bucket_Node))
            m_BF.write(-1, i + sizeof(TableHeader));
        return true;
    } // end if
    return false;
} // end createNew

bool DiskMultiMap::openExisting(const std::string& filename)
{
    if (m_BF.isOpen())
        m_BF.close();
    if(m_BF.openExisting(filename))
    {
        m_BF.read(m_buckets, 0);
        return true;
    } // end if
    return false;
} // end openExisting

void DiskMultiMap::close()
{
    if (m_BF.isOpen())
        m_BF.close();
} // end DiskMultiMap

bool DiskMultiMap::insert(const std::string& key, const std::string& value, const std::string& context)
{
    if (key.size() > 120 || value.size() > 120 || context.size() > 120)
        return false;
    
    int h = hash(key);
    Bucket_Node B;
    m_BF.read(B, h);
    
    // If the bucketnode is currently empty...
    if (B.Offset == -1)
        InsertNodeAux(h, 1, key, value, context);
    // Otherwise...
    else
    {
        Key_Node tempKN;
        m_BF.read(tempKN, B.Offset);
        
        int cur = tempKN.Offset;
        int prev = -1;
        // Go through the keys...
        while (cur != -1)
        {
            m_BF.read(tempKN, cur);
            // If the key is already in the map, break out of the loop
            if (key.compare(tempKN.Key) == 0)
                break;
            prev = cur;
            cur = tempKN.NextKey;
        } // end while
        // If the key was not in the map...
        if (cur == -1)
            // Insert it.
            InsertNodeAux(prev, 2, key, value, context);
        // Otherwise...
        else
        {
            Key_Node KN;
            m_BF.read(KN, cur);
            KN.Count++;
            m_BF.write(KN, cur);
            
            MMT_Node MMT;
            MMT.NextMMT = -1;
            MMT.Key_Offset = KN.Offset;
            value.copy(MMT.Value, value.size(), 0);
            MMT.Value[value.size()] = '\0';
            context.copy(MMT.Context, context.size(), 0);
            MMT.Context[context.size()] = '\0';
            
            MMT_Node tempMMT;
            m_BF.read(tempMMT, KN.MMT_Offset);
            cur = tempMMT.Offset;
            prev = -1;
            
            // Go through the Multi-Map Tuples...
            while (cur != -1)
            {
                m_BF.read(tempMMT, cur);
                prev = cur;
                cur = tempMMT.NextMMT;
            } // end while
            
            MMT.PrevMMT = prev;
            TableHeader TH;
            m_BF.read(TH, 0);
            // Check to see if there is free memory...
            if (TH.ErasedMMT == -1)
            {
                MMT.Offset = TH.currentPosition;
                TH.currentPosition += sizeof(MMT_Node);
            } else
            {
                MMT_Node tempMMT;
                int prev = -1;
                m_BF.read(tempMMT, TH.ErasedMMT);
                while(tempMMT.NextMMT != -1)
                {
                    prev = tempMMT.Offset;
                    m_BF.read(tempMMT, tempMMT.NextMMT);
                }
                MMT.Offset = tempMMT.Offset;
                KN.MMT_Offset = MMT.Offset;
                if (prev == -1)
                {
                    TH.ErasedMMT = -1;
                } else
                {
                    m_BF.read(tempMMT, prev);
                    tempMMT.NextMMT = -1;
                    m_BF.write(tempMMT, prev);
                } // end if-else
            } // end if-else
            m_BF.write(TH, 0);
            m_BF.read(tempMMT, prev);
            tempMMT.NextMMT = MMT.Offset;
            MMT.PrevMMT = tempMMT.Offset;
            m_BF.write(MMT, MMT.Offset);
            m_BF.write(tempMMT, prev);
        } // end if-else
    } // end if-else
    return true;
} // end insert

DiskMultiMap::Iterator DiskMultiMap::search(const std::string& key)
{
    int h = hash(key);
    Bucket_Node B;
    m_BF.read(B, h);
    if (B.Offset == -1)
    {
        Iterator it;
        return it;
    } else
    {
        Key_Node KN;
        m_BF.read(KN, B.Offset);
        int cur = KN.Offset;
        while (cur != -1)
        {
            m_BF.read(KN, cur);
            // If the key is already in the map, break out of the loop
            if (key.compare(KN.Key) == 0)
                break;
            cur = KN.NextKey;
        } // end while
        if (cur == -1)
        {
            Iterator it;
            return it;
        } else
        {
            MMT_Node MMT;
            m_BF.read(MMT, KN.MMT_Offset);
            Iterator it(MMT.Offset, &m_BF);
            return it;
        } // end if-else
    } // end if-else
} // end search

int DiskMultiMap::erase(const std::string& key, const std::string& value, const std::string& context)
{
    if (key.size() > 120 || value.size() > 120 || context.size() > 120)
        return 0;
    
    int count = 0;
    int h = hash(key);
    Bucket_Node B;
    m_BF.read(B, h);
    
    if (B.Offset == -1)
        return count;
    
    Key_Node tempKN;
    m_BF.read(tempKN, B.Offset);
        
    int cur = tempKN.Offset;
    int prev = -1;
    // Go through the keys...
    while (cur != -1)
    {
        m_BF.read(tempKN, cur);
        // If the key is  in the map, break out of the loop
        if (key.compare(tempKN.Key) == 0)
            break;
        prev = cur;
        cur = tempKN.NextKey;
    } // end while
    // If the key was not in the map...
    if (cur == -1)
        return count;
    // Otherwise...
    
    Key_Node KN;
    m_BF.read(KN, cur);
    TableHeader TH;
    m_BF.read(TH, 0);
    MMT_Node MMT;
    m_BF.read(MMT, KN.MMT_Offset);
    cur = MMT.Offset;
    
    // Go through the Multi-Map Tuples...
    while (cur != -1)
    {
        m_BF.read(MMT, cur);
        cur = MMT.NextMMT;
        if(value.compare(MMT.Value) == 0 && context.compare(MMT.Context) == 0)
        {
            count++;
            KN.Count--;
            MMT_Node tempMMT;
            if (MMT.PrevMMT == -1)
            {
                KN.MMT_Offset = MMT.NextMMT;
                if (MMT.NextMMT != -1)
                {
                    m_BF.read(tempMMT, MMT.NextMMT);
                    tempMMT.PrevMMT = MMT.PrevMMT;
                    m_BF.write(tempMMT, tempMMT.Offset);
                } // end if
                m_BF.write(KN, KN.Offset);
            }else
            {
                m_BF.read(tempMMT, MMT.PrevMMT);
                tempMMT.NextMMT = MMT.NextMMT;
                m_BF.write(tempMMT, tempMMT.Offset);
                if (MMT.NextMMT != -1)
                {
                    m_BF.read(tempMMT, MMT.NextMMT);
                    tempMMT.PrevMMT = MMT.PrevMMT;
                    m_BF.write(tempMMT, tempMMT.Offset);
                } // end if
            } // end if-else
            
            if (TH.ErasedMMT == -1)
            {
                TH.ErasedMMT = MMT.Offset;
                MMT.NextMMT = -1;
                m_BF.write(TH, 0);
                m_BF.write(MMT, MMT.Offset);
            } else
            {
                m_BF.read(tempMMT, TH.ErasedMMT);
                while (tempMMT.NextMMT != -1)
                   m_BF.read(tempMMT, tempMMT.NextMMT);
                tempMMT.NextMMT = MMT.Offset;
                MMT.NextMMT = -1;
                m_BF.write(MMT, MMT.Offset);
                m_BF.write(tempMMT, tempMMT.Offset);
            } // end if-else
        } // end if
    } // end while
    
    if (KN.Count <= 0)
    {
        if (KN.PrevKey == -1)
        {
            B.Offset = KN.NextKey;
            if (KN.NextKey != -1)
            {
                m_BF.read(tempKN, KN.NextKey);
                tempKN.PrevKey = KN.PrevKey;
                m_BF.write(tempKN, tempKN.Offset);
            } // end if
            m_BF.write(KN.NextKey, h);
        }
        else
        {
            m_BF.read(tempKN, KN.PrevKey);
            tempKN.NextKey = KN.NextKey;
            m_BF.write(tempKN, tempKN.Offset);
            if (KN.NextKey != -1)
            {
                m_BF.read(tempKN, KN.NextKey);
                tempKN.PrevKey = KN.PrevKey;
                m_BF.write(tempKN, tempKN.Offset);
            } // end if
        } // end if-else
        
        if (TH.ErasedKey == -1)
        {
            TH.ErasedKey = KN.Offset;
            KN.NextKey = -1;
            m_BF.write(TH, 0);
            m_BF.write(KN, KN.Offset);
        } else
        {
            m_BF.read(tempKN, TH.ErasedKey);
            while (tempKN.NextKey != -1)
                m_BF.read(tempKN, tempKN.NextKey);
            tempKN.NextKey = KN.Offset;
            KN.NextKey = -1;
            m_BF.write(KN, KN.Offset);
            m_BF.write(tempKN, tempKN.Offset);
        } // end if-else
    } // end if
    return count;
} // end erase
