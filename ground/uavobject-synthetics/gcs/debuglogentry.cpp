/**
 ******************************************************************************
 *
 * @file       debuglogentry.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectsPlugin UAVObjects Plugin
 * @{
 *
 * @note       Object definition file: debuglogentry.xml.
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

#include "debuglogentry.h"
#include "uavobjectfield.h"

const QString DebugLogEntry::NAME = QString("DebugLogEntry");
const QString DebugLogEntry::DESCRIPTION = QString("Log Entry in Flash");
const QString DebugLogEntry::CATEGORY = QString("System");

/**
 * Constructor
 */
DebugLogEntry::DebugLogEntry(): UAVDataObject(OBJID, ISSINGLEINST, ISSETTINGS, NAME)
{
    // Create fields
    QList<UAVObjectField *> fields;
    QStringList FlightTimeElemNames;
    FlightTimeElemNames.append("0");
    fields.append( new UAVObjectField(QString("FlightTime"), tr(""), QString("us"), UAVObjectField::UINT32, FlightTimeElemNames, QStringList(), QString("")));
    QStringList ObjectIDElemNames;
    ObjectIDElemNames.append("0");
    fields.append( new UAVObjectField(QString("ObjectID"), tr(""), QString(""), UAVObjectField::UINT32, ObjectIDElemNames, QStringList(), QString("")));
    QStringList FlightElemNames;
    FlightElemNames.append("0");
    fields.append( new UAVObjectField(QString("Flight"), tr(""), QString(""), UAVObjectField::UINT16, FlightElemNames, QStringList(), QString("")));
    QStringList EntryElemNames;
    EntryElemNames.append("0");
    fields.append( new UAVObjectField(QString("Entry"), tr(""), QString(""), UAVObjectField::UINT16, EntryElemNames, QStringList(), QString("")));
    QStringList InstanceIDElemNames;
    InstanceIDElemNames.append("0");
    fields.append( new UAVObjectField(QString("InstanceID"), tr(""), QString(""), UAVObjectField::UINT16, InstanceIDElemNames, QStringList(), QString("")));
    QStringList SizeElemNames;
    SizeElemNames.append("0");
    fields.append( new UAVObjectField(QString("Size"), tr(""), QString(""), UAVObjectField::UINT16, SizeElemNames, QStringList(), QString("")));
    QStringList TypeElemNames;
    TypeElemNames.append("0");
    QStringList TypeEnumOptions;
    TypeEnumOptions.append("Empty");
    TypeEnumOptions.append("Text");
    TypeEnumOptions.append("UAVObject");
    TypeEnumOptions.append("MultipleUAVObjects");
    fields.append( new UAVObjectField(QString("Type"), tr(""), QString(""), UAVObjectField::ENUM, TypeElemNames, TypeEnumOptions, QString("")));
    QStringList DataElemNames;
    DataElemNames.append("0");
    DataElemNames.append("1");
    DataElemNames.append("2");
    DataElemNames.append("3");
    DataElemNames.append("4");
    DataElemNames.append("5");
    DataElemNames.append("6");
    DataElemNames.append("7");
    DataElemNames.append("8");
    DataElemNames.append("9");
    DataElemNames.append("10");
    DataElemNames.append("11");
    DataElemNames.append("12");
    DataElemNames.append("13");
    DataElemNames.append("14");
    DataElemNames.append("15");
    DataElemNames.append("16");
    DataElemNames.append("17");
    DataElemNames.append("18");
    DataElemNames.append("19");
    DataElemNames.append("20");
    DataElemNames.append("21");
    DataElemNames.append("22");
    DataElemNames.append("23");
    DataElemNames.append("24");
    DataElemNames.append("25");
    DataElemNames.append("26");
    DataElemNames.append("27");
    DataElemNames.append("28");
    DataElemNames.append("29");
    DataElemNames.append("30");
    DataElemNames.append("31");
    DataElemNames.append("32");
    DataElemNames.append("33");
    DataElemNames.append("34");
    DataElemNames.append("35");
    DataElemNames.append("36");
    DataElemNames.append("37");
    DataElemNames.append("38");
    DataElemNames.append("39");
    DataElemNames.append("40");
    DataElemNames.append("41");
    DataElemNames.append("42");
    DataElemNames.append("43");
    DataElemNames.append("44");
    DataElemNames.append("45");
    DataElemNames.append("46");
    DataElemNames.append("47");
    DataElemNames.append("48");
    DataElemNames.append("49");
    DataElemNames.append("50");
    DataElemNames.append("51");
    DataElemNames.append("52");
    DataElemNames.append("53");
    DataElemNames.append("54");
    DataElemNames.append("55");
    DataElemNames.append("56");
    DataElemNames.append("57");
    DataElemNames.append("58");
    DataElemNames.append("59");
    DataElemNames.append("60");
    DataElemNames.append("61");
    DataElemNames.append("62");
    DataElemNames.append("63");
    DataElemNames.append("64");
    DataElemNames.append("65");
    DataElemNames.append("66");
    DataElemNames.append("67");
    DataElemNames.append("68");
    DataElemNames.append("69");
    DataElemNames.append("70");
    DataElemNames.append("71");
    DataElemNames.append("72");
    DataElemNames.append("73");
    DataElemNames.append("74");
    DataElemNames.append("75");
    DataElemNames.append("76");
    DataElemNames.append("77");
    DataElemNames.append("78");
    DataElemNames.append("79");
    DataElemNames.append("80");
    DataElemNames.append("81");
    DataElemNames.append("82");
    DataElemNames.append("83");
    DataElemNames.append("84");
    DataElemNames.append("85");
    DataElemNames.append("86");
    DataElemNames.append("87");
    DataElemNames.append("88");
    DataElemNames.append("89");
    DataElemNames.append("90");
    DataElemNames.append("91");
    DataElemNames.append("92");
    DataElemNames.append("93");
    DataElemNames.append("94");
    DataElemNames.append("95");
    DataElemNames.append("96");
    DataElemNames.append("97");
    DataElemNames.append("98");
    DataElemNames.append("99");
    DataElemNames.append("100");
    DataElemNames.append("101");
    DataElemNames.append("102");
    DataElemNames.append("103");
    DataElemNames.append("104");
    DataElemNames.append("105");
    DataElemNames.append("106");
    DataElemNames.append("107");
    DataElemNames.append("108");
    DataElemNames.append("109");
    DataElemNames.append("110");
    DataElemNames.append("111");
    DataElemNames.append("112");
    DataElemNames.append("113");
    DataElemNames.append("114");
    DataElemNames.append("115");
    DataElemNames.append("116");
    DataElemNames.append("117");
    DataElemNames.append("118");
    DataElemNames.append("119");
    DataElemNames.append("120");
    DataElemNames.append("121");
    DataElemNames.append("122");
    DataElemNames.append("123");
    DataElemNames.append("124");
    DataElemNames.append("125");
    DataElemNames.append("126");
    DataElemNames.append("127");
    DataElemNames.append("128");
    DataElemNames.append("129");
    DataElemNames.append("130");
    DataElemNames.append("131");
    DataElemNames.append("132");
    DataElemNames.append("133");
    DataElemNames.append("134");
    DataElemNames.append("135");
    DataElemNames.append("136");
    DataElemNames.append("137");
    DataElemNames.append("138");
    DataElemNames.append("139");
    DataElemNames.append("140");
    DataElemNames.append("141");
    DataElemNames.append("142");
    DataElemNames.append("143");
    DataElemNames.append("144");
    DataElemNames.append("145");
    DataElemNames.append("146");
    DataElemNames.append("147");
    DataElemNames.append("148");
    DataElemNames.append("149");
    DataElemNames.append("150");
    DataElemNames.append("151");
    DataElemNames.append("152");
    DataElemNames.append("153");
    DataElemNames.append("154");
    DataElemNames.append("155");
    DataElemNames.append("156");
    DataElemNames.append("157");
    DataElemNames.append("158");
    DataElemNames.append("159");
    DataElemNames.append("160");
    DataElemNames.append("161");
    DataElemNames.append("162");
    DataElemNames.append("163");
    DataElemNames.append("164");
    DataElemNames.append("165");
    DataElemNames.append("166");
    DataElemNames.append("167");
    DataElemNames.append("168");
    DataElemNames.append("169");
    DataElemNames.append("170");
    DataElemNames.append("171");
    DataElemNames.append("172");
    DataElemNames.append("173");
    DataElemNames.append("174");
    DataElemNames.append("175");
    DataElemNames.append("176");
    DataElemNames.append("177");
    DataElemNames.append("178");
    DataElemNames.append("179");
    DataElemNames.append("180");
    DataElemNames.append("181");
    DataElemNames.append("182");
    DataElemNames.append("183");
    DataElemNames.append("184");
    DataElemNames.append("185");
    DataElemNames.append("186");
    DataElemNames.append("187");
    DataElemNames.append("188");
    DataElemNames.append("189");
    DataElemNames.append("190");
    DataElemNames.append("191");
    DataElemNames.append("192");
    DataElemNames.append("193");
    DataElemNames.append("194");
    DataElemNames.append("195");
    DataElemNames.append("196");
    DataElemNames.append("197");
    DataElemNames.append("198");
    DataElemNames.append("199");
    fields.append( new UAVObjectField(QString("Data"), tr(""), QString(""), UAVObjectField::UINT8, DataElemNames, QStringList(), QString("")));

    // Initialize object
    initializeFields(fields, (quint8 *)&data, NUMBYTES);
    // Set the default field values
    setDefaultFieldValues();
    // Set the object description
    setDescription(DESCRIPTION);

    // Set the Category of this object type
    setCategory(CATEGORY);

    connect(this, SIGNAL(objectUpdated(UAVObject *)), SLOT(emitNotifications()));
}

/**
 * Get the default metadata for this object
 */
UAVObject::Metadata DebugLogEntry::getDefaultMetadata()
{
    UAVObject::Metadata metadata;
    metadata.flags =
        ACCESS_READWRITE << UAVOBJ_ACCESS_SHIFT |
        ACCESS_READWRITE << UAVOBJ_GCS_ACCESS_SHIFT |
        0 << UAVOBJ_TELEMETRY_ACKED_SHIFT |
        0 << UAVOBJ_GCS_TELEMETRY_ACKED_SHIFT |
        UPDATEMODE_MANUAL << UAVOBJ_TELEMETRY_UPDATE_MODE_SHIFT |
        UPDATEMODE_MANUAL << UAVOBJ_GCS_TELEMETRY_UPDATE_MODE_SHIFT |
        UPDATEMODE_MANUAL << UAVOBJ_LOGGING_UPDATE_MODE_SHIFT;
    metadata.flightTelemetryUpdatePeriod = 0;
    metadata.gcsTelemetryUpdatePeriod = 0;
    metadata.loggingUpdatePeriod = 0;
    return metadata;
}

/**
 * Initialize object fields with the default values.
 * If a default value is not specified the object fields
 * will be initialized to zero.
 */
void DebugLogEntry::setDefaultFieldValues()
{

}

/**
 * Get the object data fields
 */
DebugLogEntry::DataFields DebugLogEntry::getData()
{
    QMutexLocker locker(mutex);
    return data;
}

/**
 * Set the object data fields
 */
void DebugLogEntry::setData(const DataFields& data)
{
    QMutexLocker locker(mutex);
    // Get metadata
    Metadata mdata = getMetadata();
    // Update object if the access mode permits
    if (UAVObject::GetGcsAccess(mdata) == ACCESS_READWRITE) {
        this->data = data;
        emit objectUpdatedAuto(this); // trigger object updated event
        emit objectUpdated(this);
    }
}

