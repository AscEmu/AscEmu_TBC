/*
Copyright (c) 2014-2017 AscEmu Team <http://www.ascemu.org/>
This file is released under the MIT license. See README-MIT for more information.
*/

#ifndef UTIL_HPP
#define UTIL_HPP

#include "Common.h"
#include <chrono>
#include <iomanip>

namespace Util
{

    //////////////////////////////////////////////////////////////////////////////////////////
    // String functions

    /*! \brief Manipulates the string to lowercase */
    void StringToLowerCase(std::string& str);

    /*! \brief Manipulates the string to uppercase */
    void StringToUpperCase(std::string& str);

    /*! \brief Capitalize word (uppercase first char, lowercase rest) */
    void CapitalizeString(std::string& str);

    /*! \brief Seperates string by seperator (one char) returns string vecotr */
    std::vector<std::string> SplitStringBySeperator(const std::string& str_src, const std::string& str_sep);

    /*! \brief Returns true if string x is in sttrin y */
    bool findXinYString(std::string& x, std::string& y);

    /*! \brief Returns wow specific language string to id*/
    uint32_t getLanguagesIdFromString(std::string langstr);


    //////////////////////////////////////////////////////////////////////////////////////////
    // Time calculation/formatting

    /*! \brief Returns the current point in time */
    std::chrono::high_resolution_clock::time_point TimeNow();

    /*! \brief Returns the difference between start_time and now in milliseconds */
    long long GetTimeDifferenceToNow(std::chrono::high_resolution_clock::time_point start_time);

    /*! \brief Returns the difference between start_time and end_time in milliseconds */
    long long GetTimeDifference(std::chrono::high_resolution_clock::time_point start_time, std::chrono::high_resolution_clock::time_point end_time);

    /*! \brief Returns the current Date Time as string */
    std::string GetCurrentDateTimeString();

    /*! \brief Returns the current Time as string */
    std::string GetCurrentTimeString();

    /*! \brief Returns Date Time as string from timestamp */
    std::string GetDateTimeStringFromTimeStamp(uint32_t timestamp);

    /*! \brief Returns years months days hours minutes seconds as string from seconds value */
    std::string GetDateStringFromSeconds(uint32_t seconds);

    /*! \brief Returns calculated time based on (second) values e.g. 5h will return 5 * 60 * 60 */
    uint32_t GetTimePeriodFromString(const char* str);

    uint32_t getMSTime();

    std::string ByteArrayToHexString(uint8_t const* bytes, uint32_t arrayLength, bool reverseArray = false);

}

#endif  // UTIL_HPP
