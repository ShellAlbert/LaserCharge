#ifndef SQL_H
#define SQL_H

//create table sql.
#define SQL_CREATE_PROVINCE_TABLE    "CREATE TABLE province (" \
"abbr VARCHAR( 12 )  PRIMARY KEY " \
                    "NOT NULL," \
"name VARCHAR( 64 )  NOT NULL," \
"date DATETIME " \
");"

#define SQL_CREATE_CITY_TABLE       "CREATE TABLE city (" \
    "abbr     VARCHAR( 12 )  PRIMARY KEY " \
                            "NOT NULL," \
    "name     VARCHAR( 64 )  NOT NULL," \
    "province VARCHAR( 12 ),"   \
    "date     DATETIME" \
");"

#define SQL_CREATE_CINEMA_TABLE     "CREATE TABLE cinema ( " \
    "abbr VARCHAR( 48 )   PRIMARY KEY " \
                         "NOT NULL,"  \
    "name VARCHAR( 128 )  NOT NULL," \
    "city VARCHAR( 12 )   NOT NULL," \
    "date DATETIME " \
");"


#define SQL_CREATE_DEVICE_TABLE     "CREATE TABLE device ( " \
    "ID         VARCHAR( 24 )   PRIMARY KEY " \
                               "NOT NULL," \
    "cinema     VARCHAR( 48 )   NOT NULL," \
    "TotalHours REAL            NOT NULL," \
    "memo       VARCHAR( 512 )," \
    "date       DATETIME " \
");"


#define SQL_CREATE_DATA_TABLE      "CREATE TABLE data ( " \
    "CID         INTEGER         PRIMARY KEY AUTOINCREMENT," \
    "ID          VARCHAR( 24 )   NOT NULL," \
    "UUID        VARCHAR( 64 ) NOT NULL," \
    "ChargeHours REAL            NOT NULL," \
    "ValidBefore DATETIME        NOT NULL," \
    "memo        VARCHAR( 512 )," \
    "date        DATETIME " \
");"

//check table sql.
#define SQL_CHECK_PROVINCE  "SELECT COUNT(*) FROM sqlite_master WHERE type='table' and name='province'"
#define SQL_CHECK_CITY      "SELECT COUNT(*) FROM sqlite_master WHERE type='table' and name='city'"
#define SQL_CHECK_CINEMA    "SELECT COUNT(*) FROM sqlite_master WHERE type='table' and name='cinema'"
#define SQL_CHECK_DEVICE    "SELECT COUNT(*) FROM sqlite_master WHERE type='table' and name='device'"
#define SQL_CHECK_DATA      "SELECT COUNT(*) FROM sqlite_master WHERE type='table' and name='data'"

//add province.
#define SQL_ADD_PROVINCE    "INSERT INTO [province] ([abbr], [name], [date]) VALUES (:abbr, :name, :date)"
#define SQL_DEL_PROVINCE    "DELETE FROM province WHERE name=:name"

//add city.
#define SQL_ADD_CITY        "INSERT INTO [city] ([abbr], [name], [province], [date]) VALUES (:abbr, :name, :province, :date)"
#define SQL_DEL_CITY        "DELETE FROM [city] WHERE [name]=:name"

//add cinema.
#define SQL_ADD_CINEMA      "INSERT INTO [cinema] ([abbr], [name], [city], [date]) VALUES (:abbr, :name, :city, :date)"
#define SQL_DEL_CINEMA      "DELETE FROM [cinema] WHERE [name]=:name"
//add device.
#define SQL_ADD_DEVICE      "INSERT INTO [device] ([ID], [cinema], [TotalHours], [memo], [date]) VALUES (:devID, :cinemaAbbr, 0.0, :memo, :date)"
#define SQL_DEL_DEVICE      "DELETE FROM [device] WHERE [ID]=:id"
#define SQL_DEL_DATA        "DELETE FROM [data] WHERE [ID]=:id"
//add data.
#define SQL_ADD_DATA        "INSERT INTO [data] ([ID], [UUID], [ChargeHours], [ValidBefore], [memo], [date]) VALUES (:id, :uuid, :chargeHour, :validBefore, :memo, :date)"
#define SQL_UPT_DATA        "UPDATE [device] SET TotalHours=TotalHours+:totalHour WHERE ID=:id"

//filter history.
#define SQL_FIL_HISTORY     "SELECT [date],[UUID],[ChargeHours],[ValidBefore] FROM [data] WHERE ID=:id"
//select top 10.
#define SQL_GET_TOP10       "SELECT [date],[ChargeHours] FROM [data] WHERE [ID]=:id ORDER BY [date] LIMIT 1,10"
#endif // SQL_H