void DebugLogEntry::emitNotifications()
{
            //if (data.FlightTime != oldData.FlightTime)
            emit FlightTimeChanged(data.FlightTime);
        //if (data.ObjectID != oldData.ObjectID)
            emit ObjectIDChanged(data.ObjectID);
        //if (data.Flight != oldData.Flight)
            emit FlightChanged(data.Flight);
        //if (data.Entry != oldData.Entry)
            emit EntryChanged(data.Entry);
        //if (data.InstanceID != oldData.InstanceID)
            emit InstanceIDChanged(data.InstanceID);
        //if (data.Size != oldData.Size)
            emit SizeChanged(data.Size);
        //if (data.Type != oldData.Type)
            emit TypeChanged(data.Type);
        //if (data.Data[0] != oldData.Data[0])
            emit Data_0Changed(data.Data[0]);
        //if (data.Data[1] != oldData.Data[1])
            emit Data_1Changed(data.Data[1]);
        //if (data.Data[2] != oldData.Data[2])
            emit Data_2Changed(data.Data[2]);
        //if (data.Data[3] != oldData.Data[3])
            emit Data_3Changed(data.Data[3]);
        //if (data.Data[4] != oldData.Data[4])
            emit Data_4Changed(data.Data[4]);
        //if (data.Data[5] != oldData.Data[5])
            emit Data_5Changed(data.Data[5]);
        //if (data.Data[6] != oldData.Data[6])
            emit Data_6Changed(data.Data[6]);
        //if (data.Data[7] != oldData.Data[7])
            emit Data_7Changed(data.Data[7]);
        //if (data.Data[8] != oldData.Data[8])
            emit Data_8Changed(data.Data[8]);
        //if (data.Data[9] != oldData.Data[9])
            emit Data_9Changed(data.Data[9]);
        //if (data.Data[10] != oldData.Data[10])
            emit Data_10Changed(data.Data[10]);
        //if (data.Data[11] != oldData.Data[11])
            emit Data_11Changed(data.Data[11]);
        //if (data.Data[12] != oldData.Data[12])
            emit Data_12Changed(data.Data[12]);
        //if (data.Data[13] != oldData.Data[13])
            emit Data_13Changed(data.Data[13]);
        //if (data.Data[14] != oldData.Data[14])
            emit Data_14Changed(data.Data[14]);
        //if (data.Data[15] != oldData.Data[15])
            emit Data_15Changed(data.Data[15]);
        //if (data.Data[16] != oldData.Data[16])
            emit Data_16Changed(data.Data[16]);
        //if (data.Data[17] != oldData.Data[17])
            emit Data_17Changed(data.Data[17]);
        //if (data.Data[18] != oldData.Data[18])
            emit Data_18Changed(data.Data[18]);
        //if (data.Data[19] != oldData.Data[19])
            emit Data_19Changed(data.Data[19]);
        //if (data.Data[20] != oldData.Data[20])
            emit Data_20Changed(data.Data[20]);
        //if (data.Data[21] != oldData.Data[21])
            emit Data_21Changed(data.Data[21]);
        //if (data.Data[22] != oldData.Data[22])
            emit Data_22Changed(data.Data[22]);
        //if (data.Data[23] != oldData.Data[23])
            emit Data_23Changed(data.Data[23]);
        //if (data.Data[24] != oldData.Data[24])
            emit Data_24Changed(data.Data[24]);
        //if (data.Data[25] != oldData.Data[25])
            emit Data_25Changed(data.Data[25]);
        //if (data.Data[26] != oldData.Data[26])
            emit Data_26Changed(data.Data[26]);
        //if (data.Data[27] != oldData.Data[27])
            emit Data_27Changed(data.Data[27]);
        //if (data.Data[28] != oldData.Data[28])
            emit Data_28Changed(data.Data[28]);
        //if (data.Data[29] != oldData.Data[29])
            emit Data_29Changed(data.Data[29]);
        //if (data.Data[30] != oldData.Data[30])
            emit Data_30Changed(data.Data[30]);
        //if (data.Data[31] != oldData.Data[31])
            emit Data_31Changed(data.Data[31]);
        //if (data.Data[32] != oldData.Data[32])
            emit Data_32Changed(data.Data[32]);
        //if (data.Data[33] != oldData.Data[33])
            emit Data_33Changed(data.Data[33]);
        //if (data.Data[34] != oldData.Data[34])
            emit Data_34Changed(data.Data[34]);
        //if (data.Data[35] != oldData.Data[35])
            emit Data_35Changed(data.Data[35]);
        //if (data.Data[36] != oldData.Data[36])
            emit Data_36Changed(data.Data[36]);
        //if (data.Data[37] != oldData.Data[37])
            emit Data_37Changed(data.Data[37]);
        //if (data.Data[38] != oldData.Data[38])
            emit Data_38Changed(data.Data[38]);
        //if (data.Data[39] != oldData.Data[39])
            emit Data_39Changed(data.Data[39]);
        //if (data.Data[40] != oldData.Data[40])
            emit Data_40Changed(data.Data[40]);
        //if (data.Data[41] != oldData.Data[41])
            emit Data_41Changed(data.Data[41]);
        //if (data.Data[42] != oldData.Data[42])
            emit Data_42Changed(data.Data[42]);
        //if (data.Data[43] != oldData.Data[43])
            emit Data_43Changed(data.Data[43]);
        //if (data.Data[44] != oldData.Data[44])
            emit Data_44Changed(data.Data[44]);
        //if (data.Data[45] != oldData.Data[45])
            emit Data_45Changed(data.Data[45]);
        //if (data.Data[46] != oldData.Data[46])
            emit Data_46Changed(data.Data[46]);
        //if (data.Data[47] != oldData.Data[47])
            emit Data_47Changed(data.Data[47]);
        //if (data.Data[48] != oldData.Data[48])
            emit Data_48Changed(data.Data[48]);
        //if (data.Data[49] != oldData.Data[49])
            emit Data_49Changed(data.Data[49]);
        //if (data.Data[50] != oldData.Data[50])
            emit Data_50Changed(data.Data[50]);
        //if (data.Data[51] != oldData.Data[51])
            emit Data_51Changed(data.Data[51]);
        //if (data.Data[52] != oldData.Data[52])
            emit Data_52Changed(data.Data[52]);
        //if (data.Data[53] != oldData.Data[53])
            emit Data_53Changed(data.Data[53]);
        //if (data.Data[54] != oldData.Data[54])
            emit Data_54Changed(data.Data[54]);
        //if (data.Data[55] != oldData.Data[55])
            emit Data_55Changed(data.Data[55]);
        //if (data.Data[56] != oldData.Data[56])
            emit Data_56Changed(data.Data[56]);
        //if (data.Data[57] != oldData.Data[57])
            emit Data_57Changed(data.Data[57]);
        //if (data.Data[58] != oldData.Data[58])
            emit Data_58Changed(data.Data[58]);
        //if (data.Data[59] != oldData.Data[59])
            emit Data_59Changed(data.Data[59]);
        //if (data.Data[60] != oldData.Data[60])
            emit Data_60Changed(data.Data[60]);
        //if (data.Data[61] != oldData.Data[61])
            emit Data_61Changed(data.Data[61]);
        //if (data.Data[62] != oldData.Data[62])
            emit Data_62Changed(data.Data[62]);
        //if (data.Data[63] != oldData.Data[63])
            emit Data_63Changed(data.Data[63]);
        //if (data.Data[64] != oldData.Data[64])
            emit Data_64Changed(data.Data[64]);
        //if (data.Data[65] != oldData.Data[65])
            emit Data_65Changed(data.Data[65]);
        //if (data.Data[66] != oldData.Data[66])
            emit Data_66Changed(data.Data[66]);
        //if (data.Data[67] != oldData.Data[67])
            emit Data_67Changed(data.Data[67]);
        //if (data.Data[68] != oldData.Data[68])
            emit Data_68Changed(data.Data[68]);
        //if (data.Data[69] != oldData.Data[69])
            emit Data_69Changed(data.Data[69]);
        //if (data.Data[70] != oldData.Data[70])
            emit Data_70Changed(data.Data[70]);
        //if (data.Data[71] != oldData.Data[71])
            emit Data_71Changed(data.Data[71]);
        //if (data.Data[72] != oldData.Data[72])
            emit Data_72Changed(data.Data[72]);
        //if (data.Data[73] != oldData.Data[73])
            emit Data_73Changed(data.Data[73]);
        //if (data.Data[74] != oldData.Data[74])
            emit Data_74Changed(data.Data[74]);
        //if (data.Data[75] != oldData.Data[75])
            emit Data_75Changed(data.Data[75]);
        //if (data.Data[76] != oldData.Data[76])
            emit Data_76Changed(data.Data[76]);
        //if (data.Data[77] != oldData.Data[77])
            emit Data_77Changed(data.Data[77]);
        //if (data.Data[78] != oldData.Data[78])
            emit Data_78Changed(data.Data[78]);
        //if (data.Data[79] != oldData.Data[79])
            emit Data_79Changed(data.Data[79]);
        //if (data.Data[80] != oldData.Data[80])
            emit Data_80Changed(data.Data[80]);
        //if (data.Data[81] != oldData.Data[81])
            emit Data_81Changed(data.Data[81]);
        //if (data.Data[82] != oldData.Data[82])
            emit Data_82Changed(data.Data[82]);
        //if (data.Data[83] != oldData.Data[83])
            emit Data_83Changed(data.Data[83]);
        //if (data.Data[84] != oldData.Data[84])
            emit Data_84Changed(data.Data[84]);
        //if (data.Data[85] != oldData.Data[85])
            emit Data_85Changed(data.Data[85]);
        //if (data.Data[86] != oldData.Data[86])
            emit Data_86Changed(data.Data[86]);
        //if (data.Data[87] != oldData.Data[87])
            emit Data_87Changed(data.Data[87]);
        //if (data.Data[88] != oldData.Data[88])
            emit Data_88Changed(data.Data[88]);
        //if (data.Data[89] != oldData.Data[89])
            emit Data_89Changed(data.Data[89]);
        //if (data.Data[90] != oldData.Data[90])
            emit Data_90Changed(data.Data[90]);
        //if (data.Data[91] != oldData.Data[91])
            emit Data_91Changed(data.Data[91]);
        //if (data.Data[92] != oldData.Data[92])
            emit Data_92Changed(data.Data[92]);
        //if (data.Data[93] != oldData.Data[93])
            emit Data_93Changed(data.Data[93]);
        //if (data.Data[94] != oldData.Data[94])
            emit Data_94Changed(data.Data[94]);
        //if (data.Data[95] != oldData.Data[95])
            emit Data_95Changed(data.Data[95]);
        //if (data.Data[96] != oldData.Data[96])
            emit Data_96Changed(data.Data[96]);
        //if (data.Data[97] != oldData.Data[97])
            emit Data_97Changed(data.Data[97]);
        //if (data.Data[98] != oldData.Data[98])
            emit Data_98Changed(data.Data[98]);
        //if (data.Data[99] != oldData.Data[99])
            emit Data_99Changed(data.Data[99]);
        //if (data.Data[100] != oldData.Data[100])
            emit Data_100Changed(data.Data[100]);
        //if (data.Data[101] != oldData.Data[101])
            emit Data_101Changed(data.Data[101]);
        //if (data.Data[102] != oldData.Data[102])
            emit Data_102Changed(data.Data[102]);
        //if (data.Data[103] != oldData.Data[103])
            emit Data_103Changed(data.Data[103]);
        //if (data.Data[104] != oldData.Data[104])
            emit Data_104Changed(data.Data[104]);
        //if (data.Data[105] != oldData.Data[105])
            emit Data_105Changed(data.Data[105]);
        //if (data.Data[106] != oldData.Data[106])
            emit Data_106Changed(data.Data[106]);
        //if (data.Data[107] != oldData.Data[107])
            emit Data_107Changed(data.Data[107]);
        //if (data.Data[108] != oldData.Data[108])
            emit Data_108Changed(data.Data[108]);
        //if (data.Data[109] != oldData.Data[109])
            emit Data_109Changed(data.Data[109]);
        //if (data.Data[110] != oldData.Data[110])
            emit Data_110Changed(data.Data[110]);
        //if (data.Data[111] != oldData.Data[111])
            emit Data_111Changed(data.Data[111]);
        //if (data.Data[112] != oldData.Data[112])
            emit Data_112Changed(data.Data[112]);
        //if (data.Data[113] != oldData.Data[113])
            emit Data_113Changed(data.Data[113]);
        //if (data.Data[114] != oldData.Data[114])
            emit Data_114Changed(data.Data[114]);
        //if (data.Data[115] != oldData.Data[115])
            emit Data_115Changed(data.Data[115]);
        //if (data.Data[116] != oldData.Data[116])
            emit Data_116Changed(data.Data[116]);
        //if (data.Data[117] != oldData.Data[117])
            emit Data_117Changed(data.Data[117]);
        //if (data.Data[118] != oldData.Data[118])
            emit Data_118Changed(data.Data[118]);
        //if (data.Data[119] != oldData.Data[119])
            emit Data_119Changed(data.Data[119]);
        //if (data.Data[120] != oldData.Data[120])
            emit Data_120Changed(data.Data[120]);
        //if (data.Data[121] != oldData.Data[121])
            emit Data_121Changed(data.Data[121]);
        //if (data.Data[122] != oldData.Data[122])
            emit Data_122Changed(data.Data[122]);
        //if (data.Data[123] != oldData.Data[123])
            emit Data_123Changed(data.Data[123]);
        //if (data.Data[124] != oldData.Data[124])
            emit Data_124Changed(data.Data[124]);
        //if (data.Data[125] != oldData.Data[125])
            emit Data_125Changed(data.Data[125]);
        //if (data.Data[126] != oldData.Data[126])
            emit Data_126Changed(data.Data[126]);
        //if (data.Data[127] != oldData.Data[127])
            emit Data_127Changed(data.Data[127]);
        //if (data.Data[128] != oldData.Data[128])
            emit Data_128Changed(data.Data[128]);
        //if (data.Data[129] != oldData.Data[129])
            emit Data_129Changed(data.Data[129]);
        //if (data.Data[130] != oldData.Data[130])
            emit Data_130Changed(data.Data[130]);
        //if (data.Data[131] != oldData.Data[131])
            emit Data_131Changed(data.Data[131]);
        //if (data.Data[132] != oldData.Data[132])
            emit Data_132Changed(data.Data[132]);
        //if (data.Data[133] != oldData.Data[133])
            emit Data_133Changed(data.Data[133]);
        //if (data.Data[134] != oldData.Data[134])
            emit Data_134Changed(data.Data[134]);
        //if (data.Data[135] != oldData.Data[135])
            emit Data_135Changed(data.Data[135]);
        //if (data.Data[136] != oldData.Data[136])
            emit Data_136Changed(data.Data[136]);
        //if (data.Data[137] != oldData.Data[137])
            emit Data_137Changed(data.Data[137]);
        //if (data.Data[138] != oldData.Data[138])
            emit Data_138Changed(data.Data[138]);
        //if (data.Data[139] != oldData.Data[139])
            emit Data_139Changed(data.Data[139]);
        //if (data.Data[140] != oldData.Data[140])
            emit Data_140Changed(data.Data[140]);
        //if (data.Data[141] != oldData.Data[141])
            emit Data_141Changed(data.Data[141]);
        //if (data.Data[142] != oldData.Data[142])
            emit Data_142Changed(data.Data[142]);
        //if (data.Data[143] != oldData.Data[143])
            emit Data_143Changed(data.Data[143]);
        //if (data.Data[144] != oldData.Data[144])
            emit Data_144Changed(data.Data[144]);
        //if (data.Data[145] != oldData.Data[145])
            emit Data_145Changed(data.Data[145]);
        //if (data.Data[146] != oldData.Data[146])
            emit Data_146Changed(data.Data[146]);
        //if (data.Data[147] != oldData.Data[147])
            emit Data_147Changed(data.Data[147]);
        //if (data.Data[148] != oldData.Data[148])
            emit Data_148Changed(data.Data[148]);
        //if (data.Data[149] != oldData.Data[149])
            emit Data_149Changed(data.Data[149]);
        //if (data.Data[150] != oldData.Data[150])
            emit Data_150Changed(data.Data[150]);
        //if (data.Data[151] != oldData.Data[151])
            emit Data_151Changed(data.Data[151]);
        //if (data.Data[152] != oldData.Data[152])
            emit Data_152Changed(data.Data[152]);
        //if (data.Data[153] != oldData.Data[153])
            emit Data_153Changed(data.Data[153]);
        //if (data.Data[154] != oldData.Data[154])
            emit Data_154Changed(data.Data[154]);
        //if (data.Data[155] != oldData.Data[155])
            emit Data_155Changed(data.Data[155]);
        //if (data.Data[156] != oldData.Data[156])
            emit Data_156Changed(data.Data[156]);
        //if (data.Data[157] != oldData.Data[157])
            emit Data_157Changed(data.Data[157]);
        //if (data.Data[158] != oldData.Data[158])
            emit Data_158Changed(data.Data[158]);
        //if (data.Data[159] != oldData.Data[159])
            emit Data_159Changed(data.Data[159]);
        //if (data.Data[160] != oldData.Data[160])
            emit Data_160Changed(data.Data[160]);
        //if (data.Data[161] != oldData.Data[161])
            emit Data_161Changed(data.Data[161]);
        //if (data.Data[162] != oldData.Data[162])
            emit Data_162Changed(data.Data[162]);
        //if (data.Data[163] != oldData.Data[163])
            emit Data_163Changed(data.Data[163]);
        //if (data.Data[164] != oldData.Data[164])
            emit Data_164Changed(data.Data[164]);
        //if (data.Data[165] != oldData.Data[165])
            emit Data_165Changed(data.Data[165]);
        //if (data.Data[166] != oldData.Data[166])
            emit Data_166Changed(data.Data[166]);
        //if (data.Data[167] != oldData.Data[167])
            emit Data_167Changed(data.Data[167]);
        //if (data.Data[168] != oldData.Data[168])
            emit Data_168Changed(data.Data[168]);
        //if (data.Data[169] != oldData.Data[169])
            emit Data_169Changed(data.Data[169]);
        //if (data.Data[170] != oldData.Data[170])
            emit Data_170Changed(data.Data[170]);
        //if (data.Data[171] != oldData.Data[171])
            emit Data_171Changed(data.Data[171]);
        //if (data.Data[172] != oldData.Data[172])
            emit Data_172Changed(data.Data[172]);
        //if (data.Data[173] != oldData.Data[173])
            emit Data_173Changed(data.Data[173]);
        //if (data.Data[174] != oldData.Data[174])
            emit Data_174Changed(data.Data[174]);
        //if (data.Data[175] != oldData.Data[175])
            emit Data_175Changed(data.Data[175]);
        //if (data.Data[176] != oldData.Data[176])
            emit Data_176Changed(data.Data[176]);
        //if (data.Data[177] != oldData.Data[177])
            emit Data_177Changed(data.Data[177]);
        //if (data.Data[178] != oldData.Data[178])
            emit Data_178Changed(data.Data[178]);
        //if (data.Data[179] != oldData.Data[179])
            emit Data_179Changed(data.Data[179]);
        //if (data.Data[180] != oldData.Data[180])
            emit Data_180Changed(data.Data[180]);
        //if (data.Data[181] != oldData.Data[181])
            emit Data_181Changed(data.Data[181]);
        //if (data.Data[182] != oldData.Data[182])
            emit Data_182Changed(data.Data[182]);
        //if (data.Data[183] != oldData.Data[183])
            emit Data_183Changed(data.Data[183]);
        //if (data.Data[184] != oldData.Data[184])
            emit Data_184Changed(data.Data[184]);
        //if (data.Data[185] != oldData.Data[185])
            emit Data_185Changed(data.Data[185]);
        //if (data.Data[186] != oldData.Data[186])
            emit Data_186Changed(data.Data[186]);
        //if (data.Data[187] != oldData.Data[187])
            emit Data_187Changed(data.Data[187]);
        //if (data.Data[188] != oldData.Data[188])
            emit Data_188Changed(data.Data[188]);
        //if (data.Data[189] != oldData.Data[189])
            emit Data_189Changed(data.Data[189]);
        //if (data.Data[190] != oldData.Data[190])
            emit Data_190Changed(data.Data[190]);
        //if (data.Data[191] != oldData.Data[191])
            emit Data_191Changed(data.Data[191]);
        //if (data.Data[192] != oldData.Data[192])
            emit Data_192Changed(data.Data[192]);
        //if (data.Data[193] != oldData.Data[193])
            emit Data_193Changed(data.Data[193]);
        //if (data.Data[194] != oldData.Data[194])
            emit Data_194Changed(data.Data[194]);
        //if (data.Data[195] != oldData.Data[195])
            emit Data_195Changed(data.Data[195]);
        //if (data.Data[196] != oldData.Data[196])
            emit Data_196Changed(data.Data[196]);
        //if (data.Data[197] != oldData.Data[197])
            emit Data_197Changed(data.Data[197]);
        //if (data.Data[198] != oldData.Data[198])
            emit Data_198Changed(data.Data[198]);
        //if (data.Data[199] != oldData.Data[199])
            emit Data_199Changed(data.Data[199]);

}

