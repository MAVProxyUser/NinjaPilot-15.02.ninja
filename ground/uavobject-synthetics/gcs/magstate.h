/**
 ******************************************************************************
 *
 * @file       magstate.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *   
 * @note       Object definition file: magstate.xml. 
 *             This is an automatically generated file.
 *             DO NOT modify manually.
 *
 * @brief      The UAVUObjects GCS plugin 
 *****************************************************************************/
/* 
 * This program is free software; you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation; either version 3 of the License, or 
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License 
 * for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with this program; if not, write to the Free Software Foundation, Inc., 
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */
#ifndef MAGSTATE_H
#define MAGSTATE_H

#include "uavdataobject.h"
#include "uavobjectmanager.h"

class UAVOBJECTS_EXPORT MagState: public UAVDataObject
{
    Q_OBJECT
    Q_PROPERTY(float x READ getx WRITE setx NOTIFY xChanged);
    Q_PROPERTY(float y READ gety WRITE sety NOTIFY yChanged);
    Q_PROPERTY(float z READ getz WRITE setz NOTIFY zChanged);
    Q_PROPERTY(quint8 Source READ getSource WRITE setSource NOTIFY SourceChanged);


public:
    // Field structure
    typedef struct {
        float x;
        float y;
        float z;
        quint8 Source;

    } __attribute__((packed)) DataFields;

    // Field information
    // Field x information
    // Field y information
    // Field z information
    // Field Source information
    /* Enumeration options for field Source */
    typedef enum { SOURCE_INVALID=0, SOURCE_ONBOARD=1, SOURCE_AUX=2 } SourceOptions;

  
    // Constants
    static const quint32 OBJID = 0x9FFEAA0C;
    static const QString NAME;
    static const QString DESCRIPTION;
    static const QString CATEGORY;
    static const bool ISSINGLEINST = 1;
    static const bool ISSETTINGS = 0;
    static const quint32 NUMBYTES = sizeof(DataFields);

    // Functions
    MagState();

    DataFields getData();
    void setData(const DataFields& data);
    Metadata getDefaultMetadata();
    UAVDataObject* clone(quint32 instID);
	UAVDataObject* dirtyClone();
	
    static MagState* GetInstance(UAVObjectManager* objMngr, quint32 instID = 0);

    Q_INVOKABLE float getx() const;
    Q_INVOKABLE float gety() const;
    Q_INVOKABLE float getz() const;
    Q_INVOKABLE quint8 getSource() const;


public slots:
    void setx(float value);
    void sety(float value);
    void setz(float value);
    void setSource(quint8 value);


signals:
    void xChanged(float value);
    void yChanged(float value);
    void zChanged(float value);
    void SourceChanged(quint8 value);


private slots:
    void emitNotifications();
	
private:
    DataFields data;

    void setDefaultFieldValues();

};

#endif // MAGSTATE_H
