/** @file: DiskMultiMap.h */

#ifndef DISKMULTIMAP_H_
#define DISKMULTIMAP_H_

#include <string>
#include "MultiMapTuple.h"
#include "BinaryFile.h"
#include <iostream>

class DiskMultiMap
{
public:

    class Iterator
    {
    public:
        Iterator()
        : m_isValid(false), m_BF(nullptr), m_position(-1)
        {}
        
        Iterator(BinaryFile::Offset Position, BinaryFile* BF)
        : m_isValid(true), m_BF(BF), m_position(Position)
        {}
        
        bool isValid() const
        {
            return m_isValid;
        } // end isValid
        
        Iterator& operator++()
        {
            if (!m_isValid)
                return *this;
            
            MMT_Node MMT;
            m_BF->read(MMT, m_position);
            if (MMT.NextMMT != -1)
                m_position = MMT.NextMMT;
            else
                m_isValid = false;
            return *this;
        } // end ++ operator
        
        MultiMapTuple operator*()
        {
            MultiMapTuple MMT;
            if (!m_isValid)
                return MMT;
            
            MMT_Node MMTN;
            Key_Node KN;
            m_BF->read(MMTN, m_position);
            m_BF->read(KN, MMTN.Key_Offset);
            MMT.key = KN.Key;
            MMT.value = MMTN.Value;
            MMT.context = MMTN.Context;
            return MMT;
        } // end * operator
        
    private:
        bool m_isValid;
        BinaryFile* m_BF;
        BinaryFile::Offset m_position;
    };
    
    DiskMultiMap();
    ~DiskMultiMap();
    bool createNew(const std::string& filename, unsigned int numBuckets);
    bool openExisting(const std::string& filename);
    void close();
    bool insert(const std::string& key, const std::string& value, const std::string& context);
    Iterator search(const std::string& key);
    int erase(const std::string& key, const std::string& value, const std::string& context);
private:
    
    BinaryFile m_BF;
    unsigned int m_buckets;
    
    struct Bucket_Node
    {
        BinaryFile::Offset Offset;
    }; // end BucketNode
    
    struct TableHeader
    {
        int numBuckets;
        BinaryFile::Offset ErasedKey;
        BinaryFile::Offset ErasedMMT;
        BinaryFile::Offset currentPosition;
    }; // end TableHeader
    
    struct Key_Node
    {
        BinaryFile::Offset Offset;
        BinaryFile::Offset NextKey;
        BinaryFile::Offset PrevKey;
        BinaryFile::Offset MMT_Offset;
        int Count;
        char Key[120+1];
    }; // end KeyNode
    
    struct MMT_Node
    {
        BinaryFile::Offset Offset;
        BinaryFile::Offset NextMMT;
        BinaryFile::Offset PrevMMT;
        BinaryFile::Offset Key_Offset;
        char Value[120+1];
        char Context[120+1];
    }; // end MMTNode
    
    unsigned int hash(const std::string& s)
    {
        unsigned int h = 2166136261;
        for (int i = 0; i != s.size(); i++)
        {
            h ^= s[i];
            h *= 16777619;
        } // end for
        return ((h % m_buckets) * sizeof(Bucket_Node)) + sizeof(TableHeader);
    } // end hash
    
    /** Used to help insert nodes at the end of a bucket */
    void InsertNodeAux(int source, int type, const std::string& key, const std::string& value, const std::string& context)
    {
        // Initialize the key node...
        Key_Node KN;
        KN.NextKey = -1;
        KN.PrevKey = -1;
        KN.Count = 1;
        key.copy(KN.Key, key.size(), 0);
        KN.Key[key.size()] = '\0';
        // Initialize the Multi-map Tuple node...
        MMT_Node MMT;
        MMT.NextMMT = -1;
        MMT.PrevMMT = -1;
        value.copy(MMT.Value, value.size(), 0);
        MMT.Value[value.size()] = '\0';
        context.copy(MMT.Context, context.size(), 0);
        MMT.Context[context.size()] = '\0';
        // Get the table header...
        TableHeader TH;
        m_BF.read(TH, 0);
        // If there is not previously erased memory for the key...
        if (TH.ErasedKey == -1)
        {
            // Put the key at the end of memory
            KN.Offset = TH.currentPosition;
            TH.currentPosition += sizeof(Key_Node);
            MMT.Key_Offset = KN.Offset;
        } else
        {
            Key_Node tempKN;
            int prev = -1;
            m_BF.read(tempKN, TH.ErasedKey);
            while(tempKN.NextKey != -1)
            {
                prev = tempKN.Offset;
                m_BF.read(tempKN, tempKN.NextKey);
            }
            KN.Offset = tempKN.Offset;
            MMT.Key_Offset = KN.Offset;
            if (prev == -1)
                TH.ErasedKey = -1;
            else
            {
                m_BF.read(tempKN, prev);
                tempKN.NextKey = -1;
                m_BF.write(tempKN, prev);
            } // end if-else
        } // end if-else
        // Do the same for the Multi-map Tuple...
        if (TH.ErasedMMT == -1)
        {
            MMT.Offset = TH.currentPosition;
            TH.currentPosition += sizeof(MMT_Node);
            KN.MMT_Offset = MMT.Offset;
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
                TH.ErasedMMT = -1;
            else
            {
                m_BF.read(tempMMT, prev);
                tempMMT.NextMMT = -1;
                m_BF.write(tempMMT, prev);
            } // end if-else
        } // end if-else
        if (type == 1)
        {
            m_BF.write(KN.Offset, source);
        } else if (type == 2)
        {
            Key_Node tempKN;
            m_BF.read(tempKN, source);
            tempKN.NextKey = KN.Offset;
            KN.PrevKey = tempKN.Offset;
            m_BF.write(tempKN, tempKN.Offset);
        }
        m_BF.write(TH, 0);
        m_BF.write(KN, KN.Offset);
        m_BF.write(MMT, MMT.Offset);
    } // end InsertNodeAux
}; // end DiskMultiMap

#endif // DISKMULTIMAP_H_