/**
 * Create a clone of this object, a new instance ID must be specified.
 * Do not use this function directly to create new instances, the
 * UAVObjectManager should be used instead.
 */
UAVDataObject *DebugLogEntry::clone(quint32 instID)
{
    DebugLogEntry *obj = new DebugLogEntry();
    obj->initialize(instID, this->getMetaObject());
    return obj;
}

/**
 * Create a clone of this object only to be used to retrieve defaults
 */
UAVDataObject *DebugLogEntry::dirtyClone()
{
    DebugLogEntry *obj = new DebugLogEntry();
    return obj;
}

/**
 * Static function to retrieve an instance of the object.
 */
DebugLogEntry *DebugLogEntry::GetInstance(UAVObjectManager *objMngr, quint32 instID)
{
    return dynamic_cast<DebugLogEntry *>(objMngr->getObject(DebugLogEntry::OBJID, instID));
}

quint32 DebugLogEntry::getFlightTime() const
{
   QMutexLocker locker(mutex);
   return data.FlightTime;
}
void DebugLogEntry::setFlightTime(quint32 value)
{
   mutex->lock();
   bool changed = data.FlightTime != value;
   data.FlightTime = value;
   mutex->unlock();
   if (changed) emit FlightTimeChanged(value);
}

quint32 DebugLogEntry::getObjectID() const
{
   QMutexLocker locker(mutex);
   return data.ObjectID;
}
void DebugLogEntry::setObjectID(quint32 value)
{
   mutex->lock();
   bool changed = data.ObjectID != value;
   data.ObjectID = value;
   mutex->unlock();
   if (changed) emit ObjectIDChanged(value);
}

quint16 DebugLogEntry::getFlight() const
{
   QMutexLocker locker(mutex);
   return data.Flight;
}
void DebugLogEntry::setFlight(quint16 value)
{
   mutex->lock();
   bool changed = data.Flight != value;
   data.Flight = value;
   mutex->unlock();
   if (changed) emit FlightChanged(value);
}

quint16 DebugLogEntry::getEntry() const
{
   QMutexLocker locker(mutex);
   return data.Entry;
}
void DebugLogEntry::setEntry(quint16 value)
{
   mutex->lock();
   bool changed = data.Entry != value;
   data.Entry = value;
   mutex->unlock();
   if (changed) emit EntryChanged(value);
}

