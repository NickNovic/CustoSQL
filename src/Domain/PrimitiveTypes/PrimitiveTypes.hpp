#ifndef TYPES
#define TYPES

#include <bitset>
#include <cstddef>
#include <vector>
#include <string>

// In this file are stored all of basic types used while
// database for storing and processing data

    /*
    * Base type for all primitive types
    */
    class Primitive{
        public:
            // virtual PrimitiveType(std::vector<std::byte> bytes);
            virtual ~Primitive() = 0;
            /*
            * Returns byte representation of the type
            */
            virtual std::vector<std::byte> toBytes() = 0;
            /*
            * Returns string representation of the type
            */
            virtual std::string toString() = 0;
    };

    /*
    * This class is used to store and process integers in SQL Tables.
    * It's size is 2 bytes and it supports all of standart operations like +, -, *, /, <, >, =, ==.
    * First byte contains sign and others are used for storing the value.
    * Value 00000000 is equal to 0.
    */
    class SqlInt : public Primitive{
        private:
            // size of type in bits
            static const int size = 32;
            // position of sign bit
            static const int signBit = 0;
            std::bitset<size> bits;
            // Helper function
            static SqlInt binarySumm(bool sign, SqlInt a, SqlInt b);
            static SqlInt flipNumber(SqlInt number, int position);
        public:
            // Constructors & destructors
            SqlInt(int value = 0);
            SqlInt(std::bitset<size> bits);
            ~SqlInt();
            // Implementing methods
            std::vector<std::byte> toBytes() override;
            std::string toString() override;
            // Converters
            static int toInt(SqlInt value);
            int toInt();
            explicit operator int();
            // Math methods
            static SqlInt Abs(SqlInt value);
            // Appropriation
            SqlInt operator=(int value);
            // Logical operators
            bool operator<(SqlInt value);
            bool operator<=(SqlInt value);
            bool operator>(SqlInt value);
            bool operator>=(SqlInt value);
            bool operator==(SqlInt value);
            bool operator!=(SqlInt value);
            // Arithmetic operators
            SqlInt operator+(SqlInt value);
            SqlInt& operator++(int);
            SqlInt operator+=(SqlInt value);
            SqlInt operator-(SqlInt value);
            SqlInt& operator--(int);
            SqlInt operator-=(SqlInt value);
            SqlInt operator*(SqlInt value);
            SqlInt operator*=(SqlInt value);
            SqlInt operator/(SqlInt value);
            SqlInt operator/=(SqlInt value); 
            SqlInt operator%(SqlInt value);
            SqlInt operator%=(SqlInt value);
    };

    /*
    * This class is used to store and process floats in SQL Tables
    * It's size is  and it supports all of standart operations like +, -, *, / etc.
    * Inside it contains a common fraction
    */
    class SqlFloat : public Primitive{
        private:
            SqlInt solid;
            SqlInt numerator;
            SqlInt denominator;
            int size;
        public:
            // Overriding constructors
            SqlFloat(std::vector<std::byte> bytes);
            ~SqlFloat();
            // Implementing methods
            std::vector<std::byte> toBytes() override;
            std::string toString() override;
            static SqlInt* toSqlInt(SqlFloat* value);
            // Methods for converting
            SqlFloat fromFloat(float value);
    };

    // class SqlString : public PrimitiveType{
    //     private:
    //         std::vector<std::byte> bytes;
    //         int size;
    //     public:
    //         SqlString();
    //         ~SqlString();
    //         SqlString fromString(std::string value);
    // };

#endif