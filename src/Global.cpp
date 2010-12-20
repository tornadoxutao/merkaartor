//
// C++ Implementation: Global
//
// Description:
//
//
// Author: cbro <cbro@semperpax.com>, (C) 2010
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "Global.h"
#include "MainWindow.h"

#ifdef PORTABLE_BUILD
bool g_Merk_Portable = true;
#else
bool g_Merk_Portable = false;
#endif
bool g_Merk_Frisius = true;
bool g_Merk_NoGuardedTagsImport = false;
bool g_Merk_Segment_Mode = false;
bool g_Merk_Ignore_Preferences = false;
bool g_Merk_Reset_Preferences = false;
bool g_Merk_IgnoreStartupTemplate = false;
bool g_Merk_SelfClip = false;

MainWindow* g_Merk_MainWindow = NULL;

QStringList tagKeys;
QStringList tagValues;
QHash< quint32, QList<quint32> > tagList;

QPair<quint32, quint32> g_addToTagList(QString k, QString v)
{
    qint32 ik, iv;

    ik = tagKeys.indexOf(k);
    if (ik == -1) {
        tagKeys.append(k);
        ik = tagKeys.size()-1;
    }
    iv = tagValues.indexOf(v);
    if (iv == -1) {
        tagValues.append(v);
        iv = tagValues.size()-1;
    }

    if (!k.isEmpty() && !v.isEmpty())
        tagList[ik].append(iv);

    return qMakePair((quint32)ik, (quint32)iv);
}

void g_removeFromTagList(quint32 k, quint32 v)
{
    tagList[k].removeOne(v);
    if (tagList[k].isEmpty())
        tagList.remove(k);
}

QList<QString> g_getTagKeys()
{
    return tagKeys;
}

QList<QString> g_getTagValues()
{
    return tagValues;
}

QStringList g_getTagValueList(QString k)
{
    QSet<quint32> retList;
    if (k == "*") {
        foreach (QList<quint32> list, tagList)
            retList.unite(list.toSet());
    } else
        retList = tagList[tagKeys.indexOf(k)].toSet();

    QStringList res;
    foreach (quint32 i, retList)
        res << g_getTagValue(i);

    return res;
}

const QString& g_getTagKey(int idx)
{
    return tagKeys.at(idx);
}

quint32 g_getTagKeyIndex(const QString& s)
{
    return tagKeys.indexOf(s);
}

QStringList g_getTagKeyList()
{
    return tagKeys.toSet().toList();
}

QString g_getTagValue(int idx)
{
    return tagValues.at(idx);
}

quint32 g_getTagValueIndex(const QString& s)
{
    return tagValues.indexOf(s);
}