quint16 DebugLogEntry::getInstanceID() const
{
   QMutexLocker locker(mutex);
   return data.InstanceID;
}
void DebugLogEntry::setInstanceID(quint16 value)
{
   mutex->lock();
   bool changed = data.InstanceID != value;
   data.InstanceID = value;
   mutex->unlock();
   if (changed) emit InstanceIDChanged(value);
}

quint16 DebugLogEntry::getSize() const
{
   QMutexLocker locker(mutex);
   return data.Size;
}
void DebugLogEntry::setSize(quint16 value)
{
   mutex->lock();
   bool changed = data.Size != value;
   data.Size = value;
   mutex->unlock();
   if (changed) emit SizeChanged(value);
}

quint8 DebugLogEntry::getType() const
{
   QMutexLocker locker(mutex);
   return data.Type;
}
void DebugLogEntry::setType(quint8 value)
{
   mutex->lock();
   bool changed = data.Type != value;
   data.Type = value;
   mutex->unlock();
   if (changed) emit TypeChanged(value);
}

quint8 DebugLogEntry::getData(quint32 index) const
{
   QMutexLocker locker(mutex);
   return data.Data[index];
}
void DebugLogEntry::setData(quint32 index, quint8 value)
{
   mutex->lock();
   bool changed = data.Data[index] != value;
   data.Data[index] = value;
   mutex->unlock();
   if (changed) emit DataChanged(index,value);
}

quint8 DebugLogEntry::getData_0() const
{
   QMutexLocker locker(mutex);
   return data.Data[0];
}
void DebugLogEntry::setData_0(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[0] != value;
   data.Data[0] = value;
   mutex->unlock();
   if (changed) emit Data_0Changed(value);
}

quint8 DebugLogEntry::getData_1() const
{
   QMutexLocker locker(mutex);
   return data.Data[1];
}
void DebugLogEntry::setData_1(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[1] != value;
   data.Data[1] = value;
   mutex->unlock();
   if (changed) emit Data_1Changed(value);
}

quint8 DebugLogEntry::getData_2() const
{
   QMutexLocker locker(mutex);
   return data.Data[2];
}
void DebugLogEntry::setData_2(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[2] != value;
   data.Data[2] = value;
   mutex->unlock();
   if (changed) emit Data_2Changed(value);
}

quint8 DebugLogEntry::getData_3() const
{
   QMutexLocker locker(mutex);
   return data.Data[3];
}
void DebugLogEntry::setData_3(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[3] != value;
   data.Data[3] = value;
   mutex->unlock();
   if (changed) emit Data_3Changed(value);
}

quint8 DebugLogEntry::getData_4() const
{
   QMutexLocker locker(mutex);
   return data.Data[4];
}
void DebugLogEntry::setData_4(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[4] != value;
   data.Data[4] = value;
   mutex->unlock();
   if (changed) emit Data_4Changed(value);
}

quint8 DebugLogEntry::getData_5() const
{
   QMutexLocker locker(mutex);
   return data.Data[5];
}
void DebugLogEntry::setData_5(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[5] != value;
   data.Data[5] = value;
   mutex->unlock();
   if (changed) emit Data_5Changed(value);
}

quint8 DebugLogEntry::getData_6() const
{
   QMutexLocker locker(mutex);
   return data.Data[6];
}
void DebugLogEntry::setData_6(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[6] != value;
   data.Data[6] = value;
   mutex->unlock();
   if (changed) emit Data_6Changed(value);
}

quint8 DebugLogEntry::getData_7() const
{
   QMutexLocker locker(mutex);
   return data.Data[7];
}
void DebugLogEntry::setData_7(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[7] != value;
   data.Data[7] = value;
   mutex->unlock();
   if (changed) emit Data_7Changed(value);
}

quint8 DebugLogEntry::getData_8() const
{
   QMutexLocker locker(mutex);
   return data.Data[8];
}
void DebugLogEntry::setData_8(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[8] != value;
   data.Data[8] = value;
   mutex->unlock();
   if (changed) emit Data_8Changed(value);
}

quint8 DebugLogEntry::getData_9() const
{
   QMutexLocker locker(mutex);
   return data.Data[9];
}
void DebugLogEntry::setData_9(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[9] != value;
   data.Data[9] = value;
   mutex->unlock();
   if (changed) emit Data_9Changed(value);
}

quint8 DebugLogEntry::getData_10() const
{
   QMutexLocker locker(mutex);
   return data.Data[10];
}
void DebugLogEntry::setData_10(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[10] != value;
   data.Data[10] = value;
   mutex->unlock();
   if (changed) emit Data_10Changed(value);
}

quint8 DebugLogEntry::getData_11() const
{
   QMutexLocker locker(mutex);
   return data.Data[11];
}
void DebugLogEntry::setData_11(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[11] != value;
   data.Data[11] = value;
   mutex->unlock();
   if (changed) emit Data_11Changed(value);
}

quint8 DebugLogEntry::getData_12() const
{
   QMutexLocker locker(mutex);
   return data.Data[12];
}
void DebugLogEntry::setData_12(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[12] != value;
   data.Data[12] = value;
   mutex->unlock();
   if (changed) emit Data_12Changed(value);
}

quint8 DebugLogEntry::getData_13() const
{
   QMutexLocker locker(mutex);
   return data.Data[13];
}
void DebugLogEntry::setData_13(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[13] != value;
   data.Data[13] = value;
   mutex->unlock();
   if (changed) emit Data_13Changed(value);
}

quint8 DebugLogEntry::getData_14() const
{
   QMutexLocker locker(mutex);
   return data.Data[14];
}
void DebugLogEntry::setData_14(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[14] != value;
   data.Data[14] = value;
   mutex->unlock();
   if (changed) emit Data_14Changed(value);
}

quint8 DebugLogEntry::getData_15() const
{
   QMutexLocker locker(mutex);
   return data.Data[15];
}
void DebugLogEntry::setData_15(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[15] != value;
   data.Data[15] = value;
   mutex->unlock();
   if (changed) emit Data_15Changed(value);
}

quint8 DebugLogEntry::getData_16() const
{
   QMutexLocker locker(mutex);
   return data.Data[16];
}
void DebugLogEntry::setData_16(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[16] != value;
   data.Data[16] = value;
   mutex->unlock();
   if (changed) emit Data_16Changed(value);
}

quint8 DebugLogEntry::getData_17() const
{
   QMutexLocker locker(mutex);
   return data.Data[17];
}
void DebugLogEntry::setData_17(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[17] != value;
   data.Data[17] = value;
   mutex->unlock();
   if (changed) emit Data_17Changed(value);
}

quint8 DebugLogEntry::getData_18() const
{
   QMutexLocker locker(mutex);
   return data.Data[18];
}
void DebugLogEntry::setData_18(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[18] != value;
   data.Data[18] = value;
   mutex->unlock();
   if (changed) emit Data_18Changed(value);
}

quint8 DebugLogEntry::getData_19() const
{
   QMutexLocker locker(mutex);
   return data.Data[19];
}
void DebugLogEntry::setData_19(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[19] != value;
   data.Data[19] = value;
   mutex->unlock();
   if (changed) emit Data_19Changed(value);
}

quint8 DebugLogEntry::getData_20() const
{
   QMutexLocker locker(mutex);
   return data.Data[20];
}
void DebugLogEntry::setData_20(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[20] != value;
   data.Data[20] = value;
   mutex->unlock();
   if (changed) emit Data_20Changed(value);
}

quint8 DebugLogEntry::getData_21() const
{
   QMutexLocker locker(mutex);
   return data.Data[21];
}
void DebugLogEntry::setData_21(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[21] != value;
   data.Data[21] = value;
   mutex->unlock();
   if (changed) emit Data_21Changed(value);
}

quint8 DebugLogEntry::getData_22() const
{
   QMutexLocker locker(mutex);
   return data.Data[22];
}
void DebugLogEntry::setData_22(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[22] != value;
   data.Data[22] = value;
   mutex->unlock();
   if (changed) emit Data_22Changed(value);
}

quint8 DebugLogEntry::getData_23() const
{
   QMutexLocker locker(mutex);
   return data.Data[23];
}
void DebugLogEntry::setData_23(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[23] != value;
   data.Data[23] = value;
   mutex->unlock();
   if (changed) emit Data_23Changed(value);
}

quint8 DebugLogEntry::getData_24() const
{
   QMutexLocker locker(mutex);
   return data.Data[24];
}
void DebugLogEntry::setData_24(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[24] != value;
   data.Data[24] = value;
   mutex->unlock();
   if (changed) emit Data_24Changed(value);
}

quint8 DebugLogEntry::getData_25() const
{
   QMutexLocker locker(mutex);
   return data.Data[25];
}
void DebugLogEntry::setData_25(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[25] != value;
   data.Data[25] = value;
   mutex->unlock();
   if (changed) emit Data_25Changed(value);
}

quint8 DebugLogEntry::getData_26() const
{
   QMutexLocker locker(mutex);
   return data.Data[26];
}
void DebugLogEntry::setData_26(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[26] != value;
   data.Data[26] = value;
   mutex->unlock();
   if (changed) emit Data_26Changed(value);
}

quint8 DebugLogEntry::getData_27() const
{
   QMutexLocker locker(mutex);
   return data.Data[27];
}
void DebugLogEntry::setData_27(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[27] != value;
   data.Data[27] = value;
   mutex->unlock();
   if (changed) emit Data_27Changed(value);
}

quint8 DebugLogEntry::getData_28() const
{
   QMutexLocker locker(mutex);
   return data.Data[28];
}
void DebugLogEntry::setData_28(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[28] != value;
   data.Data[28] = value;
   mutex->unlock();
   if (changed) emit Data_28Changed(value);
}

quint8 DebugLogEntry::getData_29() const
{
   QMutexLocker locker(mutex);
   return data.Data[29];
}
void DebugLogEntry::setData_29(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[29] != value;
   data.Data[29] = value;
   mutex->unlock();
   if (changed) emit Data_29Changed(value);
}

quint8 DebugLogEntry::getData_30() const
{
   QMutexLocker locker(mutex);
   return data.Data[30];
}
void DebugLogEntry::setData_30(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[30] != value;
   data.Data[30] = value;
   mutex->unlock();
   if (changed) emit Data_30Changed(value);
}

quint8 DebugLogEntry::getData_31() const
{
   QMutexLocker locker(mutex);
   return data.Data[31];
}
void DebugLogEntry::setData_31(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[31] != value;
   data.Data[31] = value;
   mutex->unlock();
   if (changed) emit Data_31Changed(value);
}

quint8 DebugLogEntry::getData_32() const
{
   QMutexLocker locker(mutex);
   return data.Data[32];
}
void DebugLogEntry::setData_32(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[32] != value;
   data.Data[32] = value;
   mutex->unlock();
   if (changed) emit Data_32Changed(value);
}

quint8 DebugLogEntry::getData_33() const
{
   QMutexLocker locker(mutex);
   return data.Data[33];
}
void DebugLogEntry::setData_33(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[33] != value;
   data.Data[33] = value;
   mutex->unlock();
   if (changed) emit Data_33Changed(value);
}

quint8 DebugLogEntry::getData_34() const
{
   QMutexLocker locker(mutex);
   return data.Data[34];
}
void DebugLogEntry::setData_34(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[34] != value;
   data.Data[34] = value;
   mutex->unlock();
   if (changed) emit Data_34Changed(value);
}

quint8 DebugLogEntry::getData_35() const
{
   QMutexLocker locker(mutex);
   return data.Data[35];
}
void DebugLogEntry::setData_35(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[35] != value;
   data.Data[35] = value;
   mutex->unlock();
   if (changed) emit Data_35Changed(value);
}

