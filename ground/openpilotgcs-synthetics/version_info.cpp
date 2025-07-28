/**
 ******************************************************************************
 * @file       version_info.cpp.template
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2013.
 * @addtogroup VersionInfo
 * @{
 * @brief      The template file used to generate the real source file called
 *             build/openpilotgcs-synthetics/version_info.cpp
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

VersionInfo::VersionInfo()
{
}

QString VersionInfo::origin()
{
    return "https://github.com/MAVProxyUser/NinjaPilot-15.02.ninja.git";
}

QString VersionInfo::revision()
{
    return "claude:55f7242a-dirty 20250728 03:15";
}

QString VersionInfo::hash()
{
    return "55f7242ae66ce8f53f564e03d8ae4b6ffd5f294f";
}

QString VersionInfo::uavoHash()
{
    return "da39a3ee5e6b4b0d3255bfef95601890afd80709";
}

QString VersionInfo::uavoHashArray()
{
    return "{ 0xda,0x39,0xa3,0xee,0x5e,0x6b,0x4b,0x0d,0x32,0x55,0xbf,0xef,0x95,0x60,0x18,0x90,0xaf,0xd8,0x07,0x09 }";
}

QString VersionInfo::label()
{
    return "NinjaPilot-BETA-15.02.ninja+r30-g55f7242-dirty";
}

QString VersionInfo::tag()
{
    return "";
}

QString VersionInfo::tagOrBranch()
{
    return "claude";
}

QString VersionInfo::tagOrHash8()
{
    return "55f7242a";
}

QString VersionInfo::hash8()
{
    return "55f7242a";
}

QString VersionInfo::fwTag()
{
    return "claude-dirty";
}

QString VersionInfo::unixTime()
{
    return "1753672518";
}

QString VersionInfo::dateTime()
{
    return "20250728 03:15";
}

QString VersionInfo::date()
{
    return "20250728";
}

QString VersionInfo::day()
{
    return "28";
}

QString VersionInfo::month()
{
    return "07";
}

QString VersionInfo::year()
{
    return "2025";
}

QString VersionInfo::hour()
{
    return "03";
}

QString VersionInfo::minute()
{
    return "15";
}

QString VersionInfo::dirty()
{
    return "-dirty";
}