quint8 DebugLogEntry::getData_36() const
{
   QMutexLocker locker(mutex);
   return data.Data[36];
}
void DebugLogEntry::setData_36(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[36] != value;
   data.Data[36] = value;
   mutex->unlock();
   if (changed) emit Data_36Changed(value);
}

quint8 DebugLogEntry::getData_37() const
{
   QMutexLocker locker(mutex);
   return data.Data[37];
}
void DebugLogEntry::setData_37(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[37] != value;
   data.Data[37] = value;
   mutex->unlock();
   if (changed) emit Data_37Changed(value);
}

quint8 DebugLogEntry::getData_38() const
{
   QMutexLocker locker(mutex);
   return data.Data[38];
}
void DebugLogEntry::setData_38(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[38] != value;
   data.Data[38] = value;
   mutex->unlock();
   if (changed) emit Data_38Changed(value);
}

quint8 DebugLogEntry::getData_39() const
{
   QMutexLocker locker(mutex);
   return data.Data[39];
}
void DebugLogEntry::setData_39(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[39] != value;
   data.Data[39] = value;
   mutex->unlock();
   if (changed) emit Data_39Changed(value);
}

quint8 DebugLogEntry::getData_40() const
{
   QMutexLocker locker(mutex);
   return data.Data[40];
}
void DebugLogEntry::setData_40(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[40] != value;
   data.Data[40] = value;
   mutex->unlock();
   if (changed) emit Data_40Changed(value);
}

quint8 DebugLogEntry::getData_41() const
{
   QMutexLocker locker(mutex);
   return data.Data[41];
}
void DebugLogEntry::setData_41(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[41] != value;
   data.Data[41] = value;
   mutex->unlock();
   if (changed) emit Data_41Changed(value);
}

quint8 DebugLogEntry::getData_42() const
{
   QMutexLocker locker(mutex);
   return data.Data[42];
}
void DebugLogEntry::setData_42(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[42] != value;
   data.Data[42] = value;
   mutex->unlock();
   if (changed) emit Data_42Changed(value);
}

quint8 DebugLogEntry::getData_43() const
{
   QMutexLocker locker(mutex);
   return data.Data[43];
}
void DebugLogEntry::setData_43(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[43] != value;
   data.Data[43] = value;
   mutex->unlock();
   if (changed) emit Data_43Changed(value);
}

quint8 DebugLogEntry::getData_44() const
{
   QMutexLocker locker(mutex);
   return data.Data[44];
}
void DebugLogEntry::setData_44(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[44] != value;
   data.Data[44] = value;
   mutex->unlock();
   if (changed) emit Data_44Changed(value);
}

quint8 DebugLogEntry::getData_45() const
{
   QMutexLocker locker(mutex);
   return data.Data[45];
}
void DebugLogEntry::setData_45(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[45] != value;
   data.Data[45] = value;
   mutex->unlock();
   if (changed) emit Data_45Changed(value);
}

quint8 DebugLogEntry::getData_46() const
{
   QMutexLocker locker(mutex);
   return data.Data[46];
}
void DebugLogEntry::setData_46(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[46] != value;
   data.Data[46] = value;
   mutex->unlock();
   if (changed) emit Data_46Changed(value);
}

quint8 DebugLogEntry::getData_47() const
{
   QMutexLocker locker(mutex);
   return data.Data[47];
}
void DebugLogEntry::setData_47(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[47] != value;
   data.Data[47] = value;
   mutex->unlock();
   if (changed) emit Data_47Changed(value);
}

quint8 DebugLogEntry::getData_48() const
{
   QMutexLocker locker(mutex);
   return data.Data[48];
}
void DebugLogEntry::setData_48(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[48] != value;
   data.Data[48] = value;
   mutex->unlock();
   if (changed) emit Data_48Changed(value);
}

quint8 DebugLogEntry::getData_49() const
{
   QMutexLocker locker(mutex);
   return data.Data[49];
}
void DebugLogEntry::setData_49(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[49] != value;
   data.Data[49] = value;
   mutex->unlock();
   if (changed) emit Data_49Changed(value);
}

quint8 DebugLogEntry::getData_50() const
{
   QMutexLocker locker(mutex);
   return data.Data[50];
}
void DebugLogEntry::setData_50(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[50] != value;
   data.Data[50] = value;
   mutex->unlock();
   if (changed) emit Data_50Changed(value);
}

quint8 DebugLogEntry::getData_51() const
{
   QMutexLocker locker(mutex);
   return data.Data[51];
}
void DebugLogEntry::setData_51(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[51] != value;
   data.Data[51] = value;
   mutex->unlock();
   if (changed) emit Data_51Changed(value);
}

quint8 DebugLogEntry::getData_52() const
{
   QMutexLocker locker(mutex);
   return data.Data[52];
}
void DebugLogEntry::setData_52(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[52] != value;
   data.Data[52] = value;
   mutex->unlock();
   if (changed) emit Data_52Changed(value);
}

quint8 DebugLogEntry::getData_53() const
{
   QMutexLocker locker(mutex);
   return data.Data[53];
}
void DebugLogEntry::setData_53(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[53] != value;
   data.Data[53] = value;
   mutex->unlock();
   if (changed) emit Data_53Changed(value);
}

quint8 DebugLogEntry::getData_54() const
{
   QMutexLocker locker(mutex);
   return data.Data[54];
}
void DebugLogEntry::setData_54(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[54] != value;
   data.Data[54] = value;
   mutex->unlock();
   if (changed) emit Data_54Changed(value);
}

quint8 DebugLogEntry::getData_55() const
{
   QMutexLocker locker(mutex);
   return data.Data[55];
}
void DebugLogEntry::setData_55(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[55] != value;
   data.Data[55] = value;
   mutex->unlock();
   if (changed) emit Data_55Changed(value);
}

quint8 DebugLogEntry::getData_56() const
{
   QMutexLocker locker(mutex);
   return data.Data[56];
}
void DebugLogEntry::setData_56(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[56] != value;
   data.Data[56] = value;
   mutex->unlock();
   if (changed) emit Data_56Changed(value);
}

quint8 DebugLogEntry::getData_57() const
{
   QMutexLocker locker(mutex);
   return data.Data[57];
}
void DebugLogEntry::setData_57(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[57] != value;
   data.Data[57] = value;
   mutex->unlock();
   if (changed) emit Data_57Changed(value);
}

quint8 DebugLogEntry::getData_58() const
{
   QMutexLocker locker(mutex);
   return data.Data[58];
}
void DebugLogEntry::setData_58(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[58] != value;
   data.Data[58] = value;
   mutex->unlock();
   if (changed) emit Data_58Changed(value);
}

quint8 DebugLogEntry::getData_59() const
{
   QMutexLocker locker(mutex);
   return data.Data[59];
}
void DebugLogEntry::setData_59(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[59] != value;
   data.Data[59] = value;
   mutex->unlock();
   if (changed) emit Data_59Changed(value);
}

quint8 DebugLogEntry::getData_60() const
{
   QMutexLocker locker(mutex);
   return data.Data[60];
}
void DebugLogEntry::setData_60(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[60] != value;
   data.Data[60] = value;
   mutex->unlock();
   if (changed) emit Data_60Changed(value);
}

quint8 DebugLogEntry::getData_61() const
{
   QMutexLocker locker(mutex);
   return data.Data[61];
}
void DebugLogEntry::setData_61(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[61] != value;
   data.Data[61] = value;
   mutex->unlock();
   if (changed) emit Data_61Changed(value);
}

quint8 DebugLogEntry::getData_62() const
{
   QMutexLocker locker(mutex);
   return data.Data[62];
}
void DebugLogEntry::setData_62(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[62] != value;
   data.Data[62] = value;
   mutex->unlock();
   if (changed) emit Data_62Changed(value);
}

quint8 DebugLogEntry::getData_63() const
{
   QMutexLocker locker(mutex);
   return data.Data[63];
}
void DebugLogEntry::setData_63(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[63] != value;
   data.Data[63] = value;
   mutex->unlock();
   if (changed) emit Data_63Changed(value);
}

quint8 DebugLogEntry::getData_64() const
{
   QMutexLocker locker(mutex);
   return data.Data[64];
}
void DebugLogEntry::setData_64(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[64] != value;
   data.Data[64] = value;
   mutex->unlock();
   if (changed) emit Data_64Changed(value);
}

quint8 DebugLogEntry::getData_65() const
{
   QMutexLocker locker(mutex);
   return data.Data[65];
}
void DebugLogEntry::setData_65(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[65] != value;
   data.Data[65] = value;
   mutex->unlock();
   if (changed) emit Data_65Changed(value);
}

quint8 DebugLogEntry::getData_66() const
{
   QMutexLocker locker(mutex);
   return data.Data[66];
}
void DebugLogEntry::setData_66(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[66] != value;
   data.Data[66] = value;
   mutex->unlock();
   if (changed) emit Data_66Changed(value);
}

quint8 DebugLogEntry::getData_67() const
{
   QMutexLocker locker(mutex);
   return data.Data[67];
}
void DebugLogEntry::setData_67(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[67] != value;
   data.Data[67] = value;
   mutex->unlock();
   if (changed) emit Data_67Changed(value);
}

quint8 DebugLogEntry::getData_68() const
{
   QMutexLocker locker(mutex);
   return data.Data[68];
}
void DebugLogEntry::setData_68(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[68] != value;
   data.Data[68] = value;
   mutex->unlock();
   if (changed) emit Data_68Changed(value);
}

quint8 DebugLogEntry::getData_69() const
{
   QMutexLocker locker(mutex);
   return data.Data[69];
}
void DebugLogEntry::setData_69(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[69] != value;
   data.Data[69] = value;
   mutex->unlock();
   if (changed) emit Data_69Changed(value);
}

quint8 DebugLogEntry::getData_70() const
{
   QMutexLocker locker(mutex);
   return data.Data[70];
}
void DebugLogEntry::setData_70(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[70] != value;
   data.Data[70] = value;
   mutex->unlock();
   if (changed) emit Data_70Changed(value);
}

quint8 DebugLogEntry::getData_71() const
{
   QMutexLocker locker(mutex);
   return data.Data[71];
}
void DebugLogEntry::setData_71(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[71] != value;
   data.Data[71] = value;
   mutex->unlock();
   if (changed) emit Data_71Changed(value);
}

quint8 DebugLogEntry::getData_72() const
{
   QMutexLocker locker(mutex);
   return data.Data[72];
}
void DebugLogEntry::setData_72(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[72] != value;
   data.Data[72] = value;
   mutex->unlock();
   if (changed) emit Data_72Changed(value);
}

quint8 DebugLogEntry::getData_73() const
{
   QMutexLocker locker(mutex);
   return data.Data[73];
}
void DebugLogEntry::setData_73(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[73] != value;
   data.Data[73] = value;
   mutex->unlock();
   if (changed) emit Data_73Changed(value);
}

quint8 DebugLogEntry::getData_74() const
{
   QMutexLocker locker(mutex);
   return data.Data[74];
}
void DebugLogEntry::setData_74(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[74] != value;
   data.Data[74] = value;
   mutex->unlock();
   if (changed) emit Data_74Changed(value);
}

quint8 DebugLogEntry::getData_75() const
{
   QMutexLocker locker(mutex);
   return data.Data[75];
}
void DebugLogEntry::setData_75(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[75] != value;
   data.Data[75] = value;
   mutex->unlock();
   if (changed) emit Data_75Changed(value);
}

quint8 DebugLogEntry::getData_76() const
{
   QMutexLocker locker(mutex);
   return data.Data[76];
}
void DebugLogEntry::setData_76(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[76] != value;
   data.Data[76] = value;
   mutex->unlock();
   if (changed) emit Data_76Changed(value);
}

quint8 DebugLogEntry::getData_77() const
{
   QMutexLocker locker(mutex);
   return data.Data[77];
}
void DebugLogEntry::setData_77(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[77] != value;
   data.Data[77] = value;
   mutex->unlock();
   if (changed) emit Data_77Changed(value);
}

quint8 DebugLogEntry::getData_78() const
{
   QMutexLocker locker(mutex);
   return data.Data[78];
}
void DebugLogEntry::setData_78(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[78] != value;
   data.Data[78] = value;
   mutex->unlock();
   if (changed) emit Data_78Changed(value);
}

quint8 DebugLogEntry::getData_79() const
{
   QMutexLocker locker(mutex);
   return data.Data[79];
}
void DebugLogEntry::setData_79(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[79] != value;
   data.Data[79] = value;
   mutex->unlock();
   if (changed) emit Data_79Changed(value);
}

quint8 DebugLogEntry::getData_80() const
{
   QMutexLocker locker(mutex);
   return data.Data[80];
}
void DebugLogEntry::setData_80(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[80] != value;
   data.Data[80] = value;
   mutex->unlock();
   if (changed) emit Data_80Changed(value);
}

quint8 DebugLogEntry::getData_81() const
{
   QMutexLocker locker(mutex);
   return data.Data[81];
}
void DebugLogEntry::setData_81(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[81] != value;
   data.Data[81] = value;
   mutex->unlock();
   if (changed) emit Data_81Changed(value);
}

quint8 DebugLogEntry::getData_82() const
{
   QMutexLocker locker(mutex);
   return data.Data[82];
}
void DebugLogEntry::setData_82(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[82] != value;
   data.Data[82] = value;
   mutex->unlock();
   if (changed) emit Data_82Changed(value);
}

quint8 DebugLogEntry::getData_83() const
{
   QMutexLocker locker(mutex);
   return data.Data[83];
}
void DebugLogEntry::setData_83(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[83] != value;
   data.Data[83] = value;
   mutex->unlock();
   if (changed) emit Data_83Changed(value);
}

quint8 DebugLogEntry::getData_84() const
{
   QMutexLocker locker(mutex);
   return data.Data[84];
}
void DebugLogEntry::setData_84(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[84] != value;
   data.Data[84] = value;
   mutex->unlock();
   if (changed) emit Data_84Changed(value);
}

quint8 DebugLogEntry::getData_85() const
{
   QMutexLocker locker(mutex);
   return data.Data[85];
}
void DebugLogEntry::setData_85(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[85] != value;
   data.Data[85] = value;
   mutex->unlock();
   if (changed) emit Data_85Changed(value);
}

quint8 DebugLogEntry::getData_86() const
{
   QMutexLocker locker(mutex);
   return data.Data[86];
}
void DebugLogEntry::setData_86(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[86] != value;
   data.Data[86] = value;
   mutex->unlock();
   if (changed) emit Data_86Changed(value);
}

quint8 DebugLogEntry::getData_87() const
{
   QMutexLocker locker(mutex);
   return data.Data[87];
}
void DebugLogEntry::setData_87(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[87] != value;
   data.Data[87] = value;
   mutex->unlock();
   if (changed) emit Data_87Changed(value);
}

quint8 DebugLogEntry::getData_88() const
{
   QMutexLocker locker(mutex);
   return data.Data[88];
}
void DebugLogEntry::setData_88(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[88] != value;
   data.Data[88] = value;
   mutex->unlock();
   if (changed) emit Data_88Changed(value);
}

quint8 DebugLogEntry::getData_89() const
{
   QMutexLocker locker(mutex);
   return data.Data[89];
}
void DebugLogEntry::setData_89(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[89] != value;
   data.Data[89] = value;
   mutex->unlock();
   if (changed) emit Data_89Changed(value);
}

quint8 DebugLogEntry::getData_90() const
{
   QMutexLocker locker(mutex);
   return data.Data[90];
}
void DebugLogEntry::setData_90(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[90] != value;
   data.Data[90] = value;
   mutex->unlock();
   if (changed) emit Data_90Changed(value);
}

quint8 DebugLogEntry::getData_91() const
{
   QMutexLocker locker(mutex);
   return data.Data[91];
}
void DebugLogEntry::setData_91(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[91] != value;
   data.Data[91] = value;
   mutex->unlock();
   if (changed) emit Data_91Changed(value);
}

quint8 DebugLogEntry::getData_92() const
{
   QMutexLocker locker(mutex);
   return data.Data[92];
}
void DebugLogEntry::setData_92(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[92] != value;
   data.Data[92] = value;
   mutex->unlock();
   if (changed) emit Data_92Changed(value);
}

quint8 DebugLogEntry::getData_93() const
{
   QMutexLocker locker(mutex);
   return data.Data[93];
}
void DebugLogEntry::setData_93(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[93] != value;
   data.Data[93] = value;
   mutex->unlock();
   if (changed) emit Data_93Changed(value);
}

quint8 DebugLogEntry::getData_94() const
{
   QMutexLocker locker(mutex);
   return data.Data[94];
}
void DebugLogEntry::setData_94(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[94] != value;
   data.Data[94] = value;
   mutex->unlock();
   if (changed) emit Data_94Changed(value);
}

quint8 DebugLogEntry::getData_95() const
{
   QMutexLocker locker(mutex);
   return data.Data[95];
}
void DebugLogEntry::setData_95(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[95] != value;
   data.Data[95] = value;
   mutex->unlock();
   if (changed) emit Data_95Changed(value);
}

quint8 DebugLogEntry::getData_96() const
{
   QMutexLocker locker(mutex);
   return data.Data[96];
}
void DebugLogEntry::setData_96(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[96] != value;
   data.Data[96] = value;
   mutex->unlock();
   if (changed) emit Data_96Changed(value);
}

quint8 DebugLogEntry::getData_97() const
{
   QMutexLocker locker(mutex);
   return data.Data[97];
}
void DebugLogEntry::setData_97(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[97] != value;
   data.Data[97] = value;
   mutex->unlock();
   if (changed) emit Data_97Changed(value);
}

quint8 DebugLogEntry::getData_98() const
{
   QMutexLocker locker(mutex);
   return data.Data[98];
}
void DebugLogEntry::setData_98(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[98] != value;
   data.Data[98] = value;
   mutex->unlock();
   if (changed) emit Data_98Changed(value);
}

quint8 DebugLogEntry::getData_99() const
{
   QMutexLocker locker(mutex);
   return data.Data[99];
}
void DebugLogEntry::setData_99(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[99] != value;
   data.Data[99] = value;
   mutex->unlock();
   if (changed) emit Data_99Changed(value);
}

quint8 DebugLogEntry::getData_100() const
{
   QMutexLocker locker(mutex);
   return data.Data[100];
}
void DebugLogEntry::setData_100(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[100] != value;
   data.Data[100] = value;
   mutex->unlock();
   if (changed) emit Data_100Changed(value);
}

quint8 DebugLogEntry::getData_101() const
{
   QMutexLocker locker(mutex);
   return data.Data[101];
}
void DebugLogEntry::setData_101(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[101] != value;
   data.Data[101] = value;
   mutex->unlock();
   if (changed) emit Data_101Changed(value);
}

quint8 DebugLogEntry::getData_102() const
{
   QMutexLocker locker(mutex);
   return data.Data[102];
}
void DebugLogEntry::setData_102(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[102] != value;
   data.Data[102] = value;
   mutex->unlock();
   if (changed) emit Data_102Changed(value);
}

quint8 DebugLogEntry::getData_103() const
{
   QMutexLocker locker(mutex);
   return data.Data[103];
}
void DebugLogEntry::setData_103(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[103] != value;
   data.Data[103] = value;
   mutex->unlock();
   if (changed) emit Data_103Changed(value);
}

quint8 DebugLogEntry::getData_104() const
{
   QMutexLocker locker(mutex);
   return data.Data[104];
}
void DebugLogEntry::setData_104(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[104] != value;
   data.Data[104] = value;
   mutex->unlock();
   if (changed) emit Data_104Changed(value);
}

quint8 DebugLogEntry::getData_105() const
{
   QMutexLocker locker(mutex);
   return data.Data[105];
}
void DebugLogEntry::setData_105(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[105] != value;
   data.Data[105] = value;
   mutex->unlock();
   if (changed) emit Data_105Changed(value);
}

quint8 DebugLogEntry::getData_106() const
{
   QMutexLocker locker(mutex);
   return data.Data[106];
}
void DebugLogEntry::setData_106(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[106] != value;
   data.Data[106] = value;
   mutex->unlock();
   if (changed) emit Data_106Changed(value);
}

quint8 DebugLogEntry::getData_107() const
{
   QMutexLocker locker(mutex);
   return data.Data[107];
}
void DebugLogEntry::setData_107(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[107] != value;
   data.Data[107] = value;
   mutex->unlock();
   if (changed) emit Data_107Changed(value);
}

quint8 DebugLogEntry::getData_108() const
{
   QMutexLocker locker(mutex);
   return data.Data[108];
}
void DebugLogEntry::setData_108(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[108] != value;
   data.Data[108] = value;
   mutex->unlock();
   if (changed) emit Data_108Changed(value);
}

quint8 DebugLogEntry::getData_109() const
{
   QMutexLocker locker(mutex);
   return data.Data[109];
}
void DebugLogEntry::setData_109(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[109] != value;
   data.Data[109] = value;
   mutex->unlock();
   if (changed) emit Data_109Changed(value);
}

quint8 DebugLogEntry::getData_110() const
{
   QMutexLocker locker(mutex);
   return data.Data[110];
}
void DebugLogEntry::setData_110(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[110] != value;
   data.Data[110] = value;
   mutex->unlock();
   if (changed) emit Data_110Changed(value);
}

quint8 DebugLogEntry::getData_111() const
{
   QMutexLocker locker(mutex);
   return data.Data[111];
}
void DebugLogEntry::setData_111(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[111] != value;
   data.Data[111] = value;
   mutex->unlock();
   if (changed) emit Data_111Changed(value);
}

quint8 DebugLogEntry::getData_112() const
{
   QMutexLocker locker(mutex);
   return data.Data[112];
}
void DebugLogEntry::setData_112(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[112] != value;
   data.Data[112] = value;
   mutex->unlock();
   if (changed) emit Data_112Changed(value);
}

quint8 DebugLogEntry::getData_113() const
{
   QMutexLocker locker(mutex);
   return data.Data[113];
}
void DebugLogEntry::setData_113(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[113] != value;
   data.Data[113] = value;
   mutex->unlock();
   if (changed) emit Data_113Changed(value);
}

quint8 DebugLogEntry::getData_114() const
{
   QMutexLocker locker(mutex);
   return data.Data[114];
}
void DebugLogEntry::setData_114(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[114] != value;
   data.Data[114] = value;
   mutex->unlock();
   if (changed) emit Data_114Changed(value);
}

quint8 DebugLogEntry::getData_115() const
{
   QMutexLocker locker(mutex);
   return data.Data[115];
}
void DebugLogEntry::setData_115(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[115] != value;
   data.Data[115] = value;
   mutex->unlock();
   if (changed) emit Data_115Changed(value);
}

quint8 DebugLogEntry::getData_116() const
{
   QMutexLocker locker(mutex);
   return data.Data[116];
}
void DebugLogEntry::setData_116(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[116] != value;
   data.Data[116] = value;
   mutex->unlock();
   if (changed) emit Data_116Changed(value);
}

quint8 DebugLogEntry::getData_117() const
{
   QMutexLocker locker(mutex);
   return data.Data[117];
}
void DebugLogEntry::setData_117(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[117] != value;
   data.Data[117] = value;
   mutex->unlock();
   if (changed) emit Data_117Changed(value);
}

quint8 DebugLogEntry::getData_118() const
{
   QMutexLocker locker(mutex);
   return data.Data[118];
}
void DebugLogEntry::setData_118(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[118] != value;
   data.Data[118] = value;
   mutex->unlock();
   if (changed) emit Data_118Changed(value);
}

quint8 DebugLogEntry::getData_119() const
{
   QMutexLocker locker(mutex);
   return data.Data[119];
}
void DebugLogEntry::setData_119(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[119] != value;
   data.Data[119] = value;
   mutex->unlock();
   if (changed) emit Data_119Changed(value);
}

quint8 DebugLogEntry::getData_120() const
{
   QMutexLocker locker(mutex);
   return data.Data[120];
}
void DebugLogEntry::setData_120(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[120] != value;
   data.Data[120] = value;
   mutex->unlock();
   if (changed) emit Data_120Changed(value);
}

quint8 DebugLogEntry::getData_121() const
{
   QMutexLocker locker(mutex);
   return data.Data[121];
}
void DebugLogEntry::setData_121(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[121] != value;
   data.Data[121] = value;
   mutex->unlock();
   if (changed) emit Data_121Changed(value);
}

quint8 DebugLogEntry::getData_122() const
{
   QMutexLocker locker(mutex);
   return data.Data[122];
}
void DebugLogEntry::setData_122(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[122] != value;
   data.Data[122] = value;
   mutex->unlock();
   if (changed) emit Data_122Changed(value);
}

quint8 DebugLogEntry::getData_123() const
{
   QMutexLocker locker(mutex);
   return data.Data[123];
}
void DebugLogEntry::setData_123(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[123] != value;
   data.Data[123] = value;
   mutex->unlock();
   if (changed) emit Data_123Changed(value);
}

quint8 DebugLogEntry::getData_124() const
{
   QMutexLocker locker(mutex);
   return data.Data[124];
}
void DebugLogEntry::setData_124(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[124] != value;
   data.Data[124] = value;
   mutex->unlock();
   if (changed) emit Data_124Changed(value);
}

quint8 DebugLogEntry::getData_125() const
{
   QMutexLocker locker(mutex);
   return data.Data[125];
}
void DebugLogEntry::setData_125(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[125] != value;
   data.Data[125] = value;
   mutex->unlock();
   if (changed) emit Data_125Changed(value);
}

quint8 DebugLogEntry::getData_126() const
{
   QMutexLocker locker(mutex);
   return data.Data[126];
}
void DebugLogEntry::setData_126(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[126] != value;
   data.Data[126] = value;
   mutex->unlock();
   if (changed) emit Data_126Changed(value);
}

quint8 DebugLogEntry::getData_127() const
{
   QMutexLocker locker(mutex);
   return data.Data[127];
}
void DebugLogEntry::setData_127(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[127] != value;
   data.Data[127] = value;
   mutex->unlock();
   if (changed) emit Data_127Changed(value);
}

quint8 DebugLogEntry::getData_128() const
{
   QMutexLocker locker(mutex);
   return data.Data[128];
}
void DebugLogEntry::setData_128(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[128] != value;
   data.Data[128] = value;
   mutex->unlock();
   if (changed) emit Data_128Changed(value);
}

quint8 DebugLogEntry::getData_129() const
{
   QMutexLocker locker(mutex);
   return data.Data[129];
}
void DebugLogEntry::setData_129(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[129] != value;
   data.Data[129] = value;
   mutex->unlock();
   if (changed) emit Data_129Changed(value);
}

quint8 DebugLogEntry::getData_130() const
{
   QMutexLocker locker(mutex);
   return data.Data[130];
}
void DebugLogEntry::setData_130(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[130] != value;
   data.Data[130] = value;
   mutex->unlock();
   if (changed) emit Data_130Changed(value);
}

quint8 DebugLogEntry::getData_131() const
{
   QMutexLocker locker(mutex);
   return data.Data[131];
}
void DebugLogEntry::setData_131(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[131] != value;
   data.Data[131] = value;
   mutex->unlock();
   if (changed) emit Data_131Changed(value);
}

quint8 DebugLogEntry::getData_132() const
{
   QMutexLocker locker(mutex);
   return data.Data[132];
}
void DebugLogEntry::setData_132(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[132] != value;
   data.Data[132] = value;
   mutex->unlock();
   if (changed) emit Data_132Changed(value);
}

quint8 DebugLogEntry::getData_133() const
{
   QMutexLocker locker(mutex);
   return data.Data[133];
}
void DebugLogEntry::setData_133(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[133] != value;
   data.Data[133] = value;
   mutex->unlock();
   if (changed) emit Data_133Changed(value);
}

quint8 DebugLogEntry::getData_134() const
{
   QMutexLocker locker(mutex);
   return data.Data[134];
}
void DebugLogEntry::setData_134(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[134] != value;
   data.Data[134] = value;
   mutex->unlock();
   if (changed) emit Data_134Changed(value);
}

quint8 DebugLogEntry::getData_135() const
{
   QMutexLocker locker(mutex);
   return data.Data[135];
}
void DebugLogEntry::setData_135(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[135] != value;
   data.Data[135] = value;
   mutex->unlock();
   if (changed) emit Data_135Changed(value);
}

quint8 DebugLogEntry::getData_136() const
{
   QMutexLocker locker(mutex);
   return data.Data[136];
}
void DebugLogEntry::setData_136(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[136] != value;
   data.Data[136] = value;
   mutex->unlock();
   if (changed) emit Data_136Changed(value);
}

quint8 DebugLogEntry::getData_137() const
{
   QMutexLocker locker(mutex);
   return data.Data[137];
}
void DebugLogEntry::setData_137(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[137] != value;
   data.Data[137] = value;
   mutex->unlock();
   if (changed) emit Data_137Changed(value);
}

quint8 DebugLogEntry::getData_138() const
{
   QMutexLocker locker(mutex);
   return data.Data[138];
}
void DebugLogEntry::setData_138(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[138] != value;
   data.Data[138] = value;
   mutex->unlock();
   if (changed) emit Data_138Changed(value);
}

quint8 DebugLogEntry::getData_139() const
{
   QMutexLocker locker(mutex);
   return data.Data[139];
}
void DebugLogEntry::setData_139(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[139] != value;
   data.Data[139] = value;
   mutex->unlock();
   if (changed) emit Data_139Changed(value);
}

quint8 DebugLogEntry::getData_140() const
{
   QMutexLocker locker(mutex);
   return data.Data[140];
}
void DebugLogEntry::setData_140(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[140] != value;
   data.Data[140] = value;
   mutex->unlock();
   if (changed) emit Data_140Changed(value);
}

quint8 DebugLogEntry::getData_141() const
{
   QMutexLocker locker(mutex);
   return data.Data[141];
}
void DebugLogEntry::setData_141(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[141] != value;
   data.Data[141] = value;
   mutex->unlock();
   if (changed) emit Data_141Changed(value);
}

quint8 DebugLogEntry::getData_142() const
{
   QMutexLocker locker(mutex);
   return data.Data[142];
}
void DebugLogEntry::setData_142(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[142] != value;
   data.Data[142] = value;
   mutex->unlock();
   if (changed) emit Data_142Changed(value);
}

quint8 DebugLogEntry::getData_143() const
{
   QMutexLocker locker(mutex);
   return data.Data[143];
}
void DebugLogEntry::setData_143(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[143] != value;
   data.Data[143] = value;
   mutex->unlock();
   if (changed) emit Data_143Changed(value);
}

quint8 DebugLogEntry::getData_144() const
{
   QMutexLocker locker(mutex);
   return data.Data[144];
}
void DebugLogEntry::setData_144(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[144] != value;
   data.Data[144] = value;
   mutex->unlock();
   if (changed) emit Data_144Changed(value);
}

quint8 DebugLogEntry::getData_145() const
{
   QMutexLocker locker(mutex);
   return data.Data[145];
}
void DebugLogEntry::setData_145(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[145] != value;
   data.Data[145] = value;
   mutex->unlock();
   if (changed) emit Data_145Changed(value);
}

quint8 DebugLogEntry::getData_146() const
{
   QMutexLocker locker(mutex);
   return data.Data[146];
}
void DebugLogEntry::setData_146(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[146] != value;
   data.Data[146] = value;
   mutex->unlock();
   if (changed) emit Data_146Changed(value);
}

quint8 DebugLogEntry::getData_147() const
{
   QMutexLocker locker(mutex);
   return data.Data[147];
}
void DebugLogEntry::setData_147(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[147] != value;
   data.Data[147] = value;
   mutex->unlock();
   if (changed) emit Data_147Changed(value);
}

quint8 DebugLogEntry::getData_148() const
{
   QMutexLocker locker(mutex);
   return data.Data[148];
}
void DebugLogEntry::setData_148(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[148] != value;
   data.Data[148] = value;
   mutex->unlock();
   if (changed) emit Data_148Changed(value);
}

quint8 DebugLogEntry::getData_149() const
{
   QMutexLocker locker(mutex);
   return data.Data[149];
}
void DebugLogEntry::setData_149(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[149] != value;
   data.Data[149] = value;
   mutex->unlock();
   if (changed) emit Data_149Changed(value);
}

quint8 DebugLogEntry::getData_150() const
{
   QMutexLocker locker(mutex);
   return data.Data[150];
}
void DebugLogEntry::setData_150(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[150] != value;
   data.Data[150] = value;
   mutex->unlock();
   if (changed) emit Data_150Changed(value);
}

quint8 DebugLogEntry::getData_151() const
{
   QMutexLocker locker(mutex);
   return data.Data[151];
}
void DebugLogEntry::setData_151(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[151] != value;
   data.Data[151] = value;
   mutex->unlock();
   if (changed) emit Data_151Changed(value);
}

quint8 DebugLogEntry::getData_152() const
{
   QMutexLocker locker(mutex);
   return data.Data[152];
}
void DebugLogEntry::setData_152(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[152] != value;
   data.Data[152] = value;
   mutex->unlock();
   if (changed) emit Data_152Changed(value);
}

quint8 DebugLogEntry::getData_153() const
{
   QMutexLocker locker(mutex);
   return data.Data[153];
}
void DebugLogEntry::setData_153(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[153] != value;
   data.Data[153] = value;
   mutex->unlock();
   if (changed) emit Data_153Changed(value);
}

quint8 DebugLogEntry::getData_154() const
{
   QMutexLocker locker(mutex);
   return data.Data[154];
}
void DebugLogEntry::setData_154(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[154] != value;
   data.Data[154] = value;
   mutex->unlock();
   if (changed) emit Data_154Changed(value);
}

quint8 DebugLogEntry::getData_155() const
{
   QMutexLocker locker(mutex);
   return data.Data[155];
}
void DebugLogEntry::setData_155(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[155] != value;
   data.Data[155] = value;
   mutex->unlock();
   if (changed) emit Data_155Changed(value);
}

quint8 DebugLogEntry::getData_156() const
{
   QMutexLocker locker(mutex);
   return data.Data[156];
}
void DebugLogEntry::setData_156(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[156] != value;
   data.Data[156] = value;
   mutex->unlock();
   if (changed) emit Data_156Changed(value);
}

quint8 DebugLogEntry::getData_157() const
{
   QMutexLocker locker(mutex);
   return data.Data[157];
}
void DebugLogEntry::setData_157(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[157] != value;
   data.Data[157] = value;
   mutex->unlock();
   if (changed) emit Data_157Changed(value);
}

quint8 DebugLogEntry::getData_158() const
{
   QMutexLocker locker(mutex);
   return data.Data[158];
}
void DebugLogEntry::setData_158(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[158] != value;
   data.Data[158] = value;
   mutex->unlock();
   if (changed) emit Data_158Changed(value);
}

quint8 DebugLogEntry::getData_159() const
{
   QMutexLocker locker(mutex);
   return data.Data[159];
}
void DebugLogEntry::setData_159(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[159] != value;
   data.Data[159] = value;
   mutex->unlock();
   if (changed) emit Data_159Changed(value);
}

quint8 DebugLogEntry::getData_160() const
{
   QMutexLocker locker(mutex);
   return data.Data[160];
}
void DebugLogEntry::setData_160(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[160] != value;
   data.Data[160] = value;
   mutex->unlock();
   if (changed) emit Data_160Changed(value);
}

quint8 DebugLogEntry::getData_161() const
{
   QMutexLocker locker(mutex);
   return data.Data[161];
}
void DebugLogEntry::setData_161(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[161] != value;
   data.Data[161] = value;
   mutex->unlock();
   if (changed) emit Data_161Changed(value);
}

quint8 DebugLogEntry::getData_162() const
{
   QMutexLocker locker(mutex);
   return data.Data[162];
}
void DebugLogEntry::setData_162(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[162] != value;
   data.Data[162] = value;
   mutex->unlock();
   if (changed) emit Data_162Changed(value);
}

quint8 DebugLogEntry::getData_163() const
{
   QMutexLocker locker(mutex);
   return data.Data[163];
}
void DebugLogEntry::setData_163(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[163] != value;
   data.Data[163] = value;
   mutex->unlock();
   if (changed) emit Data_163Changed(value);
}

quint8 DebugLogEntry::getData_164() const
{
   QMutexLocker locker(mutex);
   return data.Data[164];
}
void DebugLogEntry::setData_164(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[164] != value;
   data.Data[164] = value;
   mutex->unlock();
   if (changed) emit Data_164Changed(value);
}

quint8 DebugLogEntry::getData_165() const
{
   QMutexLocker locker(mutex);
   return data.Data[165];
}
void DebugLogEntry::setData_165(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[165] != value;
   data.Data[165] = value;
   mutex->unlock();
   if (changed) emit Data_165Changed(value);
}

quint8 DebugLogEntry::getData_166() const
{
   QMutexLocker locker(mutex);
   return data.Data[166];
}
void DebugLogEntry::setData_166(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[166] != value;
   data.Data[166] = value;
   mutex->unlock();
   if (changed) emit Data_166Changed(value);
}

quint8 DebugLogEntry::getData_167() const
{
   QMutexLocker locker(mutex);
   return data.Data[167];
}
void DebugLogEntry::setData_167(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[167] != value;
   data.Data[167] = value;
   mutex->unlock();
   if (changed) emit Data_167Changed(value);
}

quint8 DebugLogEntry::getData_168() const
{
   QMutexLocker locker(mutex);
   return data.Data[168];
}
void DebugLogEntry::setData_168(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[168] != value;
   data.Data[168] = value;
   mutex->unlock();
   if (changed) emit Data_168Changed(value);
}

quint8 DebugLogEntry::getData_169() const
{
   QMutexLocker locker(mutex);
   return data.Data[169];
}
void DebugLogEntry::setData_169(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[169] != value;
   data.Data[169] = value;
   mutex->unlock();
   if (changed) emit Data_169Changed(value);
}

quint8 DebugLogEntry::getData_170() const
{
   QMutexLocker locker(mutex);
   return data.Data[170];
}
void DebugLogEntry::setData_170(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[170] != value;
   data.Data[170] = value;
   mutex->unlock();
   if (changed) emit Data_170Changed(value);
}

quint8 DebugLogEntry::getData_171() const
{
   QMutexLocker locker(mutex);
   return data.Data[171];
}
void DebugLogEntry::setData_171(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[171] != value;
   data.Data[171] = value;
   mutex->unlock();
   if (changed) emit Data_171Changed(value);
}

quint8 DebugLogEntry::getData_172() const
{
   QMutexLocker locker(mutex);
   return data.Data[172];
}
void DebugLogEntry::setData_172(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[172] != value;
   data.Data[172] = value;
   mutex->unlock();
   if (changed) emit Data_172Changed(value);
}

quint8 DebugLogEntry::getData_173() const
{
   QMutexLocker locker(mutex);
   return data.Data[173];
}
void DebugLogEntry::setData_173(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[173] != value;
   data.Data[173] = value;
   mutex->unlock();
   if (changed) emit Data_173Changed(value);
}

quint8 DebugLogEntry::getData_174() const
{
   QMutexLocker locker(mutex);
   return data.Data[174];
}
void DebugLogEntry::setData_174(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[174] != value;
   data.Data[174] = value;
   mutex->unlock();
   if (changed) emit Data_174Changed(value);
}

quint8 DebugLogEntry::getData_175() const
{
   QMutexLocker locker(mutex);
   return data.Data[175];
}
void DebugLogEntry::setData_175(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[175] != value;
   data.Data[175] = value;
   mutex->unlock();
   if (changed) emit Data_175Changed(value);
}

quint8 DebugLogEntry::getData_176() const
{
   QMutexLocker locker(mutex);
   return data.Data[176];
}
void DebugLogEntry::setData_176(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[176] != value;
   data.Data[176] = value;
   mutex->unlock();
   if (changed) emit Data_176Changed(value);
}

quint8 DebugLogEntry::getData_177() const
{
   QMutexLocker locker(mutex);
   return data.Data[177];
}
void DebugLogEntry::setData_177(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[177] != value;
   data.Data[177] = value;
   mutex->unlock();
   if (changed) emit Data_177Changed(value);
}

quint8 DebugLogEntry::getData_178() const
{
   QMutexLocker locker(mutex);
   return data.Data[178];
}
void DebugLogEntry::setData_178(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[178] != value;
   data.Data[178] = value;
   mutex->unlock();
   if (changed) emit Data_178Changed(value);
}

quint8 DebugLogEntry::getData_179() const
{
   QMutexLocker locker(mutex);
   return data.Data[179];
}
void DebugLogEntry::setData_179(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[179] != value;
   data.Data[179] = value;
   mutex->unlock();
   if (changed) emit Data_179Changed(value);
}

quint8 DebugLogEntry::getData_180() const
{
   QMutexLocker locker(mutex);
   return data.Data[180];
}
void DebugLogEntry::setData_180(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[180] != value;
   data.Data[180] = value;
   mutex->unlock();
   if (changed) emit Data_180Changed(value);
}

quint8 DebugLogEntry::getData_181() const
{
   QMutexLocker locker(mutex);
   return data.Data[181];
}
void DebugLogEntry::setData_181(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[181] != value;
   data.Data[181] = value;
   mutex->unlock();
   if (changed) emit Data_181Changed(value);
}

quint8 DebugLogEntry::getData_182() const
{
   QMutexLocker locker(mutex);
   return data.Data[182];
}
void DebugLogEntry::setData_182(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[182] != value;
   data.Data[182] = value;
   mutex->unlock();
   if (changed) emit Data_182Changed(value);
}

quint8 DebugLogEntry::getData_183() const
{
   QMutexLocker locker(mutex);
   return data.Data[183];
}
void DebugLogEntry::setData_183(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[183] != value;
   data.Data[183] = value;
   mutex->unlock();
   if (changed) emit Data_183Changed(value);
}

quint8 DebugLogEntry::getData_184() const
{
   QMutexLocker locker(mutex);
   return data.Data[184];
}
void DebugLogEntry::setData_184(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[184] != value;
   data.Data[184] = value;
   mutex->unlock();
   if (changed) emit Data_184Changed(value);
}

quint8 DebugLogEntry::getData_185() const
{
   QMutexLocker locker(mutex);
   return data.Data[185];
}
void DebugLogEntry::setData_185(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[185] != value;
   data.Data[185] = value;
   mutex->unlock();
   if (changed) emit Data_185Changed(value);
}

quint8 DebugLogEntry::getData_186() const
{
   QMutexLocker locker(mutex);
   return data.Data[186];
}
void DebugLogEntry::setData_186(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[186] != value;
   data.Data[186] = value;
   mutex->unlock();
   if (changed) emit Data_186Changed(value);
}

quint8 DebugLogEntry::getData_187() const
{
   QMutexLocker locker(mutex);
   return data.Data[187];
}
void DebugLogEntry::setData_187(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[187] != value;
   data.Data[187] = value;
   mutex->unlock();
   if (changed) emit Data_187Changed(value);
}

quint8 DebugLogEntry::getData_188() const
{
   QMutexLocker locker(mutex);
   return data.Data[188];
}
void DebugLogEntry::setData_188(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[188] != value;
   data.Data[188] = value;
   mutex->unlock();
   if (changed) emit Data_188Changed(value);
}

quint8 DebugLogEntry::getData_189() const
{
   QMutexLocker locker(mutex);
   return data.Data[189];
}
void DebugLogEntry::setData_189(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[189] != value;
   data.Data[189] = value;
   mutex->unlock();
   if (changed) emit Data_189Changed(value);
}

quint8 DebugLogEntry::getData_190() const
{
   QMutexLocker locker(mutex);
   return data.Data[190];
}
void DebugLogEntry::setData_190(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[190] != value;
   data.Data[190] = value;
   mutex->unlock();
   if (changed) emit Data_190Changed(value);
}

quint8 DebugLogEntry::getData_191() const
{
   QMutexLocker locker(mutex);
   return data.Data[191];
}
void DebugLogEntry::setData_191(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[191] != value;
   data.Data[191] = value;
   mutex->unlock();
   if (changed) emit Data_191Changed(value);
}

quint8 DebugLogEntry::getData_192() const
{
   QMutexLocker locker(mutex);
   return data.Data[192];
}
void DebugLogEntry::setData_192(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[192] != value;
   data.Data[192] = value;
   mutex->unlock();
   if (changed) emit Data_192Changed(value);
}

quint8 DebugLogEntry::getData_193() const
{
   QMutexLocker locker(mutex);
   return data.Data[193];
}
void DebugLogEntry::setData_193(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[193] != value;
   data.Data[193] = value;
   mutex->unlock();
   if (changed) emit Data_193Changed(value);
}

quint8 DebugLogEntry::getData_194() const
{
   QMutexLocker locker(mutex);
   return data.Data[194];
}
void DebugLogEntry::setData_194(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[194] != value;
   data.Data[194] = value;
   mutex->unlock();
   if (changed) emit Data_194Changed(value);
}

quint8 DebugLogEntry::getData_195() const
{
   QMutexLocker locker(mutex);
   return data.Data[195];
}
void DebugLogEntry::setData_195(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[195] != value;
   data.Data[195] = value;
   mutex->unlock();
   if (changed) emit Data_195Changed(value);
}

quint8 DebugLogEntry::getData_196() const
{
   QMutexLocker locker(mutex);
   return data.Data[196];
}
void DebugLogEntry::setData_196(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[196] != value;
   data.Data[196] = value;
   mutex->unlock();
   if (changed) emit Data_196Changed(value);
}

quint8 DebugLogEntry::getData_197() const
{
   QMutexLocker locker(mutex);
   return data.Data[197];
}
void DebugLogEntry::setData_197(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[197] != value;
   data.Data[197] = value;
   mutex->unlock();
   if (changed) emit Data_197Changed(value);
}

quint8 DebugLogEntry::getData_198() const
{
   QMutexLocker locker(mutex);
   return data.Data[198];
}
void DebugLogEntry::setData_198(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[198] != value;
   data.Data[198] = value;
   mutex->unlock();
   if (changed) emit Data_198Changed(value);
}

quint8 DebugLogEntry::getData_199() const
{
   QMutexLocker locker(mutex);
   return data.Data[199];
}
void DebugLogEntry::setData_199(quint8 value)
{
   mutex->lock();
   bool changed = data.Data[199] != value;
   data.Data[199] = value;
   mutex->unlock();
   if (changed) emit Data_199Changed(value);
}


